/********************************************************************************
** Form generated from reading UI file 'stockcars.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCKCARS_H
#define UI_STOCKCARS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StockCars
{
public:
    QAction *action_SaveAs;
    QAction *action_Save;
    QAction *action_LoadDb;
    QAction *action_SaveDb;
    QAction *action_CreateDb;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *TableCar;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout_2;
    QLabel *label_13;
    QGroupBox *CarType_gb;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *Truck_rb;
    QRadioButton *PassengerCar_rb;
    QRadioButton *Bus_rb;
    QRadioButton *Trailer_rb;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *ModelName;
    QGroupBox *CarsInfo;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_14;
    QDoubleSpinBox *EngineVolume_sp;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_15;
    QSpinBox *Capacity_sp;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_16;
    QSpinBox *Carrying_sp;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_17;
    QSpinBox *MaxSpeed_sp;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_18;
    QDoubleSpinBox *Acceleration_sp;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_19;
    QCheckBox *Climat_flag;
    QFormLayout *formLayout;
    QLabel *label_20;
    QLabel *label_21;
    QSpinBox *Price_sp;
    QLabel *label_22;
    QDateEdit *CurrentDate_sp;
    QSpinBox *Quantity_sp;
    QVBoxLayout *verticalLayout;
    QPushButton *SaveBtn;
    QPushButton *AddButton;
    QPushButton *AddRandBtn;
    QPushButton *CancelBtn;
    QPushButton *DelBtn;
    QPushButton *EditBtn;
    QMenuBar *menubar;
    QMenu *menufile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StockCars)
    {
        if (StockCars->objectName().isEmpty())
            StockCars->setObjectName(QString::fromUtf8("StockCars"));
        StockCars->resize(1069, 668);
        StockCars->setMinimumSize(QSize(1024, 554));
        StockCars->setMaximumSize(QSize(1980, 1020));
        action_SaveAs = new QAction(StockCars);
        action_SaveAs->setObjectName(QString::fromUtf8("action_SaveAs"));
        action_Save = new QAction(StockCars);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        action_LoadDb = new QAction(StockCars);
        action_LoadDb->setObjectName(QString::fromUtf8("action_LoadDb"));
        action_SaveDb = new QAction(StockCars);
        action_SaveDb->setObjectName(QString::fromUtf8("action_SaveDb"));
        action_CreateDb = new QAction(StockCars);
        action_CreateDb->setObjectName(QString::fromUtf8("action_CreateDb"));
        centralwidget = new QWidget(StockCars);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 19, 571, 601));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        TableCar = new QTableWidget(verticalLayoutWidget);
        if (TableCar->columnCount() < 4)
            TableCar->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TableCar->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TableCar->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TableCar->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TableCar->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        TableCar->setObjectName(QString::fromUtf8("TableCar"));
        TableCar->setMaximumSize(QSize(1024, 16777215));

        verticalLayout_4->addWidget(TableCar);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(610, 10, 396, 614));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        QFont font;
        font.setPointSize(12);
        label_13->setFont(font);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_13);

        CarType_gb = new QGroupBox(layoutWidget);
        CarType_gb->setObjectName(QString::fromUtf8("CarType_gb"));
        horizontalLayout_3 = new QHBoxLayout(CarType_gb);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        Truck_rb = new QRadioButton(CarType_gb);
        Truck_rb->setObjectName(QString::fromUtf8("Truck_rb"));

        horizontalLayout_3->addWidget(Truck_rb);

        PassengerCar_rb = new QRadioButton(CarType_gb);
        PassengerCar_rb->setObjectName(QString::fromUtf8("PassengerCar_rb"));

        horizontalLayout_3->addWidget(PassengerCar_rb);

        Bus_rb = new QRadioButton(CarType_gb);
        Bus_rb->setObjectName(QString::fromUtf8("Bus_rb"));

        horizontalLayout_3->addWidget(Bus_rb);

        Trailer_rb = new QRadioButton(CarType_gb);
        Trailer_rb->setObjectName(QString::fromUtf8("Trailer_rb"));

        horizontalLayout_3->addWidget(Trailer_rb);


        formLayout_2->setWidget(1, QFormLayout::FieldRole, CarType_gb);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);

        horizontalLayout_2->addWidget(label_12);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        ModelName = new QLineEdit(layoutWidget);
        ModelName->setObjectName(QString::fromUtf8("ModelName"));
        ModelName->setMaxLength(30);
        ModelName->setClearButtonEnabled(false);

        horizontalLayout_2->addWidget(ModelName);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, horizontalLayout_2);


        verticalLayout_3->addLayout(formLayout_2);

        CarsInfo = new QGroupBox(layoutWidget);
        CarsInfo->setObjectName(QString::fromUtf8("CarsInfo"));
        CarsInfo->setFont(font);
        verticalLayout_2 = new QVBoxLayout(CarsInfo);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_14 = new QLabel(CarsInfo);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font);

        horizontalLayout_9->addWidget(label_14);

        EngineVolume_sp = new QDoubleSpinBox(CarsInfo);
        EngineVolume_sp->setObjectName(QString::fromUtf8("EngineVolume_sp"));
        EngineVolume_sp->setMinimum(0.500000000000000);
        EngineVolume_sp->setMaximum(30.000000000000000);

        horizontalLayout_9->addWidget(EngineVolume_sp);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_15 = new QLabel(CarsInfo);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font);

        horizontalLayout_8->addWidget(label_15);

        Capacity_sp = new QSpinBox(CarsInfo);
        Capacity_sp->setObjectName(QString::fromUtf8("Capacity_sp"));
        Capacity_sp->setMinimum(1);
        Capacity_sp->setMaximum(300);

        horizontalLayout_8->addWidget(Capacity_sp);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_16 = new QLabel(CarsInfo);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font);

        horizontalLayout_6->addWidget(label_16);

        Carrying_sp = new QSpinBox(CarsInfo);
        Carrying_sp->setObjectName(QString::fromUtf8("Carrying_sp"));
        Carrying_sp->setMinimum(100);
        Carrying_sp->setMaximum(5000);

        horizontalLayout_6->addWidget(Carrying_sp);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_17 = new QLabel(CarsInfo);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font);

        horizontalLayout_5->addWidget(label_17);

        MaxSpeed_sp = new QSpinBox(CarsInfo);
        MaxSpeed_sp->setObjectName(QString::fromUtf8("MaxSpeed_sp"));
        MaxSpeed_sp->setMinimum(60);
        MaxSpeed_sp->setMaximum(320);

        horizontalLayout_5->addWidget(MaxSpeed_sp);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_18 = new QLabel(CarsInfo);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font);

        horizontalLayout_4->addWidget(label_18);

        Acceleration_sp = new QDoubleSpinBox(CarsInfo);
        Acceleration_sp->setObjectName(QString::fromUtf8("Acceleration_sp"));
        Acceleration_sp->setMinimum(5.000000000000000);
        Acceleration_sp->setMaximum(120.000000000000000);

        horizontalLayout_4->addWidget(Acceleration_sp);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_19 = new QLabel(CarsInfo);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font);

        horizontalLayout_7->addWidget(label_19);

        Climat_flag = new QCheckBox(CarsInfo);
        Climat_flag->setObjectName(QString::fromUtf8("Climat_flag"));

        horizontalLayout_7->addWidget(Climat_flag);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout_3->addWidget(CarsInfo);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_20);

        label_21 = new QLabel(layoutWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_21);

        Price_sp = new QSpinBox(layoutWidget);
        Price_sp->setObjectName(QString::fromUtf8("Price_sp"));
        Price_sp->setMinimum(20000);
        Price_sp->setMaximum(3000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, Price_sp);

        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_22);

        CurrentDate_sp = new QDateEdit(layoutWidget);
        CurrentDate_sp->setObjectName(QString::fromUtf8("CurrentDate_sp"));

        formLayout->setWidget(2, QFormLayout::FieldRole, CurrentDate_sp);

        Quantity_sp = new QSpinBox(layoutWidget);
        Quantity_sp->setObjectName(QString::fromUtf8("Quantity_sp"));
        Quantity_sp->setMaximum(1000);

        formLayout->setWidget(0, QFormLayout::FieldRole, Quantity_sp);


        verticalLayout_3->addLayout(formLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(10, -1, 10, -1);
        SaveBtn = new QPushButton(layoutWidget);
        SaveBtn->setObjectName(QString::fromUtf8("SaveBtn"));

        verticalLayout->addWidget(SaveBtn);

        AddButton = new QPushButton(layoutWidget);
        AddButton->setObjectName(QString::fromUtf8("AddButton"));

        verticalLayout->addWidget(AddButton);

        AddRandBtn = new QPushButton(layoutWidget);
        AddRandBtn->setObjectName(QString::fromUtf8("AddRandBtn"));

        verticalLayout->addWidget(AddRandBtn);

        CancelBtn = new QPushButton(layoutWidget);
        CancelBtn->setObjectName(QString::fromUtf8("CancelBtn"));

        verticalLayout->addWidget(CancelBtn);

        DelBtn = new QPushButton(layoutWidget);
        DelBtn->setObjectName(QString::fromUtf8("DelBtn"));

        verticalLayout->addWidget(DelBtn);

        EditBtn = new QPushButton(layoutWidget);
        EditBtn->setObjectName(QString::fromUtf8("EditBtn"));

        verticalLayout->addWidget(EditBtn);


        verticalLayout_3->addLayout(verticalLayout);

        StockCars->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StockCars);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1069, 21));
        menufile = new QMenu(menubar);
        menufile->setObjectName(QString::fromUtf8("menufile"));
        StockCars->setMenuBar(menubar);
        statusbar = new QStatusBar(StockCars);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        StockCars->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menufile->addSeparator();
        menufile->addAction(action_SaveAs);
        menufile->addAction(action_Save);
        menufile->addAction(action_SaveDb);
        menufile->addAction(action_LoadDb);
        menufile->addSeparator();
        menufile->addAction(action_CreateDb);

        retranslateUi(StockCars);

        QMetaObject::connectSlotsByName(StockCars);
    } // setupUi

    void retranslateUi(QMainWindow *StockCars)
    {
        StockCars->setWindowTitle(QCoreApplication::translate("StockCars", "StockCars", nullptr));
        action_SaveAs->setText(QCoreApplication::translate("StockCars", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", nullptr));
        action_Save->setText(QCoreApplication::translate("StockCars", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 ", nullptr));
        action_LoadDb->setText(QCoreApplication::translate("StockCars", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\261\320\260\320\267\321\203 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        action_SaveDb->setText(QCoreApplication::translate("StockCars", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\261\320\260\320\267\321\203 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        action_CreateDb->setText(QCoreApplication::translate("StockCars", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\261\320\260\320\267\321\203 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem = TableCar->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("StockCars", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\274\320\276\320\264\320\265\320\273\320\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TableCar->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("StockCars", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TableCar->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("StockCars", "\320\246\320\265\320\275\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TableCar->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("StockCars", "id", nullptr));
        label_13->setText(QCoreApplication::translate("StockCars", "\320\242\320\270\320\277", nullptr));
        CarType_gb->setTitle(QString());
        Truck_rb->setText(QCoreApplication::translate("StockCars", "\320\223\321\200\321\203\320\267\320\276\320\262\320\276\320\271", nullptr));
        PassengerCar_rb->setText(QCoreApplication::translate("StockCars", "\320\233\320\265\320\263\320\272\320\276\320\262\320\276\320\271", nullptr));
        Bus_rb->setText(QCoreApplication::translate("StockCars", "\320\220\320\262\321\202\320\276\320\261\321\203\321\201", nullptr));
        Trailer_rb->setText(QCoreApplication::translate("StockCars", "\320\237\321\200\320\270\321\206\320\265\320\277", nullptr));
        label_12->setText(QCoreApplication::translate("StockCars", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\274\320\276\320\264\320\265\320\273\320\270", nullptr));
        CarsInfo->setTitle(QCoreApplication::translate("StockCars", "\320\236\321\201\320\275\320\276\320\262\320\275\321\213\320\265 \321\205\320\260\321\200\320\260\320\272\321\202\320\265\321\200\320\270\321\201\321\202\320\270\320\272\320\270", nullptr));
        label_14->setText(QCoreApplication::translate("StockCars", "\320\236\320\261\321\212\320\265\320\274 \320\264\320\262\320\270\320\263\320\260\321\202\320\265\320\273\321\217", nullptr));
        label_15->setText(QCoreApplication::translate("StockCars", "\320\222\320\274\320\265\321\201\321\202\320\270\320\274\320\276\321\201\321\202\321\214", nullptr));
        label_16->setText(QCoreApplication::translate("StockCars", "\320\223\321\200\321\203\320\267\320\276\320\277\320\276\320\264\321\212\320\265\320\274\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_17->setText(QCoreApplication::translate("StockCars", "\320\234\320\260\320\272\321\201\320\270\320\274\320\260\320\273\321\214\320\275\320\260\321\217 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\321\214", nullptr));
        label_18->setText(QCoreApplication::translate("StockCars", "\320\240\320\260\320\267\320\263\320\276\320\275 \320\264\320\276 100 \320\272\320\274/\321\207", nullptr));
        label_19->setText(QCoreApplication::translate("StockCars", "\320\235\320\260\320\273\320\270\321\207\320\270\320\265 \321\201\320\270\321\201\321\202\320\265\320\274\321\213 \320\272\320\273\320\270\320\274\320\260\321\202-\320\272\320\276\320\275\321\202\321\200\320\276\320\273\321\217", nullptr));
        Climat_flag->setText(QCoreApplication::translate("StockCars", "\320\222 \320\275\320\260\320\273\320\270\321\207\320\270\320\270", nullptr));
        label_20->setText(QCoreApplication::translate("StockCars", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        label_21->setText(QCoreApplication::translate("StockCars", "\320\246\320\265\320\275\320\260", nullptr));
        label_22->setText(QCoreApplication::translate("StockCars", "\320\224\320\260\321\202\320\260 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\263\320\276 \320\267\320\260\320\262\320\276\320\267\320\260", nullptr));
        SaveBtn->setText(QCoreApplication::translate("StockCars", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        AddButton->setText(QCoreApplication::translate("StockCars", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        AddRandBtn->setText(QCoreApplication::translate("StockCars", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\320\273\321\203\321\207\320\260\320\271\320\275\321\213\320\265 \320\267\320\260\320\277\320\270\321\201\320\270", nullptr));
        CancelBtn->setText(QCoreApplication::translate("StockCars", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        DelBtn->setText(QCoreApplication::translate("StockCars", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        EditBtn->setText(QCoreApplication::translate("StockCars", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        menufile->setTitle(QCoreApplication::translate("StockCars", "file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StockCars: public Ui_StockCars {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCKCARS_H
