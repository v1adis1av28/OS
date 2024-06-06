#ifndef CARDATABASE_H
#define CARDATABASE_H
#include <vector>
#include <QDataStream>
#include "Savedata.h"
#include <QFile>
#include <windows.h>
#include <iostream>
#include <qdebug.h>
#include <algorithm> // Для std::fill
#include <winbase.h>
class CarDataBase
{
public:
    void SortRecords();
    CarDataBase();
    bool start();
    //Возвращает кол-во записей
    int count(SOCKET);
    void append(SOCKET);

    void append_load(Cars& record);
    void remove(SOCKET);

    bool sl_UploadFile();
void sl_SaveDataBase();
    int id_rec(int id);
    int update(SOCKET);
    //возвращает запись (только для чтения) по заданному идентификатору;
    Cars record_id(SOCKET);
    Cars record_index(SOCKET);
    Cars index_rec(int index);
    QVector<Cars> Records(SOCKET);
    bool save(QString filename);
    //bool load(QString filename);
    //Очищает все файлы
    void clear();
    int getSize();
    //показывает, имеются ли изменения БД после ее загрузки/сохранения
    bool IsModified() const;
    bool empty();
    int getNextId();
    int GetNewNext();


private:
    int size_ = 0;
    QVector<Cars> records;
    bool is_changed = false;
    //const LPCTSTR FILENAME = TEXT("main.dd");
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

        HANDLE hPipe;
      //  DWORD mode, bytesWritten, bytesRead;
        //char buffer[1024];
      //  int bufferSize = 1024;
        int req, pos;
        int nextId = 1;
        unsigned int id = 1;
};

#endif // CARDATABASE_H
