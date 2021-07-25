#pragma once
#include "CTaskComplex.h"

class CTaskComplexDieInCar : public CTaskComplex
{
public:
    eWeaponType m_nWeaponID;
    int m_nTimeDrive;
    int m_nEq2000;
    bool a4;
    bool a5;
    unsigned char _pad[2];

    static void InjectHooks();

    CTaskComplexDieInCar(eWeaponType nWeaponID);
    ~CTaskComplexDieInCar() override {}

private:
    CTaskComplexDieInCar* Constructor(eWeaponType nWeaponID);

public:
    CTask* Clone() override { return new CTaskComplexDieInCar(m_nWeaponID); }
    eTaskType GetId() override { return TASK_COMPLEX_DIE_IN_CAR; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
    void PreparePedVehicleForPedDeath(CVehicle* pVehicle);

    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);
};
