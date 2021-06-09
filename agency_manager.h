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
    Agency** head_agencies_array;
    int agencies_array_length; 
    int head_agencies_array_length; 
    int head_agencies_counter; 

public:

    AgencyManager(): agencies_counter(0), agencies_array(NULL),head_agencies_array(NULL) ,agencies_array_length(0), head_agencies_array_length(0), head_agencies_counter(0)
    {
        agencies_array = new Agency*[1];
        head_agencies_array = new Agency*[1]; 
    }

    ~AgencyManager()
    {
        if (agencies_array != NULL)
            delete[] agencies_array;
        if (head_agencies_array != NULL)
            delete[] head_agencies_array;
    }
    StatusType UniteAgencies(int agencyID1, int agencyID2)
    {
        // !!!!check input in the library !!!
        if(agencyID1>agencies_counter || agencyID2>agencies_counter)
            return FAILURE;
        Agency* temp1 =  head_agencies_array[agencyID1];
        Agency* temp2 =  head_agencies_array[agencyID2];
        AvlTree<VehicleBySales>* old_sales_tree1 = temp1->getSalesTree(); 
        AvlTree<VehicleByType>* old_types_tree1 = temp1->getTypeTree(); 
        AvlTree<VehicleBySales>* old_sales_tree2 = temp2->getSalesTree(); 
        AvlTree<VehicleByType>* old_types_tree2 = temp2->getTypeTree(); 
        AvlTree<VehicleBySales>* merged_sales_tree =  old_sales_tree1->merge(old_sales_tree2); // O(n+m)
        AvlTree<VehicleByType>* merged_types_tree =  old_types_tree1->merge(old_types_tree2); // O(n+m)
        delete old_sales_tree1; 
        delete old_types_tree1; 
        delete old_sales_tree2; 
        delete old_types_tree2; 
        if(temp1->getNumOfAgencies()<= temp2->getNumOfAgencies())
        {
            temp1->setNext(temp2);
            head_agencies_array[agencyID1] = head_agencies_array[agencyID2];
            temp2->setNumOfAgencies(temp1->getNumOfAgencies() + temp2->getNumOfAgencies());
            temp1->setNumOfAgencies(0);
            temp1->setSalesTree(NULL);
            temp1->setTypeTree(NULL);
            temp2->setSalesTree(merged_sales_tree);
            temp2->setTypeTree(merged_types_tree);
        }
        else
        {
            temp2->setNext(temp1);
            head_agencies_array[agencyID2] = head_agencies_array[agencyID1];
            temp1->setNumOfAgencies(temp1->getNumOfAgencies() + temp2->getNumOfAgencies());
            temp2->setNumOfAgencies(0);
            temp2->setSalesTree(NULL);
            temp2->setTypeTree(NULL);
            temp1->setSalesTree(merged_sales_tree);
            temp1->setTypeTree(merged_types_tree);
        }
        head_agencies_counter--;
        return SUCCESS;        
    }


    Agency* find(int agencyID)
    {
        Agency* temp = agencies_array[agencyID];
        while(temp->getNext() != NULL) // find the head of the group.
        {
            temp = temp->getNext();
        }
        Agency* temp2 = agencies_array[agencyID];
        Agency* next_temp = temp2->getNext(); 
        while(next_temp != NULL) // update all routes to the head. 
        {
            temp2->getNext() = temp; 
            temp2 = next_temp; 
            next_temp = next_temp->getNext();
        }   
        return temp;      
    }

    StatusType GetIthSoldType(int agencyID, int i, int* res)
    {
        // !!!!check for input in the library !!! 
        if(agencyID>agencies_counter)
            return FAILURE;
        Agency* group_head = find(agencyID); //log*(n)
        AvlTree<VehicleBySales>* model_node = group_head->getSalesTree()->getNumber(i); // log(m)
        if(model_node == NULL)
            return FAILURE; 
        res* = model_node->getData().getTypeID();
        return SUCCESS;
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
© 2021 GitHub, Inc.