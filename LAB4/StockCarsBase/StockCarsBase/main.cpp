#include "stockcars.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StockCars w;
    w.show();
    return a.exec();
}
