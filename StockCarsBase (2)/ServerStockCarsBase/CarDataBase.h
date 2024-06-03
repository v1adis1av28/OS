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
    bool start();
    //Возвращает кол-во записей
    int count() const;
    void append();

    void append_load(Cars& record);
    void remove(unsigned int id);

    bool sl_UploadFile();
void sl_SaveDataBase();

    int update(Cars& record);
    //возвращает запись (только для чтения) по заданному идентификатору;
    Cars record_id(unsigned int id) const;
    Cars record_index(int index) const;

    QVector<Cars> Records();
    bool save(QString filename) const;
    bool load(QString filename);
    //Очищает все файлы
    void clear();

    //показывает, имеются ли изменения БД после ее загрузки/сохранения
    bool IsModified() const;
    bool empty();
    int getNextId();
    int GetNewNext();


private:
    int size_ = 0;
    int nextId;
    std::vector<Cars> records;
    bool is_changed = false;
    //const LPCTSTR FILENAME = TEXT("main.dd");
       // const LPCTSTR SERVERNAME = TEXT(".exe");
        const LPCTSTR SERVERPIPE = TEXT("\\\\.\\pipe\\StockCarsBasePipe");
        const DWORD
           FINISH_REQ  = 0,
           APPEND_REQ  = 1,
           REMOVE_REQ  = 2,
           SAVE_REQ    = 3,
           RECORD_REQ  = 4,
           RECORDS_REQ = 5,
           COUNT_REQ   = 6,
           UPDATE_REQ  = 7,
           APPEND_LOAD_REQ = 8,
           RECORD_INDEX_REQ = 9,
           RECORD_ID_REQ = 10;
        HANDLE hPipe;
        DWORD mode, bytesWritten, bytesRead;
        char buffer[1024];
        int bufferSize = 1024;
        int req, pos;

        unsigned int id = 0;
};

#endif // CARDATABASE_H
