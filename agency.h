#ifndef AGENCY_H_
#define AGENCY_H_
#include <iostream>
#include "avl_tree.h"
#include "vehicle_by_type.h"
#include "vehicle_by_sales.h"

class Agency
{
    int agecny_typeID;
    int num_of_agencies;
    Agency* next;
    AvlTree<VehicleByType>* type_tree;
    AvlTree<VehicleBySales>* sales_tree;
public:

    Agency(): agecny_typeID(0), num_of_agencies(0), next(NULL), type_tree(NULL), sales_tree(NULL) {}
    ~Agency()
    {
        if (type_tree != NULL)
            delete type_tree;
        if (sales_tree != NULL)
            delete sales_tree;
    }
    Agency(const Agency& agecny) = default;
    Agency(int agecny_typeID) : agecny_typeID(agecny_typeID), num_of_agencies(1), next(NULL), type_tree(NULL), sales_tree(NULL) {}
    
    void setNext(Agency* next)
    {
        this->next = next;
    }

    Agency* getNext()
    {
        return this->next;
    }

    void setNumOfAgencies(int num_of_agencies)
    {
        this->num_of_agencies = num_of_agencies;
    }

    int getNumOfAgencies()
    {
        return this->num_of_agencies;
    }

    int getAgecnyTypeID()
    {
        return this->agecny_typeID;
    }

    AvlTree<VehicleByType>* getTypeTree()
    {
        return this->type_tree;
    }

    AvlTree<VehicleBySales>* getSalesTree()
    {
        return this->sales_tree;
    }

    void setTypeTree(AvlTree<VehicleByType>* type_tr)
    {
        this->type_tree = type_tr;
    }

    void setSalesTree(AvlTree<VehicleBySales>* sales_tr)
    {
        this->sales_tree = sales_tr; 
    }
};

#endif