#ifndef VEHICLE_BY_SALES_H_
#define VEHICLE_BY_SALES_H_
#include <iostream>

class VehicleBySales
{
    int typeID;
    int num_of_sales;
public:

    VehicleBySales(): typeID(0), num_of_sales(0) {}
    ~VehicleBySales() = default;
    VehicleBySales(const VehicleBySales& v) = default;
    friend bool operator==(const VehicleBySales& v1, const VehicleBySales& v2);
    friend bool operator<(const VehicleBySales& v1, const VehicleBySales& v2);
    VehicleBySales(int typeID) : typeID(typeID), num_of_sales(0) {}
    VehicleBySales(int typeID, int num_of_sales) : typeID(typeID), num_of_sales(num_of_sales) {}
    
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

bool operator==(const VehicleBySales& v1, const VehicleBySales& v2)
{
    return (v1.num_of_sales == v2.num_of_sales) && (v1.typeID == v2.typeID);
}

bool operator<(const VehicleBySales& v1, const VehicleBySales& v2)
{
    if (v1.num_of_sales == v2.num_of_sales)
        return v1.typeID < v2.typeID;
    return v1.num_of_sales < v2.num_of_sales;
}

bool operator>(const VehicleBySales& v1, const VehicleBySales& v2)
{
    return !(v1 < v2) && !(v1 == v2);
}

#endif