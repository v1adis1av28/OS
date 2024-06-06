#ifndef SAVEDATA_H
#define SAVEDATA_H
#include<QString>
#include<QDate>

struct CarData {
    char Model[100];    // Модель автомобиля
    int id;             // ID
    int quantity;       // Количество
    int price;          // Цена
    double volume;      // Объем
    int Capacity;       // Вместимость
    int Carrying;       // Грузоподъемность
    int Acceleration;   // Ускорение
    int MaxSpeed;       // Максимальная скорость
    bool Climat;        // Климат-контроль
    bool Passenger;     // Пассажирский
    bool Truck;         // Грузовик
    bool Trailer;       // Прицеп
    bool Bus;           // Автобус
    char date[20];      // Дата
};
class Cars
{
public:
    Cars();
        QString Model;
        int id;
        int quantity;
        int price;
        double volume;
        int Capacity;
        int Carrying;
        int Acceleration;
        int MaxSpeed;
        bool Climat;
        bool Passenger;
        bool Truck;
        bool Trailer;
        bool Bus;
        QDate date;



        static CarData toCarData(Cars &car) {
            CarData data;
            QByteArray stringData;

            // Модель автомобиля
            stringData = car.Model.toUtf8();
            std::copy(stringData.constBegin(), stringData.constBegin() + qMin(99, stringData.size()), data.Model);
            data.Model[qMin(100, stringData.size())] = '\0';
            data.id = car.id;
            data.quantity = car.quantity;
            data.price = car.price;
            data.volume = car.volume;
            data.Capacity = car.Capacity;
            data.Carrying = car.Carrying;
            data.Acceleration = car.Acceleration;
            data.MaxSpeed = car.MaxSpeed;
            data.Climat = car.Climat;
            data.Passenger = car.Passenger;
            data.Truck = car.Truck;
            data.Trailer = car.Trailer;
            data.Bus = car.Bus;
            stringData = car.date.toString("dd.MM.yyyy").toUtf8();
            std::copy(stringData.constBegin(), stringData.constBegin() + qMin(10, stringData.size()), data.date);
            data.date[qMin(11, stringData.size())] = '\0';

            return data;
        }

        static Cars fromCarData(const CarData &data) {
            Cars car;
            // Модель автомобиля
            car.Model = QString::fromUtf8(data.Model);
            // ID
            car.id = data.id;
            // Количество
            car.quantity = data.quantity;
            // Цена
            car.price = data.price;
            // Объем
            car.volume = data.volume;
            // Вместимость
            car.Capacity = data.Capacity;
            // Грузоподъемность
            car.Carrying = data.Carrying;
            // Ускорение
            car.Acceleration = data.Acceleration;
            // Максимальная скорость
            car.MaxSpeed = data.MaxSpeed;
            // Климат-контроль
            car.Climat = data.Climat;
            // Пассажирский
            car.Passenger = data.Passenger;
            // Грузовик
            car.Truck = data.Truck;
            // Прицеп
            car.Trailer = data.Trailer;
            // Автобус
            car.Bus = data.Bus;
            // Дата
            car.date = QDate::fromString(QString::fromUtf8(data.date), "dd.MM.yyyy");
            return car;
        }

        bool operator<(const Cars &tmp) const
        {
            if (Passenger != tmp.Passenger) return Passenger > tmp.Passenger;
            if (Truck != tmp.Truck) return Truck > tmp.Truck;
            if (Bus != tmp.Bus) return Bus < tmp.Bus;
            if (Trailer != tmp.Trailer) return Trailer > tmp.Trailer;
            if (volume != tmp.volume) return volume > tmp.volume;
            if (Capacity != tmp.Capacity) return Capacity > tmp.Capacity;
            if (price != tmp.price) return price > tmp.price;
            return Model > tmp.Model;
        }
private:

};

#endif // SAVEDATA_H
