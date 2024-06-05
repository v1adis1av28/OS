#include "stockcars.h"
#include "ui_stockcars.h"
#include <QTableWidget>
#include <chrono>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTimer>
#include <QDebug>
#include "CarDataBase.h"
#include <windows.h>
StockCars::StockCars(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StockCars)
{
    ui->setupUi(this);
    connect(ui->Trailer_rb,SIGNAL(clicked()),this,SLOT(sl_HideInfo()));
    connect(ui->PassengerCar_rb,SIGNAL(clicked()),this,SLOT(sl_HideInfo()));
    connect(ui->Truck_rb,SIGNAL(clicked()),this,SLOT(sl_HideInfo()));
    connect(ui->Bus_rb,SIGNAL(clicked()),this,SLOT(sl_HideInfo()));
    connect(ui->SaveBtn,SIGNAL(clicked()),this,SLOT(sl_Save()));
    connect(ui->DelBtn,SIGNAL(clicked()),this,SLOT(sl_Delete()));
    connect(ui->Quantity_sp,SIGNAL(valueChanged(int)),this,SLOT(sl_SwitchDate()));
    connect(ui->AddButton,SIGNAL(clicked()),this,SLOT(sl_AddCar()));
    connect(ui->TableCar,SIGNAL(cellClicked(int, int)),this,SLOT(sl_SwitchRecord()));
    connect(ui->EditBtn,SIGNAL(clicked()),this,SLOT(sl_EditTools()));
   // connect(ui->CancelBtn,SIGNAL(clicked()),this,SLOT(sl_CanselNewRecord()));
    ui->CarsInfo->setEnabled(true);
    ui->TableCar->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableCar->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
//    ui->CancelBtn->setEnabled(false);
    //
    if (ui->TableCar->rowCount() == 0)
     {
       ui->SaveBtn->setEnabled(false);
       ui->DelBtn->setEnabled(false);
    //   ui->CancelBtn->setEnabled(false);
     }

    QDate curr_date = QDate::currentDate();
    ui->CurrentDate_sp->setMaximumDate(curr_date);
    ui->CurrentDate_sp->setDate(curr_date);
    ui->ModelName->setText(NULL);
    ui->EngineVolume_sp->setMaximum(30);
    ui->Capacity_sp->setMaximum(300);
    ui->Carrying_sp->setMaximum(5000);
    ui->MaxSpeed_sp->setMaximum(320);
    ui->Acceleration_sp->setMaximum(120);
    ui->PassengerCar_rb->click();
    ui->SaveBtn->setEnabled(true);
    int RowCount = ui->TableCar->rowCount();
    if(RowCount == 0)
    {
        ui->DelBtn->setEnabled(false);
        ui->SaveBtn->setEnabled(false);
    }
   // ui->CancelBtn->setEnabled(false);
    QValidator *valid_input = new QRegularExpressionValidator(QRegularExpression("[A-ZА-ЯЁa-zа-яё]+[0-9]+"), this);
    ui->ModelName->setValidator(valid_input);
    ui->CarsInfo->setEnabled(false);
    ui->CarType_gb->setEnabled(false);
    ui->CurrentDate_sp->setEnabled(false);
    ui->Price_sp->setEnabled(false);
    ui->Quantity_sp->setEnabled(false);
    ui->ModelName->setEnabled(false);
    ui->AddButton->setEnabled(false);
    ui->EditBtn->setEnabled(false);
    //QTimer::singleShot(100, this, &StockCars::sl_LoadFile);
    base.Connect();
    sl_LoadFile();
    OpenCommandButtons();

}

void StockCars::ReloadInterface()
{
    ui->TableCar->clearContents();
    ui->TableCar->setRowCount(base.count());

    for (int i = 0; i < base.count(); ++i) {
        Cars tmp = base.record_index(i);
        QString str = tmp.Model;
        QString car_price = QString::number(tmp.price);
        QString car_quantity = QString::number(tmp.quantity);
        QString car_id = QString::number(tmp.id); // Получаем ID записи
        ui->TableCar->setItem(i, 0, new QTableWidgetItem(str));
        ui->TableCar->setItem(i, 1, new QTableWidgetItem(car_quantity));
        ui->TableCar->setItem(i, 2, new QTableWidgetItem(car_price));
        ui->TableCar->setItem(i, 3, new QTableWidgetItem(car_id));
    }

    ui->TableCar->setCurrentCell(0, 0);
}


void StockCars::sl_LoadFile()
{

       ui->TableCar->clearContents();
       ui->TableCar->setRowCount(0);
       int pos = ui->TableCar->rowCount();
       ui->TableCar->insertRow(pos);
       int ins = ui->TableCar->rowCount();
        for(int i = 0;i<base.count();i++)
           {
               Cars tmp = base.record_index(i);
               QString str = tmp.Model;
               QString id = QString::number(tmp.id);
               QString car_price = QString::number(tmp.price);
               QString car_quantity = QString::number(tmp.quantity);
               ui->TableCar->setItem(ins-1,0,new QTableWidgetItem(str));
               ui->TableCar->setItem(ins-1,1,new QTableWidgetItem(car_quantity));
               ui->TableCar->setItem(ins-1,2,new QTableWidgetItem(car_price));
               ui->TableCar->setItem(ins-1,3,new QTableWidgetItem(id));
           }
       //base.sl_UploadFile();
       //base.SortRecords();
       OpenCommandButtons();
       // Переносим данные в таблицу и обновляем интерфейс
       ReloadInterface();
       if (ui->TableCar->rowCount() > 0) {
               // Фокусируемся на первой строке таблицы
               ui->TableCar->setCurrentCell(0, 0);
        }
}


void StockCars::OpenCommandButtons()
{
    ui->CarsInfo->setEnabled(true);
    ui->CarType_gb->setEnabled(true);
    ui->CurrentDate_sp->setEnabled(true);
    ui->Price_sp->setEnabled(true);
    ui->Quantity_sp->setEnabled(true);
    ui->ModelName->setEnabled(true);
    ui->EditBtn->setEnabled(true);
    ui->AddButton->setEnabled(true);
}


void StockCars::sl_CreateDataBase()
{
    if(ui->TableCar->rowCount() == 0)
    {
        ui->AddButton->setEnabled(true);
        ui->EditBtn->setEnabled(true);
    }
    else
    {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Вы уверены, что хотите создать новую базу данных?\nНесохранённые данные будут утеряны!");
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            if(msgBox.exec() == QMessageBox:: No)
            {
                return;
            }
            else
            {
                ui->TableCar->setRowCount(0);
                base.Records().clear();
                ui->CarsInfo->setEnabled(true);
                ui->CarType_gb->setEnabled(true);
                ui->CurrentDate_sp->setEnabled(true);
                ui->Price_sp->setEnabled(true);
                ui->Quantity_sp->setEnabled(true);
                ui->ModelName->setEnabled(true);
                //ui->CancelBtn->setEnabled(false);
                ui->DelBtn->setEnabled(false);
                ui->ModelName->clear();
                ui->EngineVolume_sp->setValue(0.5);
                ui->Capacity_sp->setValue(1);
                ui->Carrying_sp->setValue(100);
                ui->Acceleration_sp->setValue(5);
                ui->MaxSpeed_sp->setValue(60);
                ui->Climat_flag->setChecked(false);
                ui->Price_sp->setValue(20000);
                ui->Quantity_sp->setValue(0);
                QDate curr_date = QDate::currentDate();
                ui->CurrentDate_sp->setDate(curr_date);
            }
    }
}

void StockCars::closeEvent(QCloseEvent *event) {
    QMainWindow::closeEvent(event);
    base.sl_SaveDataBase();
    base.Disconnect();
}


void StockCars::sl_Delete()
{

    int RowCount = ui->TableCar->rowCount();
    if(RowCount == 0)
    {
        ui->DelBtn->setEnabled(false);
       // ui->CancelBtn->setEnabled(false);
        ui->SaveBtn->setEnabled(false);

    }

    int current_row = ui->TableCar->currentRow();
    int id_to_remove = ui->TableCar->item(current_row, 3)->text().toInt(); // Получаем id из четвертого столбца текущей строки
        if (current_row >= 0 && current_row< base.count()) {
            ui->TableCar->removeRow(current_row);
            base.remove(id_to_remove);
        }
    int row_size = ui->TableCar->rowCount();
    if(row_size == current_row)
    {
        ui->TableCar->setCurrentCell(current_row-1,0);
        sl_SwitchRecord();
    }
    else if(current_row == 0)
    {
        ui->TableCar->setCurrentCell(0,0);
        sl_SwitchRecord();
    }
    else
    {
        ui->TableCar->setCurrentCell(current_row,0);
        sl_SwitchRecord();
    }

    //base.SortRecords();
    int curr_size = ui->TableCar->rowCount();
    if(curr_size == 0)
    {
        //ui->CancelBtn->setEnabled(false);
        ui->DelBtn->setEnabled(false);
        ui->SaveBtn->setEnabled(false);
    }

    if(base.Records().size() == 0)
    {
        ui->ModelName->clear();
        ui->EngineVolume_sp->setValue(0.5);
        ui->Capacity_sp->setValue(1);
        ui->Carrying_sp->setValue(100);
        ui->Acceleration_sp->setValue(5);
        ui->MaxSpeed_sp->setValue(60);
        ui->Climat_flag->setChecked(false);
        ui->Price_sp->setValue(20000);
        ui->Quantity_sp->setValue(0);
        QDate curr_date = QDate::currentDate();
        ui->CurrentDate_sp->setDate(curr_date);
    }

}

void StockCars::sl_AddCar()
{
    ui->DelBtn->setEnabled(true);
    ui->SaveBtn->setEnabled(true);
    //ui->CancelBtn->setEnabled(true);
    ui->CarsInfo->setEnabled(true);
    ui->CarType_gb->setEnabled(true);
    ui->CurrentDate_sp->setEnabled(true);
    ui->Price_sp->setEnabled(true);
    ui->Quantity_sp->setEnabled(true);
    ui->ModelName->setEnabled(true);
    Cars tmp;
    tmp.Model = "vlad";
    recordType = base.append(tmp);
    int pos = ui->TableCar->rowCount();
    int count = base.count();
    ui->TableCar->insertRow(pos);
    int ins = ui->TableCar->rowCount();
   for(int i = 0;i<count;i++)
        {
            tmp = base.record_index(i);
            QString str = tmp.Model;
            QString id = QString::number(tmp.id);
            QString car_price = QString::number(tmp.price);
            QString car_quantity = QString::number(tmp.quantity);
            ui->TableCar->setItem(ins-1,0,new QTableWidgetItem(str));
            ui->TableCar->setItem(ins-1,1,new QTableWidgetItem(car_quantity));
            ui->TableCar->setItem(ins-1,2,new QTableWidgetItem(car_price));
            ui->TableCar->setItem(ins-1,3,new QTableWidgetItem(id));
        }
    //base.SortRecords();
    ui->ModelName->clear();
    ui->EngineVolume_sp->setValue(0.5);
    ui->Capacity_sp->setValue(1);
    ui->Carrying_sp->setValue(100);
    ui->Acceleration_sp->setValue(5);
    ui->MaxSpeed_sp->setValue(60);
    ui->Climat_flag->setChecked(false);
    ui->Price_sp->setValue(20000);
    ui->Quantity_sp->setValue(0);
    QDate curr_date = QDate::currentDate();
    ui->CurrentDate_sp->setDate(curr_date);
    ui->TableCar->setCurrentCell(ins-1, 0);
}

void StockCars::sl_EditTools()
{
    ui->CarsInfo->setEnabled(true);
    ui->CarType_gb->setEnabled(true);
    ui->CurrentDate_sp->setEnabled(true);
    ui->Price_sp->setEnabled(true);
    ui->Quantity_sp->setEnabled(true);
    ui->ModelName->setEnabled(true);
}



void StockCars::sl_Save()
{
    int RowCount = ui->TableCar->rowCount();
    if(RowCount == 0)
    {
        ui->DelBtn->setEnabled(false);
        ui->SaveBtn->setEnabled(false);
    }

    int pos = ui->TableCar->currentRow();// позиция элемента
    int id =  ui->TableCar->item(pos,3)->text().toInt();;
    Cars tmp = base.record_id(id);
    tmp.volume = ui->EngineVolume_sp->value();
    tmp.price = ui->Price_sp->value();
    tmp.Capacity = ui->Capacity_sp->value();
    tmp.quantity = ui->Quantity_sp->value();
    tmp.Model = ui->ModelName->text();
    tmp.Carrying = ui->Carrying_sp->value();
    tmp.Acceleration = ui->Acceleration_sp->value();
    tmp.MaxSpeed = ui->MaxSpeed_sp->value();
    tmp.Climat = ui->Climat_flag->checkState();
    tmp.Bus = ui->Bus_rb->isChecked();
    tmp.Trailer = ui->Trailer_rb->isChecked();
    tmp.Truck = ui->Truck_rb->isChecked();
    tmp.Passenger = ui->PassengerCar_rb->isChecked();
    //int cur_pos = ui->TableCar->currentRow();
    //int row_count = ui->TableCar->rowCount();
    tmp.id = ui->TableCar->item(pos,3)->text().toInt();
    int new_pos = base.update(tmp);
    int ins = ui->TableCar->rowCount();
    ui->TableCar->setItem(pos,0,new QTableWidgetItem(tmp.Model));
    ui->TableCar->setItem(pos,1,new QTableWidgetItem(QString::number(tmp.quantity)));
    ui->TableCar->setItem(pos,2,new QTableWidgetItem(QString::number(tmp.price)));
    ui->TableCar->setItem(pos,3,new QTableWidgetItem(QString::number(tmp.id)));
    //ui->TableCar->setRowCount(0);
   /*for(int i = 0;i<base.count();++i)
   {
       int curr_id =  ui->TableCar->item(i,3)->text().toInt();;
       Cars tmp = base.record_id(curr_id);
       QString str = tmp.Model;
       QString car_price = QString::number(tmp.price);
       QString car_quantity = QString::number(tmp.quantity);
       ui->TableCar->setItem(ins-1,0,new QTableWidgetItem(str));
       ui->TableCar->setItem(ins-1,1,new QTableWidgetItem(car_quantity));
       ui->TableCar->setItem(ins-1,2,new QTableWidgetItem(car_price));
       ui->TableCar->setItem(ins-1,3,new QTableWidgetItem(QString::number(tmp.id)));
   }*/
    ui->TableCar->setCurrentCell(ui->TableCar->currentRow(),0);
    ui->CarsInfo->setEnabled(false);
    ui->CarType_gb->setEnabled(false);
    ui->CurrentDate_sp->setEnabled(false);
    ui->Price_sp->setEnabled(false);
    ui->Quantity_sp->setEnabled(false);
    ui->ModelName->setEnabled(false);

}

void StockCars::sl_SwitchRecord()
{
    int row_count = ui->TableCar->rowCount();
    int current_row = ui->TableCar->currentRow();
    if (row_count == 0 || current_row == -1)
    {
        ui->SaveBtn->setEnabled(false);
        ui->DelBtn->setEnabled(false);
       // ui->CancelBtn->setEnabled(false);
        return;
    }

    // Включаем кнопки сохранить, удалить и отменить
    ui->SaveBtn->setEnabled(true);
    ui->DelBtn->setEnabled(true);
   // ui->CancelBtn->setEnabled(true);

    // Получаем id текущей строки
    int curId = ui->TableCar->item(current_row, 3)->text().toInt();

    ui->CarsInfo->setEnabled(false);
    ui->CarType_gb->setEnabled(false);
    ui->CurrentDate_sp->setEnabled(false);
    ui->Price_sp->setEnabled(false);
    ui->Quantity_sp->setEnabled(false);
    ui->ModelName->setEnabled(false);

    // Очищаем поле модели перед установкой нового значения
    ui->ModelName->clear();
    Cars tmp = base.record_id(curId);
    // Устанавливаем новое значение для поля модели
    ui->ModelName->setText(tmp.Model);
    ui->EngineVolume_sp->setValue(tmp.volume);
    ui->Capacity_sp->setValue(tmp.Capacity);
    ui->Carrying_sp->setValue(tmp.Carrying);
    ui->Acceleration_sp->setValue(tmp.Acceleration);
    ui->MaxSpeed_sp->setValue(tmp.MaxSpeed);
    ui->Climat_flag->setChecked(tmp.Climat);
    ui->Price_sp->setValue(tmp.price);
    ui->Quantity_sp->setValue(tmp.quantity);
    ui->CurrentDate_sp->setDate(tmp.date);
    ui->PassengerCar_rb->setChecked(tmp.Passenger);
    ui->Truck_rb->setChecked(tmp.Truck);
    ui->Bus_rb->setChecked(tmp.Bus);
    ui->Trailer_rb->setChecked(tmp.Trailer);
}


void StockCars::sl_SwitchDate()
{
    if(ui->Quantity_sp->value() != 0)
    {
        QDate curr_date = QDate::currentDate();
        ui->CurrentDate_sp->setDate(curr_date);
    }
}

//Подключаем скрытие вводимой информацией через переключения типа кузова
void StockCars:: sl_HideInfo()
{
    if(ui->Trailer_rb->isChecked())
    {
        ui->CarsInfo->setEnabled(false);
    }
    if(ui->Bus_rb->isChecked())
    {
        ui->CarsInfo->setEnabled(true);
    }
    if(ui->PassengerCar_rb->isChecked())
    {
        ui->CarsInfo->setEnabled(true);
    }
    if(ui->Truck_rb->isChecked())
    {
        ui->CarsInfo->setEnabled(true);
    }


}
StockCars::~StockCars()
{
    delete ui;

}

