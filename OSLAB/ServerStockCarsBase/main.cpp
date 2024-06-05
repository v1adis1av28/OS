#include <QCoreApplication>
#include "CarDataBase.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CarDataBase base;
    base.start();
    //base->start


    std::cout<<"*****"<<endl;
    //закрываем сервер и приложение
    QCoreApplication::quit();
    return a.exec();
}
