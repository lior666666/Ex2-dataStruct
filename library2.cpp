#include "agency_manager.h"

void *Init()
{
	try {
        AgencyManager* DS = new AgencyManager();
        return (void*)DS;
    }
    catch (std::bad_alloc& e) {
        return NULL;
    }
}

StatusType AddAgency(void *DS)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    StatusType status;
	try {
        status = ((AgencyManager*)DS)->AddAgency();
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    return status;
}

StatusType SellCar(void *DS, int agencyID, int typeID, int k)
{
    if (DS == NULL || agencyID < 0 || k <= 0)
    {
        return INVALID_INPUT;
    }
    StatusType status;
	try {
        status = ((AgencyManager*)DS)->SellCar(agencyID, typeID, k);
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    return status;
}

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2)
{
    if (DS == NULL || agencyID1 < 0 || agencyID2 < 0)
    {
        return INVALID_INPUT;
    }
    StatusType status;
	try {
        status = ((AgencyManager*)DS)->UniteAgencies(agencyID1, agencyID2);
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    return status;
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res)
{
    if (DS == NULL || res == NULL || agencyID < 0 || i < 0)
    {
        return INVALID_INPUT;
    }
    StatusType status;
	try {
        status = ((AgencyManager*)DS)->GetIthSoldType(agencyID, i, res);
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    return status;
}

void Quit(void** DS)
{
    delete *((AgencyManager**)DS);
    *DS = NULL;
}