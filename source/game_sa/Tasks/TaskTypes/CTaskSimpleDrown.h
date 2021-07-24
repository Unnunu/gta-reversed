#pragma once
#include "CTaskSimple.h"

class CTaskSimpleDie;

class CTaskSimpleDrown : public CTaskSimpleDie
{
public:
    bool m_bIsAlive;
    unsigned char _pad_29[3];

    static void InjectHooks();

    CTaskSimpleDrown();
    ~CTaskSimpleDrown() override {}

private:
    CTaskSimpleDrown* Constructor();

public:
    CTask* Clone() override { return new CTaskSimpleDrown(); }
    eTaskType GetId() override { return TASK_SIMPLE_DROWN; }
    bool ProcessPed(CPed* ped) override;

    bool ProcessPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleDrown, 0x2C);
