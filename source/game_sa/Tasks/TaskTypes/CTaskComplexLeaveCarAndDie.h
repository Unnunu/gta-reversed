#pragma once
#include "CTaskComplex.h"
class CTaskComplexLeaveCar;

class CTaskComplexLeaveCarAndDie : public CTaskComplexLeaveCar
{
public:
    CTaskComplexLeaveCarAndDie(CVehicle* pTargetVehicle, int nTargetDoor, int nDelayTime);
    ~CTaskComplexLeaveCarAndDie() override {}

    CTask* Clone() override { return new CTaskComplexLeaveCarAndDie(m_pTargetVehicle, m_nTargetDoor, m_nDelayTime); }
    eTaskType GetId() override { return TASK_COMPLEX_LEAVE_CAR_AND_DIE; }
    CTask* CreateFirstSubTask(CPed* ped) override;
};

VALIDATE_SIZE(CTaskComplexLeaveCarAndDie, 0x34);
