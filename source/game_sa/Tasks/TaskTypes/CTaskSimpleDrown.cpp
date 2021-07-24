#include "StdInc.h"

void CTaskSimpleDrown::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleDrown", "Constructor", 0x62FEC0, &CTaskSimpleDrown::Constructor);
    //VTABLE
    ReversibleHooks::Install("CTaskSimpleDrown", "ProcessPed", 0x639900, &CTaskSimpleDrown::ProcessPed_Reversed);
}

// 0x62FEC0
CTaskSimpleDrown::CTaskSimpleDrown() : CTaskSimpleDie(ANIM_GROUP_DEFAULT, ANIM_ID_DROWN, 4.0F, 0.0F)
{
    m_bIsAlive = true;
}

CTaskSimpleDrown* CTaskSimpleDrown::Constructor()
{
    this->CTaskSimpleDrown::CTaskSimpleDrown();
    return this;
}

// 0x639900
bool CTaskSimpleDrown::ProcessPed(CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

bool CTaskSimpleDrown::ProcessPed_Reversed(CPed* ped)
{
    if (m_bIsAlive)
    {
        ped->SetPedState(PEDSTATE_DIE);
        ped->bIsInTheAir = false;
        if (ped == FindPlayerPed())
            CStats::IncrementStat(STAT_TIMES_DROWNED, 1.0F);
        m_bIsAlive = false;
    }

    return CTaskSimpleDie::ProcessPed(ped);
}
