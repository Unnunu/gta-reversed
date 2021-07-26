#include "StdInc.h"

CTaskComplexLeaveCarAndDie::CTaskComplexLeaveCarAndDie(CVehicle* pTargetVehicle, int nTargetDoor, int nDelayTime) : CTaskComplexLeaveCar(pTargetVehicle, nTargetDoor, nDelayTime, false, true)
{
    m_bDie = true;
}

CTask* CTaskComplexLeaveCarAndDie::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x642280, CTask*, CPed*>(this, ped);
}
