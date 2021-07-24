#pragma once
#include "CTaskSimple.h"

class CTaskSimpleDie;

class CTaskSimpleDieInCar : public CTaskSimpleDie
{
public:
    static void InjectHooks();

    CTaskSimpleDieInCar(eAnimGroup nAnimGroup, eAnimID nAnimID);
    ~CTaskSimpleDieInCar() override {}

private:
    CTaskSimpleDieInCar* Constructor(eAnimGroup nAnimGroup, eAnimID nAnimID);

public:
    CTask* Clone() override { return new CTaskSimpleDieInCar(m_nAnimGroup, m_nAnimID); }
    eTaskType GetId() override { return TASK_SIMPLE_DIE_IN_CAR; }
};

VALIDATE_SIZE(CTaskSimpleDie, 0x28);
