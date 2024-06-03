#ifndef STOCKCARS_H
#define STOCKCARS_H
#include <QMainWindow>
#include <QDate>
#include <iterator>
#include <QFile>
#include "Savedata.h"
#include "CarDataBase.h"
#include <windows.h>
#include <iostream>
#include <winbase.h>
QT_BEGIN_NAMESPACE
namespace Ui { class StockCars; }
QT_END_NAMESPACE

class StockCars : public QMainWindow
{
    Q_OBJECT

public:
    StockCars(QWidget *parent = nullptr);
    ~StockCars();
    void ReloadInterface();
    void OpenCommandButtons();

private:
    Ui::StockCars *ui;
    CarDataBase base;
    void closeEvent(QCloseEvent *event);
    QString tmp_file_path;
    QString file_path = "E:\test.records";
    int recordType =0;
    void loadFile(const QString& file_path);
    void saveDataFile(const QString& file_path);

private slots:
    void sl_HideInfo();
    void sl_Save();
    void sl_LoadFile();
    void sl_Delete();
    void sl_SwitchDate();
    void sl_AddCar();
    void sl_SwitchRecord();//
    void sl_EditTools();
    void sl_CanselNewRecord();
    void sl_CreateDataBase();

};
#endif // STOCKCARS_H
