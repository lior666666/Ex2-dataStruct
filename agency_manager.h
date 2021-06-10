#ifndef AGENCY_MANAGER_H_
#define AGENCY_MANAGER_H_
#include <iostream>
#include "avl_tree.h"
#include "library2.h"
#include "vehicle_by_type.h"
#include "vehicle_by_sales.h"
#include "agency.h"

class AgencyManager
{
    int agencies_counter; //start from 0
    int head_agencies_counter; //start from 0
    Agency** agencies_array;
    int agencies_array_length;
    Agency** head_agencies_array;
    int head_agencies_array_length;
public:

    AgencyManager(): agencies_counter(0), head_agencies_counter(0), agencies_array(NULL),
                    agencies_array_length(1), head_agencies_array(NULL), head_agencies_array_length(1)
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

    StatusType AddAgency()
    {
        Agency* new_agency = new Agency(agencies_counter);
        agencies_array[agencies_counter] = new_agency;
        head_agencies_array[head_agencies_counter] = new_agency;
        agencies_counter++;
        head_agencies_counter++;
        if (agencies_counter == agencies_array_length) // multiply the dynamic agencies array
        {
            Agency** new_agencies_array = new Agency*[2*agencies_array_length];
            for (int i = 0; i < agencies_array_length; i++)
            {
                new_agencies_array[i] = agencies_array[i];
            }
            delete[] agencies_array;
            agencies_array = new_agencies_array;
            agencies_array_length = 2*agencies_array_length;
        }
        if (head_agencies_counter == head_agencies_array_length) // multiply the dynamic head agencies array
        {
            Agency** new_head_agencies_array = new Agency*[2*head_agencies_array_length];
            for (int i = 0; i < head_agencies_array_length; i++)
            {
                new_head_agencies_array[i] = head_agencies_array[i];
            }
            delete[] head_agencies_array;
            head_agencies_array = new_head_agencies_array;
            head_agencies_array_length = 2*head_agencies_array_length;
        }
        return SUCCESS;
    }

    StatusType SellCar(int agencyID, int typeID, int k)
    {
        if (agencyID >= agencies_counter)
            return FAILURE;
        Agency* agency = find(agencyID); // log*n
        if (agency == NULL)
            return FAILURE;
        AvlTree<VehicleByType>* agency_type_tree = agency->getTypeTree();
        VehicleByType demmy_vehicle = VehicleByType(typeID);
        VehicleByType* typeID_vehicle = agency_type_tree->getNodeData(demmy_vehicle); // log m
        if (typeID_vehicle != NULL) //there is such a typeID in the tree --> update the sales
        {
            typeID_vehicle->addSales(k);
        }
        else //no typeID in the tree --> need to create new typeID
        {
            VehicleByType new_vehicle = VehicleByType(typeID, k);
            agency_type_tree->insertElement(new_vehicle); // log m
        }
        return SUCCESS;
    }

    StatusType UniteAgencies(int agencyID1, int agencyID2)
    {
        if(agencyID1 >= agencies_counter || agencyID2 >= agencies_counter)
            return FAILURE;
        Agency* temp1 = head_agencies_array[agencyID1];
        Agency* temp2 = head_agencies_array[agencyID2];
        AvlTree<VehicleBySales>* old_sales_tree1 = temp1->getSalesTree(); 
        AvlTree<VehicleByType>* old_types_tree1 = temp1->getTypeTree(); 
        AvlTree<VehicleBySales>* old_sales_tree2 = temp2->getSalesTree(); 
        AvlTree<VehicleByType>* old_types_tree2 = temp2->getTypeTree(); 
        AvlTree<VehicleBySales>* merged_sales_tree =  old_sales_tree1->merge(old_sales_tree2); // O(m1+m2)
        AvlTree<VehicleByType>* merged_types_tree =  old_types_tree1->merge(old_types_tree2); // O(m1+m2)
        delete old_sales_tree1; 
        delete old_types_tree1; 
        delete old_sales_tree2; 
        delete old_types_tree2; 
        if(temp1->getNumOfAgencies() <= temp2->getNumOfAgencies()) // temp2 bigger so unite the trees to it
        {
            temp1->setNext(temp2);
            head_agencies_array[agencyID1] = head_agencies_array[agencyID2]; // update the new head of the group
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
            head_agencies_array[agencyID2] = head_agencies_array[agencyID1]; // update the new head of the group
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
            temp2->setNext(temp); 
            temp2 = next_temp; 
            next_temp = next_temp->getNext();
        }   
        return temp;      
    }

    StatusType GetIthSoldType(int agencyID, int i, int* res)
    {
        if(agencyID >= agencies_counter)
            return FAILURE;
        Agency* group_head = find(agencyID); //log*(n)
        AvlTree<VehicleBySales>* model_node = group_head->getSalesTree()->getNumber(i); // log(m)
        if(model_node == NULL)
            return FAILURE; 
        *res = model_node->getData().getTypeID();
        return SUCCESS;
    }
};

#endif