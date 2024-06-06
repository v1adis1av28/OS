#include "CarDataBase.h"
#include <iostream>

WORD wVersionRequested;
WSADATA wsaData;
int err;

using namespace std;

CarDataBase::CarDataBase()
{

}

bool CarDataBase::Connect() {
   // ZeroMemory( &si, sizeof(si) );
   // si.cb = sizeof(si);
    wVersionRequested = MAKEWORD(2,2);
    // Создание нового процесса
    err = WSAStartup(wVersionRequested,&wsaData);
    if(err !=0)
    {
        qDebug() << "Error Wsastarrtup";
        return 0;
    }

    sock = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in sain;
    sain.sin_family = AF_INET;
    sain.sin_port = htons(52000);
    sain.sin_addr.s_addr = inet_addr("127.0.0.1");

    ::connect(sock, (sockaddr *)&sain, sizeof(sain));
    qDebug() << sock;
    return 1;
}

// Отключение от серевера
bool CarDataBase::Disconnect() {
    req = FINISH_REQ;
    send(sock,(char*)&req,sizeof(req),0);
    closesocket(sock);
    WSACleanup();
    return 1;

}

int CarDataBase::count()
{
    req = COUNT_REQ;
    //WriteFile(hPipe, &req, sizeof(req), &bytesWritten, NULL);
    send(sock,(char*)&req,sizeof (req),0);
    int count;
    /*if(!ReadFile(hPipe, (LPVOID)&count, sizeof(int), &bytesRead, NULL))
    {
       qDebug() << "NO READ FROM COUNT METHOD!!";
    }*/
    recv(sock,(char*)&count,sizeof(count),0);
    return count;
}


Cars CarDataBase::record_index(unsigned int index) {
    Cars carCopy;
    req = RECORD_INDEX_REQ;
    /*DWORD bytesWritten;
    if (!WriteFile(hPipe, (LPCVOID)&req, sizeof(int), &bytesWritten, NULL)) {
        qDebug() << "Error writing to channel: " << GetLastError();
        return carCopy; // Возвращаем пустую копию объекта, чтобы указать ошибку
    }*/
    send(sock,(char*)&req,sizeof(req),0);

    // Записываем индекс в канал
    //WriteFile(hPipe, (LPCVOID)&index, sizeof(int), &bytesWritten, NULL);
    send(sock,(char*)&index,sizeof(req),0);
    CarData d;
    /*ReadFile(hPipe, (void*)&d.id, sizeof(d.id), &bytesRead, NULL);
    ReadFile(hPipe, &d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
    ReadFile(hPipe, &d.Truck, sizeof(d.Truck), &bytesRead, NULL);
    ReadFile(hPipe, &d.Bus, sizeof(d.Bus), &bytesRead, NULL);
    ReadFile(hPipe, &d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
    ReadFile(hPipe, &d.volume, sizeof(d.volume), &bytesRead, NULL);
    ReadFile(hPipe, &d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
    ReadFile(hPipe, &d.price, sizeof(d.price), &bytesRead, NULL);
    ReadFile(hPipe, &d.Model, sizeof(d.Model), &bytesRead, NULL);
    ReadFile(hPipe, &d.quantity, sizeof(d.quantity), &bytesRead, NULL);
*/
    /*recv(sock,(char*)&d.id,sizeof(d.id),0);
    recv(sock,(char*)&d.id,sizeof(d.Passenger),0);
    recv(sock,(char*)&d.id,sizeof(d.Truck),0);
    recv(sock,(char*)&d.id,sizeof(d.Bus),0);
    recv(sock,(char*)&d.id,sizeof(d.Trailer),0);
    recv(sock,(char*)&d.id,sizeof(d.volume),0);
    recv(sock,(char*)&d.id,sizeof(d.Capacity),0);
    recv(sock,(char*)&d.id,sizeof(d.price),0);
    recv(sock,(char*)&d.id,sizeof(d.Model),0);
    recv(sock,(char*)&d.quantity,sizeof(d.quantity),0);*/
    recv(sock,(char*)&d,sizeof(d),0);
    carCopy = Cars::fromCarData(d);
    return carCopy;
}

int CarDataBase::append(Cars& record)
{
        req = APPEND_REQ;
        send(sock,(char*)&req,sizeof(req),0);


        CarData d = Cars::toCarData(record);

        // Запись данных в канал
  /*      WriteFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.Model, sizeof(d.Model), &bytesRead, NULL);
        WriteFile(hPipe, (LPVOID)&d.quantity, sizeof(d.quantity), &bytesRead, NULL);
*/
        /*
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

        record = Cars::fromCarData(d);

        //ReadFile(hPipe,(LPVOID)&id, sizeof(id), &bytesRead, NULL);
        recv(sock,(char*)&d.id,sizeof(d.id),0);
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
    send(sock,(char*)&req,sizeof(req),0);


    //WriteFile(hPipe, (LPCVOID)&id, sizeof(int), &bytesWritten, NULL);
    send(sock,(char*)&id,sizeof(id),0);
}
void CarDataBase::sl_UploadFile()
{

}
void CarDataBase::sl_SaveDataBase()
{
    req = SAVE_DB;
    send(sock,(char*)&req,sizeof(req),0);

}
int CarDataBase::update(Cars& record)
{
    // Создаем копию объекта record
    Cars recordCopy = record;

    req = UPDATE_REQ;
    send(sock,(char*)&req,sizeof(req),0);
    CarData d = Cars::toCarData(recordCopy);
    //WriteFile(hPipe, (LPCVOID)&record.id, sizeof(int), &bytesWritten, NULL);
    send(sock,(char*)&d,sizeof(d),0);



    // Запись данных в канал
    /*WriteFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesWritten, NULL);
    WriteFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesWritten, NULL);
    WriteFile(hPipe,(LPVOID) &d.Model, sizeof(d.Model), &bytesWritten, NULL);
    WriteFile(hPipe,(LPVOID) &d.quantity, sizeof(d.quantity), &bytesWritten, NULL);
*/
   /* send(sock,(char*)&d.Passenger,sizeof(d.Passenger),0);
    send(sock,(char*)&d.Truck,sizeof(d.Truck),0);
    send(sock,(char*)&d.Bus,sizeof(d.Bus),0);
    send(sock,(char*)&d.Trailer,sizeof(d.Trailer),0);
    send(sock,(char*)&d.volume,sizeof(d.volume),0);
    send(sock,(char*)&d.Capacity,sizeof(d.Capacity),0);
    send(sock,(char*)&d.price,sizeof(d.price),0);
    send(sock,(char*)&d.Model,sizeof(d.Model),0);
    send(sock,(char*)&d.quantity,sizeof(d.quantity),0);
*/
    //ReadFile(hPipe, (void*)&pos, sizeof(pos), &bytesRead, NULL);
    return 1;
}
Cars CarDataBase::record_id(unsigned int id) {
    // Создаем копию объекта с информацией о машине
    Cars carCopy;

    // Устанавливаем код запроса на получение записи по идентификатору
    req = RECORD_ID_REQ;
    send(sock,(char*)&req,sizeof(req),0);


    // Записываем идентификатор машины в канал
    //WriteFile(hPipe, (LPCVOID)&id, sizeof(int), &bytesWritten, NULL);
    send(sock,(char*)&id,sizeof(id),0);
    CarData d;
   /* ReadFile(hPipe, (void*)&d.id, sizeof (d.id), &bytesRead,NULL);
    ReadFile(hPipe, (LPVOID)&d.Passenger, sizeof(d.Passenger), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Truck, sizeof(d.Truck), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Bus, sizeof(d.Bus), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Trailer, sizeof(d.Trailer), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.volume, sizeof(d.volume), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Capacity, sizeof(d.Capacity), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.price, sizeof(d.price), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.Model, sizeof(d.Model), &bytesRead, NULL);
    ReadFile(hPipe, (LPVOID)&d.quantity, sizeof(d.quantity), &bytesRead, NULL);
    */// Читаем информацию о машине из канала
    // Пример чтения из канала и формирования объекта Cars carCopy;
    /*recv(sock,(char*)&d.Passenger,sizeof(d.Passenger),0);
    recv(sock,(char*)&d.Truck,sizeof(d.Truck),0);
    recv(sock,(char*)&d.Bus,sizeof(d.Bus),0);
    recv(sock,(char*)&d.Trailer,sizeof(d.Trailer),0);
    recv(sock,(char*)&d.volume,sizeof(d.volume),0);
    recv(sock,(char*)&d.Capacity,sizeof(d.Capacity),0);
    recv(sock,(char*)&d.price,sizeof(d.price),0);
    recv(sock,(char*)&d.Model,sizeof(d.Model),0);
    recv(sock,(char*)&d.quantity,sizeof(d.quantity),0);*/
    recv(sock,(char*)&d,sizeof(d),0);
    carCopy = Cars::fromCarData(d);
    return carCopy;
}

QVector<Cars> CarDataBase::Records()
{
   QVector<Cars> res;
    req = RECORDS_REQ;
    send(sock,(char*)&req,sizeof(req),0);

    // Read the count of records from the channel
    int count;
     CarData d;
    //DWORD bytesRead;
    //ReadFile(hPipe, (LPVOID)&count, sizeof(int), &bytesRead, NULL);
    qDebug() << "Read from the channel: " << count;
    recv(sock,(char*)&count,sizeof(count),0);
    for(int i = 0; i < count; i++)
    {

        // Read the CarData from the channel
        recv(sock,(char*)&d.id,sizeof(d.id),0);
        recv(sock,(char*)&d.Passenger,sizeof(d.Passenger),0);
        recv(sock,(char*)&d.Truck,sizeof(d.Truck),0);
        recv(sock,(char*)&d.Bus,sizeof(d.Bus),0);
        recv(sock,(char*)&d.Trailer,sizeof(d.Trailer),0);
        recv(sock,(char*)&d.volume,sizeof(d.volume),0);
        recv(sock,(char*)&d.Capacity,sizeof(d.Capacity),0);
        recv(sock,(char*)&d.price,sizeof(d.price),0);
        recv(sock,(char*)&d.Model,sizeof(d.Model),0);
        recv(sock,(char*)&d.quantity,sizeof(d.quantity),0);
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
CarData toCarData(Cars car) {
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

Cars fromCarData(CarData &data){
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
