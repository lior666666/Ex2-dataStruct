#ifndef VEHICLE_BY_TYPE_H_
#define VEHICLE_BY_TYPE_H_
#include <iostream>

class VehicleByType
{
    int typeID;
    int num_of_sales;
public:

    VehicleByType(): typeID(0), num_of_sales(0) {}
    ~VehicleByType() = default;
    VehicleByType(const VehicleByType& v) = default;
    friend bool operator==(const VehicleByType& v1, const VehicleByType& v2);
    friend bool operator<(const VehicleByType& v1, const VehicleByType& v2);
    VehicleByType(int typeID) : typeID(typeID), num_of_sales(0) {}
    VehicleByType(int typeID, int num_of_sales) : typeID(typeID), num_of_sales(num_of_sales) {}
    
    void addSales(int new_sales)
    {
        this->num_of_sales = this->num_of_sales + new_sales;
    }

    int getTypeID()
    {
        return this->typeID;
    }

    int getNumOfSales()
    {
        return this->num_of_sales;
    }
};

bool operator==(const VehicleByType& v1, const VehicleByType& v2)
{
    return v1.typeID == v2.typeID;
}

bool operator<(const VehicleByType& v1, const VehicleByType& v2)
{
    return v1.typeID < v2.typeID;
}

bool operator>(const VehicleByType& v1, const VehicleByType& v2)
{
    return !(v1 < v2) && !(v1 == v2);
}

#endif