#ifndef CARDATABASE_H
#define CARDATABASE_H
#include <vector>
#include <QDataStream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>
#include <QMessageBox>
#include <QFile>
#include <windows.h>
#include <iostream>
#include "Savedata.h"
#include <qdebug.h>
#include <QThread>
#include <algorithm> // Для std::fill
#include <winbase.h>
class CarDataBase
{
public:
    CarDataBase();
    void SortRecords();
    int count();
    int append(Cars& record);
    int append_load(Cars& record);
    void sl_addCar(Cars& tmp);
    void remove(unsigned int id);

    bool Disconnect();
    void sl_UploadFile();
    void sl_SaveDataBase();
    int update(Cars& record);
    Cars record_id(unsigned int id);
    Cars record_index(unsigned int id);
   // Cars record_index(int index);
    QVector<Cars> Records();
    bool save(QString filename);
    bool load(QString filename);
    int getNextId();
    int GetNewNext();
    bool Connect();
private:
    int size_ = 0;
    int nextId;
    //std::vector<Cars> records;
    bool is_changed = false;
    //const LPCTSTR SERVERNAME = TEXT("G:\\OSLAB\\ServerStockCarsBase\\debug\\ServerStockCarsBase.exe");
    const LPCTSTR SERVERPIPE = TEXT("\\\\.\\pipe\\StockCarsBasePipe");

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
    int req, pos;
     SOCKET sock = INVALID_SOCKET;
     //char buffer[1024];
    // int bufferSize = 1024;

     unsigned int id;
     Cars fromCarData(CarData);
     CarData toCarData(Cars);

};

#endif // CARDATABASE_H
