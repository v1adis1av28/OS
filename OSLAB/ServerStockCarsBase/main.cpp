#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <QCoreApplication>
#include <CarDataBase.h>
#include <clocale>
#include <Windows.h>
#include <ws2tcpip.h>

//const LPCTSTR SERVERPIPE = TEXT("\\\\.\\pipe\\StockCarsBasePipe");
CarDataBase* base;
DWORD WINAPI handleClient(LPVOID);
WORD wVersionRequested;
WSADATA wsaData;
int err;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    wVersionRequested = MAKEWORD(2,2);
    err = WSAStartup(wVersionRequested,&wsaData);
   if(err != 0)
   {
       qDebug() << "Error in WSASTARtUP";
        return 0;
    }
        base = new CarDataBase();

       SOCKET sock, kl_sock1;
       int size;
       sock = socket(AF_INET, SOCK_STREAM, 0);
       sockaddr_in sain;
       sain.sin_family = AF_INET;
       sain.sin_port = htons(52000);
       sain.sin_addr.s_addr = inet_addr("127.0.0.1");

       if (bind(sock, (sockaddr *)&sain, sizeof(sain)) == SOCKET_ERROR) {
           qDebug() << "Ошибка при привязке сокета: " << WSAGetLastError();
           closesocket(sock);
           WSACleanup();
           return 0;
       }
       qDebug() << "Socket Connected!";

       while (1)
       {
           listen(sock, 5);
           size = sizeof(sain);
           kl_sock1 = accept(sock, (sockaddr *)&sain, &size);
           if (kl_sock1 == INVALID_SOCKET) {
               qDebug() << "Error in connect: " << WSAGetLastError();
               continue;
           }
           qDebug() << "Connect is Accuired!";

           CreateThread(NULL, 0, handleClient, (LPVOID)(uintptr_t)kl_sock1, 0, NULL);
       }

       WSACleanup();

       return a.exec();
   }




DWORD WINAPI handleClient(LPVOID lpParam) {
    SOCKET sock = (SOCKET)(uintptr_t)lpParam;
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

        //DWORD bytesRead;
        int req;
        do
        {
            //ReadFile(hPipe, (LPVOID)&req, sizeof(int), &bytesRead, NULL);
            recv(sock,(char*)&req,sizeof(req),0);
            switch (req) {
                case APPEND_REQ:
                    base->append(sock);
                    break;
                case RECORDS_REQ:
                    base->Records(sock);
                    break;
                case RECORD_ID_REQ:
                    base->record_id(sock);
                    break;
                case RECORD_INDEX_REQ:
                    base->record_index(sock);
                    break;
                case UPDATE_REQ:
                    base->update(sock);
                    break;
                case COUNT_REQ:
                    base->count(sock);
                    break;
                case REMOVE_REQ:
                    base->remove(sock);
                    break;
              //  case SAVE_REQ:
                   // sl_SaveDataBase();
                   // break;
                case SAVE_DB:
                   base->sl_SaveDataBase();
                    break;
            }
        }while(req!=FINISH_REQ);

    qDebug() << "Disconnetct succesfly.\n";
    closesocket(sock);
}
