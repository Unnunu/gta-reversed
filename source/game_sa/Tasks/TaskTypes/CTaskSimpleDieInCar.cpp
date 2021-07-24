#include "StdInc.h"

void CTaskSimpleDieInCar::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleDieInCar", "Constructor", 0x62FC20, &CTaskSimpleDieInCar::Constructor);
}

// 0x62FC20
CTaskSimpleDieInCar::CTaskSimpleDieInCar(eAnimGroup nAnimGroup, eAnimID nAnimID) : CTaskSimpleDie(nAnimGroup, nAnimID, 4.0F, 0.0F)
{
    //nothing here
}

CTaskSimpleDieInCar* CTaskSimpleDieInCar::Constructor(eAnimGroup nAnimGroup, eAnimID nAnimID)
{
    this->CTaskSimpleDieInCar::CTaskSimpleDieInCar(nAnimGroup, nAnimID);
    return this;
}
