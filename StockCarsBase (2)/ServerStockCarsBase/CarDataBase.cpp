#include "CarDataBase.h"
#include "string"
// Запустить сервер
bool CarDataBase::start() {
    // Создание именованного канала
    hPipe = CreateNamedPipe(
        SERVERPIPE,                                         // Имя канала
        PIPE_ACCESS_DUPLEX,                                 // Дуплексный доступ
        PIPE_TYPE_MESSAGE | PIPE_READMODE_BYTE | PIPE_WAIT, // Режимы чтения и ожидания
        PIPE_UNLIMITED_INSTANCES,                           // Количество экземпляров
        1024,                                               // Размер выходного буфера
        1024,                                               // Размер входного буфера
        5000,                                               // Время ожидания по умолчанию (5 секунд)
        NULL                                                // Защита по умолчанию
        );

    if (hPipe == INVALID_HANDLE_VALUE) {
        qDebug() << "Error creating channel: " << GetLastError();
        //cout << "Error creating channel: " << GetLastError();
        return 0;
    }

    qDebug() << "Named pipe created successfully.\n";
    //cout << "Named pipe created successfully.\n";

    // Ожидание соединения
    if (!ConnectNamedPipe(hPipe, NULL)) {
        qDebug() << "Error while waiting for connection: " << GetLastError();
        //cout << "Error while waiting for connection: " << GetLastError();
        CloseHandle(hPipe);
        return 0;
    }
    else
    {
        std::cout<<"Clien connect" <<endl;
    }

    if (!sl_UploadFile()) {
        qDebug() << "Error while loading database: " << GetLastError();
        CloseHandle(hPipe);
        return 0;
    }
    qDebug() << "Database successfully load.\n";

    const DWORD
        FINISH_REQ  = 0,
        APPEND_REQ  = 1;


    Cars rec;

    do
    {
        ReadFile(hPipe, (LPVOID)&req, sizeof(int), &bytesRead, NULL);
        if(req == 1)
            append();
    }while(req!=FINISH_REQ);
    //qDebug() << "Disconnect successful.\n";

    return 1;
}

void CarDataBase::SortRecords()
    {
        for(int i = 0;i<count();++i)
        {
            for(int j = 0;j<count()-1;++j)
            {
                if (records[j+1] < records[j]) {
                    Cars tmp = records[j];
                    records[j] = records[j+1];
                    records[j+1] = tmp;
                }
            }
        }
    }


    //Возвращает кол-во записей
    int CarDataBase::count() const
    {
        return records.size();
    }

    void CarDataBase::append()
    {
            Cars::CarData d;
            // Запись данных в канал
            ReadFile(hPipe, &d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
            ReadFile(hPipe, &d.Truck, sizeof(d.Truck), &bytesRead, NULL);
            ReadFile(hPipe, &d.Bus, sizeof(d.Bus), &bytesRead, NULL);
            ReadFile(hPipe, &d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
            ReadFile(hPipe, &d.volume, sizeof(d.volume), &bytesRead, NULL);
            ReadFile(hPipe, &d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
            ReadFile(hPipe, &d.price, sizeof(d.price), &bytesRead, NULL);
            ReadFile(hPipe, &d.Model, sizeof(d.Model), &bytesRead, NULL);

            Cars record = Cars::fromCarData(d);
        record.id = GetNewNext();
        ++size_;
        nextId++;
        WriteFile(hPipe,(LPCVOID)&record.id,sizeof(unsigned int),&bytesWritten,NULL);
        records.push_back(record);
        is_changed = true;

    }

    void CarDataBase::append_load(Cars& record)
    {
        ++size_;
        nextId++;
        records.push_back(record);
        is_changed = true;
    }


    void CarDataBase::remove(unsigned int id)
    {
        auto iter = std::remove_if(records.begin(), records.end(), [id](const Cars& car) { return car.id == id; });
        if (iter != records.end()) {
            records.erase(iter, records.end());
            is_changed = true;
        }
    }

    bool CarDataBase::sl_UploadFile()
        {
            qDebug() << "Начало загрузки файла";

            // Очищаем базу данных
            if (this->count() != 0)
                this->clear();

            // Загружаем базу данных из файла
            QString fileName = "E:/CarTest.records";
            qDebug() << "Пытаемся открыть файл" << fileName;
            HANDLE hFile = CreateFile(reinterpret_cast<LPCWSTR>(fileName.utf16()), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hFile == INVALID_HANDLE_VALUE) {
                // Обработка ошибки открытия файла
                //QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл для чтения.");
                qDebug() << "Ошибка: не удалось открыть файл";
                return 0;
            }

            DWORD bytesRead;
            int dbSize = this->count();
            if (!ReadFile(hFile, &dbSize, sizeof(int), &bytesRead, nullptr)) {
                // Обработка ошибки чтения размера базы данных
                //QMessageBox::critical(nullptr, "Ошибка", "Не удалось прочитать размер базы данных.");
                qDebug() << "Ошибка: не удалось прочитать размер базы данных";
                CloseHandle(hFile);
                return 0;
            }

            qDebug() << "Размер базы данных:" << dbSize;

            // Считываем данные из файла и добавляем их в базу данных
            for (int j = 0; j < dbSize; j++) {
                qDebug() << "Чтение записи" << j;

                Cars tmp; // Создаём новый временный объект Cars для каждой записи

                // Читаем идентификатор записи
                if (!ReadFile(hFile, &tmp.id, sizeof(int), &bytesRead, nullptr)) {
                    // Обработка ошибки чтения id записи
                    //QMessageBox::critical(nullptr, "Ошибка", "Не удалось прочитать id записи из файла.");
                    qDebug() << "Ошибка: не удалось прочитать id записи из файла.";
                    CloseHandle(hFile);
                    return 0;
                }
                //
                // Прочитаем остальные данные записи
                QString model;
                int price;
                int id, quantity,  Capacity, Carrying, Acceleration, MaxSpeed;
                double volume;
                bool Truck,Bus,Climat,Trailer,Passenger;
                QDate date;
                WCHAR szModel[256];

                if (!ReadFile(hFile, szModel, sizeof(WCHAR) * 256, &bytesRead, NULL) ||
                        !ReadFile(hFile, &id, sizeof(int), &bytesRead, NULL) ||
                        !ReadFile(hFile, &quantity, sizeof(int), &bytesRead, NULL) ||
                        !ReadFile(hFile, &price, sizeof(int), &bytesRead, NULL) ||
                        !ReadFile(hFile, &Capacity, sizeof(int), &bytesRead, NULL) ||
                        !ReadFile(hFile, &volume, sizeof(double), &bytesRead, NULL) ||
                        !ReadFile(hFile, &Carrying, sizeof(int), &bytesRead, NULL) ||
                        !ReadFile(hFile, &Acceleration, sizeof(int), &bytesRead, NULL) ||
                        !ReadFile(hFile, &MaxSpeed, sizeof(int), &bytesRead, NULL) ||
                        !ReadFile(hFile, &Climat, sizeof(bool), &bytesRead, NULL) ||
                        !ReadFile(hFile, &Passenger, sizeof(bool), &bytesRead, NULL) ||
                        !ReadFile(hFile, &Truck, sizeof(bool), &bytesRead, NULL) ||
                        !ReadFile(hFile, &Trailer, sizeof(bool), &bytesRead, NULL) ||
                        !ReadFile(hFile, &Bus, sizeof(bool), &bytesRead, NULL) ||
                        !ReadFile(hFile, &date, sizeof(QDate), &bytesRead, NULL)) {
                    // Обработка ошибки чтения данных
                    //QMessageBox::critical(nullptr, "Ошибка", "Не удалось прочитать данные из файла.");
                    CloseHandle(hFile);
                    return 0;
                }

                // Преобразуем данные в QString
                model = QString::fromWCharArray(szModel);

                // Добавляем данные во временный объект Note
                tmp.Model = model;
                tmp.id = id;
                tmp.quantity = quantity;
                tmp.price = price;
                tmp.Capacity = Capacity;
                tmp.Carrying = Carrying;
                tmp.Acceleration = Acceleration;
                tmp.MaxSpeed = MaxSpeed;
                tmp.volume = volume;
                tmp.Truck = Truck;
                tmp.Bus = Bus;
                tmp.Climat = Climat;
                tmp.Trailer = Trailer;
                tmp.Passenger = Passenger;
                tmp.date = date;

                // Добавляем запись в базу данных
                this->append_load(tmp);
                qDebug() << "Запись прочитана:" << tmp.id;
            }

            CloseHandle(hFile);

            qDebug() << "Завершение загрузки файла";
            return 1;
        }




void CarDataBase::sl_SaveDataBase()
{
    QString path = "G:/CarTest.records";
    if (path.isEmpty())
        return;

    HANDLE hFile = CreateFile(reinterpret_cast<LPCWSTR>(path.utf16()), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        //QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    DWORD bytesWritten;

    int dbSize = this->count();
    if (!WriteFile(hFile, &dbSize, sizeof(int), &bytesWritten, NULL)) {
        // Обработка ошибки записи размера базы данных
        //QMessageBox::critical(nullptr, "Ошибка", "Не удалось записать размер базы данных.");
        CloseHandle(hFile);
        return;
    }

    for (int j = 0; j < dbSize; j++) {
        Cars note = this->record_index(j);

        if (!WriteFile(hFile, &note.id, sizeof(int), &bytesWritten, NULL)) {
            // Обработка ошибки записи id записи
            //QMessageBox::critical(nullptr, "Ошибка", "Не удалось записать id записи.");
            CloseHandle(hFile);
            return;
        }

        // Записываем остальные данные записи

        QString model = note.Model;

        int id = note.id;
        int quantity = note.quantity;
        int price = note.price;
        double volume = note.volume;
        int Capacity = note.Capacity;
        int Carrying = note.Carrying;
        int Acceleration = note.Acceleration;
        int MaxSpeed = note.MaxSpeed;
        bool Climat = note.Climat;
        bool Passenger = note.Passenger;
        bool Truck = note.Truck;
        bool Trailer = note.Trailer;
        bool Bus = note.Bus;
        QDate date = note.date;
        WCHAR szModel[256];
        model.toWCharArray(szModel);

        // Устанавливаем оставшиеся символы в szModel в ничто
        std::fill(szModel + model.size(), szModel + 256, L'\0');

        if (!WriteFile(hFile, szModel, sizeof(WCHAR) * 256, &bytesWritten, NULL) ||
            !WriteFile(hFile, &id, sizeof(int), &bytesWritten, NULL) ||
            !WriteFile(hFile, &quantity, sizeof(int), &bytesWritten, NULL) ||
            !WriteFile(hFile, &price, sizeof(int), &bytesWritten, NULL) ||
            !WriteFile(hFile, &Capacity, sizeof(int), &bytesWritten, NULL) ||
            !WriteFile(hFile, &volume, sizeof(double), &bytesWritten, NULL) ||
            !WriteFile(hFile, &Carrying, sizeof(int), &bytesWritten, NULL) ||
            !WriteFile(hFile, &Acceleration, sizeof(int), &bytesWritten, NULL) ||
            !WriteFile(hFile, &MaxSpeed, sizeof(int), &bytesWritten, NULL) ||
            !WriteFile(hFile, &Climat, sizeof(bool), &bytesWritten, NULL) ||
            !WriteFile(hFile, &Passenger, sizeof(bool), &bytesWritten, NULL) ||
            !WriteFile(hFile, &Truck, sizeof(bool), &bytesWritten, NULL) ||
            !WriteFile(hFile, &Trailer, sizeof(bool), &bytesWritten, NULL) ||
            !WriteFile(hFile, &Bus, sizeof(bool), &bytesWritten, NULL) ||
            !WriteFile(hFile, &date, sizeof(QDate), &bytesWritten, NULL)) {
            // Обработка ошибки записи данных
            //QMessageBox::critical(nullptr, "Ошибка", "Не удалось записать данные в файл.");
            CloseHandle(hFile);
            return;
        }
    }

    CloseHandle(hFile);
}


    int CarDataBase::update(Cars& record)
    {
        for(auto iterator = records.begin();iterator != records.end();++iterator)
        {
           if((*iterator).id == record.id)
           {
              (*iterator).volume =  record.volume;
               (*iterator).price = record.price;
               (*iterator).Capacity = record.Capacity;
               (*iterator).quantity = record.quantity;
               (*iterator).Model = record.Model;
               (*iterator).Carrying = record.Carrying;
               (*iterator).Acceleration = record.Acceleration;
               (*iterator).MaxSpeed = record.MaxSpeed;
               (*iterator).Climat  = record.Climat;
               (*iterator).Bus = record.Bus;
               (*iterator).Trailer = record.Trailer;
               (*iterator).Truck = record.Truck;
               (*iterator).Passenger = record.Passenger;
           }
        }
        SortRecords();
        int curr_pos =0;
        is_changed = true;
        for(auto iterator = records.begin();iterator != records.end();++iterator)
        {
           if((*iterator).id == record.id)
           {
               return curr_pos;
           }
           else
               curr_pos++;
        }
        return curr_pos;
    }
    //возвращает запись (только для чтения) по заданному идентификатору;
    Cars CarDataBase::record_id(unsigned int id) const
    {
        Cars result;
        for(auto iterator = records.begin();iterator != records.end();++iterator)
        {
            if((*iterator).id == static_cast<int>(id))
            {
                result = *iterator;
            }
        }
        return result;
    }
    Cars CarDataBase::record_index(int index) const
    {
        Cars result;
        for(auto iterator = records.begin();iterator != records.end();++iterator)
        {
            if(std::distance(records.begin(),iterator) == index)
            {
                result = *iterator;
            }
        }
        return result;
    }

    QVector<Cars> CarDataBase::Records()
    {

        QVector<Cars> res;
         req = RECORDS_REQ;
         DWORD bytesWritten;
         if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
             qDebug() << "Error writing to channel: " << GetLastError();
             CloseHandle(hPipe);
             return res;
         }

         // Read the count of records from the channel
         int count = records.size();
         DWORD bytesRead;
         if (!ReadFile(hPipe, (LPVOID)&count, sizeof(int), &bytesRead, NULL)) {
             qDebug() << "Error read from channel: " << GetLastError();
             CloseHandle(hPipe);
             return res;
         }
         qDebug() << "Read from the channel: " << count;

         for(int i = 0; i < count; i++)
         {
             Cars::CarData d;
             // Read the CarData from the channel
             WriteFile(hPipe, (void*)&d.id, sizeof(d.id), &bytesRead, NULL);
             WriteFile(hPipe, &d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
             WriteFile(hPipe, &d.Truck, sizeof(d.Truck), &bytesRead, NULL);
             WriteFile(hPipe, &d.Bus, sizeof(d.Bus), &bytesRead, NULL);
             WriteFile(hPipe, &d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
             WriteFile(hPipe, &d.volume, sizeof(d.volume), &bytesRead, NULL);
             WriteFile(hPipe, &d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
             WriteFile(hPipe, &d.price, sizeof(d.price), &bytesRead, NULL);
             WriteFile(hPipe, &d.Model, sizeof(d.Model), &bytesRead, NULL);

             // Convert the CarData to a Cars object and append it to the result vector
             res.append(Cars::fromCarData(d));
         }

         return res;
    }

    bool CarDataBase::save(QString filename) const
    {
        if(filename.length() != 0){
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        if(file.isOpen()){
            QDataStream out(&file);
            out << count();
            for(auto iterator = records.begin();iterator !=records.end();++iterator)
            {
                out << (*iterator).Model;
                out << (*iterator).Passenger;
                out << (*iterator).Bus;
                out << (*iterator).Truck;
                out << (*iterator).Trailer;
                out << (*iterator).volume;
                out << (*iterator).Capacity;
                out << (*iterator).Carrying;
                out << (*iterator).MaxSpeed;
                out <<(*iterator).Acceleration;
                out << (*iterator).price;
                out << (*iterator).quantity;
                out << (*iterator).id;
                out << (*iterator).date;
                out << (*iterator).Climat;
            }
            file.close();
            return true;
        }
        }
        return false;
    }

    bool CarDataBase::load(QString filename)
    {
        if(filename.length() != 0)
        {
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        if(file.isOpen())
        {
        QDataStream in(&file);
        int upl_file_size;
        in >> upl_file_size;
        Cars tmp;
        for(int i = 0;i<upl_file_size;++i)
        {
            in >> tmp.Model;
            in >> tmp.Passenger;
            in >> tmp.Bus;
            in >> tmp.Truck;
            in >> tmp.Trailer;
            in >> tmp.volume;
            in >> tmp.Capacity;
            in >> tmp.Carrying;
            in >> tmp.MaxSpeed;
            in >> tmp.Acceleration;
            in >> tmp.price;
            in >> tmp.quantity;
            in >> tmp.id;
            in >> tmp.date;
            in >> tmp.Climat;
            records.push_back(tmp);
            }
        }
        return true;
        }
       return false;

    }
    //Очищает все файлы
    void CarDataBase::clear()
    {
       size_ = 0;
       records.clear();
       is_changed = true;
    }
    //показывает, имеются ли изменения БД после ее загрузки/сохранения
    bool CarDataBase::IsModified() const
    {
        return is_changed;
    }
    bool CarDataBase::empty()
    {
        return size_ == 0;
    }
    int CarDataBase::getNextId()
    {
        return GetNewNext();
    }
    int CarDataBase::GetNewNext()
    {
        int max =0;
        for(Cars tmp : records)
        {
            if(tmp.id>max)
            {
                max = tmp.id;
            }
        }
        return max+1;
    }

