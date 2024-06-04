#include "CarDataBase.h"
#include <iostream>


using namespace std;

bool CarDataBase::Connect() {
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);

    // Создание нового процесса
  /*  if (!CreateProcess(SERVERNAME, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        qDebug() << "Start server error: " << GetLastError();
        return 0;
    }
*/
    qDebug() << "Start server successful.\n";

    QThread::msleep(1000);

    hPipe = CreateFile(
        SERVERPIPE,                     // Имя канала
        GENERIC_READ | GENERIC_WRITE,   // Доступ к чтению и записи
        0,                              // Не разделять ресурс между потоками
        NULL,                           // Дескриптор безопасности по умолчанию
        OPEN_EXISTING,                  // Открыть существующий канал
        0,                              // Флаги и атрибуты по умолчанию
        NULL                            // Необходимость дополнительных атрибутов
        );

    if (hPipe == INVALID_HANDLE_VALUE) {
        qDebug() << "Connect error: " << GetLastError();
        return 0;
    }

    qDebug() << "Connect successful.";
    return 1;
}

void CarDataBase::SortRecords(){}
// Отключение от серевера
bool CarDataBase::Disconnect() {
    req = FINISH_REQ;
    DWORD bytesWritten;
    if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
        qDebug() << "Error writing to channel: " << GetLastError();
        CloseHandle(hPipe);
        return 0;
    }

    // Закрытие дескриптора канала
    CloseHandle(hPipe);

    // Закрытие дескрипторов процесса и потока
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Обнуление дескрипторов процесса и потока
    ZeroMemory(&pi, sizeof(pi));

    return 1;

}

int CarDataBase::count()
{
    req = COUNT_REQ;
    WriteFile(hPipe, &req, sizeof(req), &bytesWritten, NULL);
    int count;
    if(!ReadFile(hPipe, (LPVOID)&count, sizeof(int), &bytesRead, NULL))
    {
       qDebug() << "NO READ FROM COUNT METHOD!!";
    }
    return count;
}


Cars CarDataBase::record_index(unsigned int index) {
    Cars carCopy;
    req = RECORD_INDEX_REQ;
    DWORD bytesWritten;
    if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
        qDebug() << "Error writing to channel: " << GetLastError();
        return carCopy; // Возвращаем пустую копию объекта, чтобы указать ошибку
    }

    // Записываем индекс в канал
    WriteFile(hPipe, (LPCVOID)&index, sizeof(int), &bytesWritten, NULL);

    Cars::CarData d;
    ReadFile(hPipe, (void*)&d.id, sizeof(d.id), &bytesRead, NULL);
    ReadFile(hPipe, &d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
    ReadFile(hPipe, &d.Truck, sizeof(d.Truck), &bytesRead, NULL);
    ReadFile(hPipe, &d.Bus, sizeof(d.Bus), &bytesRead, NULL);
    ReadFile(hPipe, &d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
    ReadFile(hPipe, &d.volume, sizeof(d.volume), &bytesRead, NULL);
    ReadFile(hPipe, &d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
    ReadFile(hPipe, &d.price, sizeof(d.price), &bytesRead, NULL);
    ReadFile(hPipe, &d.Model, sizeof(d.Model), &bytesRead, NULL);
    ReadFile(hPipe, &d.quantity, sizeof(d.quantity), &bytesRead, NULL);

    carCopy = Cars::fromCarData(d);
    return carCopy;
}

int CarDataBase::append(Cars& record)
{
        req = APPEND_REQ;
        if (!WriteFile(hPipe, (LPVOID)&req, sizeof(int), &bytesWritten, NULL)) {
            qDebug() << "Error writing to channel: " << GetLastError();
            CloseHandle(hPipe);
            return -1;
        }

        Cars::CarData d = Cars::toCarData(record);

        // Запись данных в канал
        WriteFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Model, sizeof(d.Model), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.quantity, sizeof(d.quantity), &bytesRead, NULL);

        record = Cars::fromCarData(d);

        ReadFile(hPipe,(LPVOID)&id, sizeof(id), &bytesRead, NULL);
        record.id = id;
        //ReadFile(hPipe, (void*)&pos, sizeof(pos), &bytesRead, NULL);

        return pos;

}
int CarDataBase::append_load(Cars& tmp)
{
  /*  req = APPEND_LOAD_REQ;
        if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
            qDebug() << "Error writing to channel: " << GetLastError();
            CloseHandle(hPipe);
            return -1;
        }

        Cars::CarData d = Cars::toCarData(tmp);

        // Запись данных в канал
        WriteFile(hPipe, &d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
        WriteFile(hPipe, &d.Truck, sizeof(d.Truck), &bytesRead, NULL);
        WriteFile(hPipe, &d.Bus, sizeof(d.Bus), &bytesRead, NULL);
        WriteFile(hPipe, &d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
        WriteFile(hPipe, &d.volume, sizeof(d.volume), &bytesRead, NULL);
        WriteFile(hPipe, &d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
        WriteFile(hPipe, &d.price, sizeof(d.price), &bytesRead, NULL);
        WriteFile(hPipe, &d.Model, sizeof(d.Model), &bytesRead, NULL);

        tmp = Cars::fromCarData(d);

        ReadFile(hPipe, (void*)&id, sizeof(id), &bytesRead, NULL);
        tmp.id = id;
        ReadFile(hPipe, (void*)&pos, sizeof(pos), &bytesRead, NULL);

        return pos;*/
}
void CarDataBase::sl_addCar(Cars& tmp)
{
     this->append(tmp);
}
void CarDataBase::remove(unsigned int id)
{
    req = REMOVE_REQ;
    if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
        qDebug() << "Error writing to channel: " << GetLastError();
        CloseHandle(hPipe);
        return;
    }

    WriteFile(hPipe, (LPCVOID)&id, sizeof(int), &bytesWritten, NULL);
}
void CarDataBase::sl_UploadFile()
{

}
void CarDataBase::sl_SaveDataBase()
{
    req = SAVE_DB;
       DWORD bytesWritten;
       if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
           qDebug() << "Error writing to channel: " << GetLastError();
           CloseHandle(hPipe);
       }

}
int CarDataBase::update(Cars& record)
{
    // Создаем копию объекта record
    Cars recordCopy = record;

    req = UPDATE_REQ;
    DWORD bytesWritten;
    if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
        qDebug() << "Error writing to channel: " << GetLastError();
        CloseHandle(hPipe);
        return -1;
    }

    WriteFile(hPipe, (LPCVOID)&record.id, sizeof(int), &bytesWritten, NULL);

    Cars::CarData d = Cars::toCarData(recordCopy);

    // Запись данных в канал
    WriteFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesWritten, NULL);
    WriteFile(hPipe,(LPVOID) &d.Model, sizeof(d.Model), &bytesWritten, NULL);
    WriteFile(hPipe,(LPVOID) &d.quantity, sizeof(d.quantity), &bytesWritten, NULL);


    //ReadFile(hPipe, (void*)&pos, sizeof(pos), &bytesRead, NULL);
    return 1;
}
Cars CarDataBase::record_id(unsigned int id) {
    // Создаем копию объекта с информацией о машине
    Cars carCopy;

    // Устанавливаем код запроса на получение записи по идентификатору
    req = RECORD_ID_REQ;
    DWORD bytesWritten;
    if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
        qDebug() << "Error writing to channel: " << GetLastError();
        return carCopy; // Возвращаем пустую копию объекта, чтобы указать ошибку
    }

    // Записываем идентификатор машины в канал
    WriteFile(hPipe, (LPCVOID)&id, sizeof(int), &bytesWritten, NULL);
    Cars::CarData d;
    ReadFile(hPipe, (void*)&d.id, sizeof (d.id), &bytesRead,NULL);
    ReadFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Model, sizeof(d.Model), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.quantity, sizeof(d.quantity), &bytesRead, NULL);
    // Читаем информацию о машине из канала
    // Пример чтения из канала и формирования объекта Cars carCopy;

    carCopy = Cars::fromCarData(d);
    return carCopy;
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
    int count;
    DWORD bytesRead;
    ReadFile(hPipe, (LPVOID)&count, sizeof(int), &bytesRead, NULL);
    qDebug() << "Read from the channel: " << count;

    for(int i = 0; i < count; i++)
    {
        Cars::CarData d;
        // Read the CarData from the channel
        ReadFile(hPipe, (LPVOID)&d.id, sizeof(d.id), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.Model, sizeof(d.Model), &bytesRead, NULL);
        ReadFile(hPipe, (LPVOID)&d.quantity, sizeof(d.quantity), &bytesRead, NULL);
        // Convert the CarData to a Cars object and append it to the result vector
        res.append(Cars::fromCarData(d));
    }

    return res;
}
bool CarDataBase::save(QString filename)
{
   /* req = SAVE_REQ;
    DWORD bytesWritten;
    if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
        qDebug() << "Error writing to channel: " << GetLastError();
        CloseHandle(hPipe);
        return 0;
    }

    return 1;
*/}
bool CarDataBase::load(QString filename)
{
    //return 1;
}
int CarDataBase::getNextId(){}
int CarDataBase::GetNewNext(){}
Cars::CarData toCarData(Cars car) {
   /* Cars::CarData rr;

    rr.id = car.id;
    rr.quantity = car.quantity;
    rr.price = car.price;
    rr.volume = car.volume;
    rr.Capacity = car.Capacity;
    rr.Carrying = car.Carrying;
    rr.Acceleration = car.Acceleration;
    rr.MaxSpeed = car.MaxSpeed;
    rr.Climat = car.Climat;
    rr.Passenger = car.Passenger;
    rr.Truck = car.Truck;
    rr.Trailer = car.Trailer;
    rr.Bus = car.Bus;
    strcpy(rr.date, car.date.toString().toLocal8Bit().data());
    strcpy(rr.Model,car.Model.toLocal8Bit().data());
    return rr;*/
}

Cars fromCarData(Cars::CarData &data){
    /*Cars d;

    d.id = data.id;
    d.quantity = data.quantity;
    d.price = data.price;
    d.volume = data.volume;
    d.Capacity = data.Capacity;
    d.Carrying = data.Carrying;
    d.Acceleration = data.Acceleration;
    d.MaxSpeed = data.MaxSpeed;
    d.Climat = data.Climat;
    d.Passenger = data.Passenger;
    d.Truck = data.Truck;
    d.Trailer = data.Trailer;
    d.Bus = data.Bus;
    QByteArray dateData = data.date;
    std::copy(dateData.constBegin(), dateData.constBegin()+qMin(20, dateData.size()), d.date);
    QByteArray stringData = data.Model;
    std::copy(stringData.constBegin(), stringData.constBegin()+qMin(20, stringData.size()), d.Model);

    return d;*/
}
