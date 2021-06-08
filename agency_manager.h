#ifndef AGENCY_MANAGER_H_
#define AGENCY_MANAGER_H_
#include <iostream>
#include "avl_tree.h"
#include "vehicle_by_type.h"
#include "vehicle_by_sales.h"
#include "agency.h"

class AgencyManager
{
    int agencies_counter; //start from 0
    Agency** agencies_array;
public:

    AgencyManager(): agencies_counter(0), agencies_array(NULL)
    {
        agencies_array = new Agency*[1];
    }

    ~AgencyManager()
    {
        if (agencies_array != NULL)
            delete[] agencies_array;
    }
    
    void updateAgencyCounter()
    {
        this->agencies_counter = this->agencies_counter + 1;
    }

    int getAgencyCounter()
    {
        return this->agencies_counter;
    }

};

#endif