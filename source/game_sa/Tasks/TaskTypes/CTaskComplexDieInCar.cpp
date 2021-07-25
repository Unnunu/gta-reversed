#include "StdInc.h"

// 0x62FC80
CTaskComplexDieInCar::CTaskComplexDieInCar(eWeaponType nWeaponID)
{
    m_nWeaponID = nWeaponID;
    m_nTimeDrive = 0;
    m_nEq2000 = 0;
    a4 = false;
    a5 = false;
}

CTaskComplexDieInCar* CTaskComplexDieInCar::Constructor(eWeaponType nWeaponID)
{
    this->CTaskComplexDieInCar::CTaskComplexDieInCar(nWeaponID);
    return this;
}

// 0x6375F0
CTask* CTaskComplexDieInCar::CreateFirstSubTask(CPed* ped)
{
    return CreateFirstSubTask_Reversed(ped);
}

// 0x637850
CTask* CTaskComplexDieInCar::CreateNextSubTask(CPed* ped)
{
    return CreateNextSubTask_Reversed(ped);
}

// 0x6377B0
CTask* CTaskComplexDieInCar::ControlSubTask(CPed* ped)
{
    return ControlSubTask_Reversed(ped);
}

// 0x62FCC0
bool CTaskComplexDieInCar::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return MakeAbortable_Reversed(ped, priority, _event);
}

// 0x62FD50
CTask* CTaskComplexDieInCar::CreateSubTask(eTaskType taskType, CPed* ped)
{
    switch (taskType)
    {
    case TASK_SIMPLE_CAR_DRIVE:
        return new CTaskSimpleCarDrive(ped->m_pVehicle, nullptr, false);
    case TASK_SIMPLE_DIE_IN_CAR:
        return new CTaskSimpleDieInCar(ANIM_GROUP_DEFAULT, ped->m_pVehicle->IsDriver(ped) ? ANIM_ID_CAR_DEAD_LHS : ANIM_ID_CAR_DEAD_RHS);
    case TASK_COMPLEX_LEAVE_CAR_AND_DIE:
        return new CTaskComplexLeaveCarAndDie(ped->m_pVehicle, 0, 0);
    default:
        return nullptr;
    }
}

// 0x62FD00
void CTaskComplexDieInCar::PreparePedVehicleForPedDeath(CVehicle* pVehicle)
{
    if (pVehicle->m_nStatus = STATUS_SIMPLE)
        CCarCtrl::SwitchVehicleToRealPhysics(pVehicle);

    pVehicle->m_autoPilot.m_nCruiseSpeed = 0;
    pVehicle->m_autoPilot.m_nCarMission = MISSION_NONE;
    pVehicle->m_autoPilot.m_nTempAction = 6;
    pVehicle->m_autoPilot.m_nTempActionTime = CTimer::m_snTimeInMilliseconds + 2000;
}

CTask* CTaskComplexDieInCar::CreateFirstSubTask_Reversed(CPed* ped)
{
    ped->SetPedState(PEDSTATE_DIE);

    auto pEvent = ped->GetIntelligence()->m_eventHandler.m_history.GetCurrentEvent();
    if (pEvent && pEvent->GetEventType() == EVENT_DAMAGE)
    {
        auto pDriver = ped->m_pVehicle->m_pDriver;
        if (pDriver && pDriver != ped)
        {
            CEventDamage* pEventCopy = static_cast<CEventDamage*>(pEvent->Clone());
            pEventCopy->m_bAddToEventGroup = false;
            pDriver->GetIntelligence()->m_eventGroup.Add(pEventCopy, false);
            delete pEventCopy;
        }

        for (unsigned int i = 0; i < ped->m_pVehicle->m_nMaxPassengers; i++)
        {
            auto pPassenger = ped->m_pVehicle->m_apPassengers[i];
            if (pPassenger && pPassenger != ped)
            {
                CEventDamage* pEventCopy = static_cast<CEventDamage*>(pEvent->Clone());
                pEventCopy->m_bAddToEventGroup = false;
                pPassenger->GetIntelligence()->m_eventGroup.Add(pEventCopy, false);
                delete pEventCopy;
            }
        }
    }

    if (ped->bForceDieInCar || m_nWeaponID == WEAPON_EXPLOSION)
        return CreateSubTask(TASK_SIMPLE_DIE_IN_CAR, ped);

    auto nVehicleSubType = ped->m_pVehicle->m_vehicleSubType;
    if (nVehicleSubType == VEHICLE_HELI || nVehicleSubType == VEHICLE_PLANE)
        return CreateSubTask(TASK_SIMPLE_DIE_IN_CAR, ped);

    if (ped->m_pVehicle->CanPedStepOutCar(false))
        return CreateSubTask(TASK_COMPLEX_LEAVE_CAR_AND_DIE, ped);

    if (ped->m_pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_AUTOMOBILE && ped->m_pVehicle->m_pDriver == ped)
    {
        PreparePedVehicleForPedDeath(ped->m_pVehicle);
        m_nTimeDrive = CTimer::m_snTimeInMilliseconds;
        m_nEq2000 = 2000;
        a4 = true;
        return CreateSubTask(TASK_SIMPLE_CAR_DRIVE, ped);
    }

    return CreateSubTask(TASK_SIMPLE_DIE_IN_CAR, ped);
}

CTask* CTaskComplexDieInCar::CreateNextSubTask_Reversed(CPed* ped)
{
    auto subTaskType = m_pSubTask->GetId();

    if (subTaskType == TASK_SIMPLE_DIE_IN_CAR)
        return CreateSubTask(TASK_FINISHED, ped);
    else if (subTaskType == TASK_COMPLEX_LEAVE_CAR_AND_DIE)
        return CreateSubTask(ped->m_pVehicle && ped->bInVehicle ? TASK_SIMPLE_DIE_IN_CAR : TASK_FINISHED, ped);

    return nullptr;
}

CTask* CTaskComplexDieInCar::ControlSubTask_Reversed(CPed* ped)
{
    auto subTaskType = m_pSubTask->GetId();

    if (subTaskType == TASK_SIMPLE_CAR_DRIVE && a4)
    {
        if (a5)
        {
            m_nTimeDrive = CTimer::m_snTimeInMilliseconds;
            a5 = false;
        }

        if (CTimer::m_snTimeInMilliseconds >= m_nTimeDrive + m_nEq2000)
        {
             
            return CreateSubTask(ped->IsCreatedBy(PED_MISSION) && ped->m_pVehicle->CanPedStepOutCar(false) ? TASK_COMPLEX_LEAVE_CAR_AND_DIE : TASK_SIMPLE_DIE_IN_CAR, ped);
        }
    }

    return m_pSubTask;
}

bool CTaskComplexDieInCar::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    if (priority == ABORT_PRIORITY_URGENT || priority == ABORT_PRIORITY_IMMEDIATE)
        return m_pSubTask->MakeAbortable(ped, priority, _event);
    else
        return false;
}
