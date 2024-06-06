#include "CarDataBase.h"
#include "string"
// Запустить сервер

CarDataBase::CarDataBase()
{
    if(!sl_UploadFile())
    {
        qDebug() << "error loading db";
    }
    qDebug() << "db load succesfull";
}


/*bool CarDataBase::start() {

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
            APPEND_REQ  = 1,
            RECORDS_REQ = 3,
            RECORD_ID_REQ =4,
            RECORD_INDEX_REQ =5,
            COUNT_REQ=6,
            UPDATE_REQ=7,
            REMOVE_REQ=8,
            SAVE_REQ=9,
            LOAD_REQ=10,
            SAVE_DB =11;

    Cars rec;

    do
    {
        ReadFile(hPipe, (LPVOID)&req, sizeof(int), &bytesRead, NULL);
        switch (req) {
            case APPEND_REQ:
                append();
                break;
            case RECORDS_REQ:
                Records();
                break;
            case RECORD_ID_REQ:
                record_id();
                break;
            case RECORD_INDEX_REQ:
                record_index();
                break;
            case UPDATE_REQ:
                update();
                break;
            case COUNT_REQ:
                count();
                break;
            case REMOVE_REQ:
                remove();
                break;
          //  case SAVE_REQ:
               // sl_SaveDataBase();
               // break;
            case SAVE_DB:
               sl_SaveDataBase();
                break;
        }
    }while(req!=FINISH_REQ);
    //qDebug() << "Disconnect successful.\n";

    return 1;
}
*/
void CarDataBase::SortRecords()
    {
       /* for(int i = 0;i<count();++i)
        {
            for(int j = 0;j<count()-1;++j)
            {
                if (records[j+1] < records[j]) {
                    Cars tmp = records[j];
                    records[j] = records[j+1];
                    records[j+1] = tmp;
                }
            }
        }*/
    }


    //Возвращает кол-во записей
    int CarDataBase::count(SOCKET sock)
    {
        int size = records.size();
        send(sock,(char*)&size,sizeof(int),0);
        return size;
    }

    int CarDataBase::getNextId()
    {
        int max_id=0;
        for(Cars tmp : records)
        {
            if(tmp.id > max_id)
            {
                max_id = tmp.id;
            }
        }
        return ++max_id;
    }
    void CarDataBase::append(SOCKET sock)
    {
            CarData recordCPY;
            recv(sock,(char*)&recordCPY,sizeof (recordCPY),0);

            Cars record = Cars::fromCarData(recordCPY);
            record.id = getNextId();
            ++size_;

            send(sock,(char*)&record.id,sizeof(unsigned int),0);
            records.push_back(record);
            is_changed = true;
            // Запись данных в канал
            /*ReadFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
            ReadFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesRead, NULL);
            ReadFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesRead, NULL);
            ReadFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
            ReadFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesRead, NULL);
            ReadFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
            ReadFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesRead, NULL);
            ReadFile(hPipe, (LPVOID)&d.Model, sizeof(d.Model), &bytesRead, NULL);
            ReadFile(hPipe, (LPVOID)&d.quantity, sizeof(d.quantity), &bytesRead, NULL);
            */
  /*      recv(sock,(char*)&recordCPY.Passenger,sizeof(recordCPY.Passenger),0);
        recv(sock,(char*)&recordCPY.Truck,sizeof(recordCPY.Truck),0);
        recv(sock,(char*)&recordCPY.Bus,sizeof(recordCPY.Bus),0);
        recv(sock,(char*)&recordCPY.Trailer,sizeof(recordCPY.Trailer),0);
        recv(sock,(char*)&recordCPY.volume,sizeof(recordCPY.volume),0);
        recv(sock,(char*)&recordCPY.Capacity,sizeof(recordCPY.Capacity),0);
        recv(sock,(char*)&recordCPY.price,sizeof(recordCPY.price),0);
        recv(sock,(char*)&recordCPY.Model,sizeof(recordCPY.Model),0);
        recv(sock,(char*)&recordCPY.quantity,sizeof(recordCPY.quantity),0);
*/


    }
    QVector<Cars> CarDataBase::Records(SOCKET sock)
    {

        QVector<Cars> res;
        int size = records.size();
        CarData d;
        //WriteFile(hPipe,(LPVOID)&size, sizeof (size),&bytesWritten,NULL);
        send(sock,(char*)&size,sizeof(size),0);
        for(int i = 0; i < size; i++)
         {
                d = Cars::toCarData(records[i]);
             // Read the CarData from the channel
            /* WriteFile(hPipe, (LPVOID)&d.id, sizeof(d.id), &bytesWritten, NULL);
             WriteFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesWritten, NULL);
             WriteFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesWritten, NULL);
             WriteFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesWritten, NULL);
             WriteFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesWritten, NULL);
             WriteFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesWritten, NULL);
             WriteFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesWritten, NULL);
             WriteFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesWritten, NULL);
             WriteFile(hPipe, (LPVOID)&d.Model, sizeof(d.Model), &bytesWritten, NULL);
             WriteFile(hPipe, (LPVOID)&d.quantity, sizeof(d.quantity), &bytesWritten, NULL);*/
             // Convert the CarData to a Cars object and append it to the result vector
             send(sock,(char*)&d.id,sizeof(d.id),0);
             send(sock,(char*)&d.Passenger,sizeof(d.Passenger),0);
             send(sock,(char*)&d.Truck,sizeof(d.Truck),0);
             send(sock,(char*)&d.Bus,sizeof(d.Bus),0);
             send(sock,(char*)&d.Trailer,sizeof(d.Trailer),0);
             send(sock,(char*)&d.volume,sizeof(d.volume),0);
             send(sock,(char*)&d.Capacity,sizeof(d.Capacity),0);
             send(sock,(char*)&d.price,sizeof(d.price),0);
             send(sock,(char*)&d.Model,sizeof(d.Model),0);
             send(sock,(char*)&d.quantity,sizeof(d.quantity),0);

             res.append(Cars::fromCarData(d));
         }

         return res;
    }

    void CarDataBase::append_load(Cars& record)
    {
        ++size_;
        id++;
        records.push_back(record);
        is_changed = true;
    }


    void CarDataBase::remove(SOCKET sock)
    {
        int id;
        recv(sock,(char*)&id,sizeof(id),0);
        for(int i = 0;i<records.size();i++)
        {
            if(records[i].id == id)
            {
                records.erase(records.begin() + i);
                size_--;
            }
        }
    }

    bool CarDataBase::sl_UploadFile()
        {
            qDebug() << "Начало загрузки файла";

            // Очищаем базу данных
            if (this->records.size() != 0)
                this->clear();

            // Загружаем базу данных из файла
            QString fileName = "G:/CarTest.records";
            qDebug() << "Пытаемся открыть файл" << fileName;
            HANDLE hFile = CreateFile(reinterpret_cast<LPCWSTR>(fileName.utf16()), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hFile == INVALID_HANDLE_VALUE) {
                // Обработка ошибки открытия файла
                //QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл для чтения.");
                qDebug() << "Ошибка: не удалось открыть файл";
                return 0;
            }

            DWORD bytesRead;
            int dbSize = this->records.size();
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

    HANDLE hFile = CreateFile(reinterpret_cast<LPCWSTR>(path.utf16()), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        //QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    DWORD bytesWritten;

    int dbSize = this->records.size();
    if (!WriteFile(hFile, &dbSize, sizeof(int), &bytesWritten, NULL)) {
        // Обработка ошибки записи размера базы данных
        //QMessageBox::critical(nullptr, "Ошибка", "Не удалось записать размер базы данных.");
        CloseHandle(hFile);
        return;
    }

    for (int j = 0; j < dbSize; j++) {
        Cars note = this->index_rec(j);

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


    int CarDataBase::update(SOCKET sock)
    {
        CarData recordCPY;
        /*ReadFile(hPipe, (LPVOID)&d.id, sizeof(int), &bytesWritten, NULL);
        // Запись данных в канал
        ReadFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Model, sizeof(d.Model), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.quantity, sizeof(d.quantity), &bytesRead, NULL);
*/
        /*recv(sock,(char*)&recordCPY.id,sizeof(recordCPY.id),0);
        recv(sock,(char*)&recordCPY.Truck,sizeof(recordCPY.Truck),0);
        recv(sock,(char*)&recordCPY.Bus,sizeof(recordCPY.Bus),0);
        recv(sock,(char*)&recordCPY.Trailer,sizeof(recordCPY.Trailer),0);
        recv(sock,(char*)&recordCPY.volume,sizeof(recordCPY.volume),0);
        recv(sock,(char*)&recordCPY.Capacity,sizeof(recordCPY.Capacity),0);
        recv(sock,(char*)&recordCPY.price,sizeof(recordCPY.price),0);
        recv(sock,(char*)&recordCPY.Model,sizeof(recordCPY.Model),0);
        recv(sock,(char*)&recordCPY.quantity,sizeof(recordCPY.quantity),0);
        */
        recv(sock,(char*)&recordCPY,sizeof(recordCPY),0);
        Cars record = Cars::fromCarData(recordCPY);
        int index = id_rec(recordCPY.id);
        records[index].id = record.id;
        records[index].Truck = record.Truck;
        records[index].Bus = record.Bus;
        records[index].Trailer = record.Trailer;
        records[index].volume = record.volume;
        records[index].Capacity = record.Capacity;
        records[index].price = record.price;
        records[index].Model = record.Model;
        records[index].quantity = record.quantity;

        //SortRecords();
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
        //WriteFile(hPipe, (LPCVOID)&pos, sizeof(curr_pos), &bytesWritten, NULL);
        return curr_pos;
    }
    //возвращает запись (только для чтения) по заданному идентификатору;
    Cars CarDataBase::record_id(SOCKET sock)
    {
        unsigned int tmpId;
        // Записываем идентификатор машины в канал
        //ReadFile(hPipe, (LPVOID)&tmpId, sizeof(int), &bytesRead, NULL);
        recv(sock,(char*)&tmpId,sizeof(tmpId),0);
        Cars result;
        Cars copy;
        CarData d;
        for(auto iterator = records.begin();iterator != records.end();++iterator)
        {
            if((*iterator).id == static_cast<int>(tmpId))
            {
              d = Cars::toCarData(*iterator);
            }
        }


            /*WriteFile(hPipe, (void*)&d.id, sizeof (d.id), &bytesWritten,NULL);
            WriteFile(hPipe, &d.Passenger, sizeof(d.Passenger), &bytesWritten, NULL);
            WriteFile(hPipe, &d.Truck, sizeof(d.Truck), &bytesWritten, NULL);
            WriteFile(hPipe, &d.Bus, sizeof(d.Bus), &bytesWritten, NULL);
            WriteFile(hPipe, &d.Trailer, sizeof(d.Trailer), &bytesWritten, NULL);
            WriteFile(hPipe, &d.volume, sizeof(d.volume), &bytesWritten, NULL);
            WriteFile(hPipe, &d.Capacity, sizeof(d.Capacity), &bytesWritten, NULL);
            WriteFile(hPipe, &d.price, sizeof(d.price), &bytesWritten, NULL);
            WriteFile(hPipe, &d.Model, sizeof(d.Model), &bytesWritten, NULL);
            WriteFile(hPipe, &d.quantity, sizeof(d.quantity), &bytesWritten, NULL);
            */
        /*
            send(sock,(char*)&d.id,sizeof(d.id),0);
            send(sock,(char*)&d.Passenger,sizeof(d.Passenger),0);
            send(sock,(char*)&d.Truck,sizeof(d.Truck),0);
            send(sock,(char*)&d.Bus,sizeof(d.Bus),0);
            send(sock,(char*)&d.Trailer,sizeof(d.Trailer),0);
            send(sock,(char*)&d.volume,sizeof(d.volume),0);
            send(sock,(char*)&d.Capacity,sizeof(d.Capacity),0);
            send(sock,(char*)&d.price,sizeof(d.price),0);
            send(sock,(char*)&d.Model,sizeof(d.Model),0);
            send(sock,(char*)&d.quantity,sizeof(d.quantity),0);*/
            // Читаем информацию о машине из канала
            // Пример чтения из канала и формирования объекта Cars carCopy;
            send(sock,(char*)&d,sizeof(d),0);
            copy = Cars::fromCarData(d);
            return copy;
        }
    Cars CarDataBase::record_index(SOCKET sock)
    {
        //DWORD bytesWritten,bytesRead;
        unsigned int index;
                // Записываем идентификатор машины в канал
         //ReadFile(hPipe, (LPVOID)&index, sizeof(int), &bytesRead, NULL);
        recv(sock,(char*)&index,sizeof(index),0);
        //QVector<Cars>::iterator i = records.begin();
        CarData d = Cars::toCarData(records[index]);
        /*WriteFile(hPipe, &d.id, sizeof(d.id), &bytesWritten, NULL);
        WriteFile(hPipe, &d.Passenger, sizeof(d.Passenger), &bytesWritten, NULL);
        WriteFile(hPipe, &d.Truck, sizeof(d.Truck), &bytesWritten, NULL);
        WriteFile(hPipe, &d.Bus, sizeof(d.Bus), &bytesWritten, NULL);
        WriteFile(hPipe, &d.Trailer, sizeof(d.Trailer), &bytesWritten, NULL);
        WriteFile(hPipe, &d.volume, sizeof(d.volume), &bytesWritten, NULL);
        WriteFile(hPipe, &d.Capacity, sizeof(d.Capacity), &bytesWritten, NULL);
        WriteFile(hPipe, &d.price, sizeof(d.price), &bytesWritten, NULL);
        WriteFile(hPipe, &d.Model, sizeof(d.Model), &bytesWritten, NULL);
        WriteFile(hPipe, &d.quantity, sizeof(d.quantity), &bytesWritten, NULL);
        *//*
        send(sock,(char*)&d.id,sizeof(d.id),0);
        send(sock,(char*)&d.Passenger,sizeof(d.Passenger),0);
        send(sock,(char*)&d.Truck,sizeof(d.Truck),0);
        send(sock,(char*)&d.Bus,sizeof(d.Bus),0);
        send(sock,(char*)&d.Trailer,sizeof(d.Trailer),0);
        send(sock,(char*)&d.volume,sizeof(d.volume),0);
        send(sock,(char*)&d.Capacity,sizeof(d.Capacity),0);
        send(sock,(char*)&d.price,sizeof(d.price),0);
        send(sock,(char*)&d.Model,sizeof(d.Model),0);
        send(sock,(char*)&d.quantity,sizeof(d.quantity),0);*/
        send(sock,(char*)&d,sizeof(d),0);
        Cars res = Cars::fromCarData(d);

    return res;

    }
    int CarDataBase::getSize()
    {
        return size_;
    }

    int CarDataBase::id_rec(int id)
    {
        int index;
        for(int i = 0;i<getSize();i++)
        {
            if(id == records[i].id)
            {
                index = i;
                break;
            }
        }
        return index;
    }

    Cars CarDataBase::index_rec(int index)
    {
        Cars result;
        for(int i = 0;i<getSize();i++)
        {
            if(i == index)
            {
                result = records[i];
                break;
            }
        }
        return result;
    }


    bool CarDataBase::save(QString filename)
    {
        if(filename.length() != 0){
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        if(file.isOpen()){
            QDataStream out(&file);
            out << records.size();
            for(auto iterator = records.begin();iterator    !=records.end();++iterator)
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

    /*bool CarDataBase::load(QString filename)
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

    }*/
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

