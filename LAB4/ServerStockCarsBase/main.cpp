#include <QCoreApplication>
#include "CarDataBase.h"


const LPCTSTR SERVERPIPE = TEXT("\\\\.\\pipe\\StockCarsBasePipe");
CarDataBase* base;
DWORD WINAPI handleClient(HANDLE);



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    base = new CarDataBase();
    HANDLE hServerPipe = CreateNamedPipe(
        SERVERPIPE,                                         // Имя канала
        PIPE_ACCESS_DUPLEX,                                 // Дуплексный доступ
        PIPE_TYPE_MESSAGE | PIPE_READMODE_BYTE | PIPE_WAIT, // Режимы чтения и ожидания
        PIPE_UNLIMITED_INSTANCES,                           // Количество экземпляров
        1024,                                               // Размер выходного буфера
        1024,                                               // Размер входного буфера
        5000,                                               // Время ожидания по умолчанию (5 секунд)
        NULL                                                // Защита по умолчанию
        );

    if (hServerPipe == INVALID_HANDLE_VALUE) {
        qDebug() << "Error creating channel: " << GetLastError();
        //cout << "Error creating channel: " << GetLastError();
        return 0;
    }

    qDebug() << "Named pipe created successfully.\n";
    while (true) {
            // Ожидание соединения
            if (!ConnectNamedPipe(hServerPipe, NULL)) {
                qDebug() << "Ошибка при ожидании подключения: " << GetLastError();
                CloseHandle(hServerPipe);
                return 0;
            }
            qDebug() << "Успешное подключение.\n";

            // Создание потока для обслуживания клиента
            CreateThread(NULL, 0, handleClient, hServerPipe, 0, NULL);

            QThread::sleep(1);
            qDebug() << "Ожидание следующего клиента.\n";

            // Создание именованного канала для приема подключений
            hServerPipe = CreateNamedPipe(
                SERVERPIPE,
                PIPE_ACCESS_DUPLEX,
                PIPE_TYPE_MESSAGE | PIPE_READMODE_BYTE | PIPE_WAIT,
                PIPE_UNLIMITED_INSTANCES,
                1024,
                1024,
                5000,
                NULL
                );

            if (hServerPipe == INVALID_HANDLE_VALUE) {
                qDebug() << "Ошибка создания канала: " << GetLastError();
                return 0;
            }
            qDebug() << "Именованный канал успешно создан.\n";
        }

    QCoreApplication::quit();
    return a.exec();
}




DWORD WINAPI handleClient(HANDLE pipe) {

    HANDLE hClientPipe = (HANDLE)pipe;

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

        DWORD bytesRead;
        int req;
        do
        {
            ReadFile(hClientPipe, (LPVOID)&req, sizeof(int), &bytesRead, NULL);
            switch (req) {
                case APPEND_REQ:
                    base->append(hClientPipe);
                    break;
                case RECORDS_REQ:
                    base->Records(hClientPipe);
                    break;
                case RECORD_ID_REQ:
                    base->record_id(hClientPipe);
                    break;
                case RECORD_INDEX_REQ:
                    base->record_index(hClientPipe);
                    break;
                case UPDATE_REQ:
                    base->update(hClientPipe);
                    break;
                case COUNT_REQ:
                    base->count(hClientPipe);
                    break;
                case REMOVE_REQ:
                    base->remove(hClientPipe);
                    break;
              //  case SAVE_REQ:
                   // sl_SaveDataBase();
                   // break;
                case SAVE_DB:
                   base->sl_SaveDataBase();
                    break;
            }
        }while(req!=FINISH_REQ);

    qDebug() << "Отключение успешно.\n";
    CloseHandle(hClientPipe);
}


