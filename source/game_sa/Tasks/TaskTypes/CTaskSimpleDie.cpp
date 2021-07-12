#include "StdInc.h"

void CTaskSimpleDie::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleDie", "Constructor", 0x62FA00, &CTaskSimpleDie::Constructor);
    ReversibleHooks::Install("CTaskSimpleDie", "Constructor2", 0x62FA60, &CTaskSimpleDie::Constructor2);
    ReversibleHooks::Install("CTaskSimpleDie", "Constructor3", 0x62FAF0, &CTaskSimpleDie::Constructor3);
    ReversibleHooks::Install("CTaskSimpleDie", "StartAnim", 0x637520, &CTaskSimpleDie::StartAnim);
    ReversibleHooks::Install("CTaskSimpleDie", "FinishAnimDieCB", 0x62FC10, &CTaskSimpleDie::FinishAnimDieCB);
    //VTABLE
    ReversibleHooks::Install("CTaskSimpleDie", "Clone", 0x635DA0, &CTaskSimpleDie::Clone_Reversed);
    ReversibleHooks::Install("CTaskSimpleDie", "MakeAbortable", 0x62FBA0, &CTaskSimpleDie::MakeAbortable_Reversed);
    ReversibleHooks::Install("CTaskSimpleDie", "ProcessPed", 0x6397E0, &CTaskSimpleDie::ProcessPed_Reversed);
}

// 0x62FA00
CTaskSimpleDie::CTaskSimpleDie(eAnimGroup nAnimGroup, eAnimID nAnimID, float fBlendDelta, float fAnimSpeed)
{
    m_nAnimGroup = nAnimGroup;
    m_nAnimID = nAnimID;
    m_fBlendDelta = fBlendDelta;
    m_fAnimSpeed = fAnimSpeed;
    bAnimFinished = false;
    bDeathEventGenerated = false;
    m_pAnimHierarchy = nullptr;
    m_nAnimFlags = 0;
    m_pAnim = nullptr;
}

// 0x62FA60
CTaskSimpleDie::CTaskSimpleDie(const char* animName, const char* animBlockName, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed)
{
    m_nAnimGroup = ANIM_GROUP_DEFAULT;
    m_nAnimID = ANIM_ID_KO_SHOT_FRONT_0;
    m_fBlendDelta = fBlendDelta;
    m_fAnimSpeed = fAnimSpeed;
    bAnimFinished = false;
    bDeathEventGenerated = false;
    m_pAnimHierarchy = CAnimManager::GetAnimation(animName, CAnimManager::GetAnimationBlock(animBlockName));
    m_nAnimFlags = nAnimFlags;
    m_pAnim = nullptr;
}

// 0x62FAF0
CTaskSimpleDie::CTaskSimpleDie(CAnimBlendHierarchy* pAnimHierarchy, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed)
{
    m_nAnimGroup = ANIM_GROUP_DEFAULT;
    m_nAnimID = ANIM_ID_KO_SHOT_FRONT_0;
    m_fBlendDelta = fBlendDelta;
    m_fAnimSpeed = fAnimSpeed;
    bAnimFinished = false;
    bDeathEventGenerated = false;
    m_pAnimHierarchy = pAnimHierarchy;
    m_nAnimFlags = nAnimFlags;
    m_pAnim = nullptr;
}

CTaskSimpleDie* CTaskSimpleDie::Constructor(eAnimGroup nAnimGroup, eAnimID nAnimID, float fBlendDelta, float fAnimSpeed)
{
    this->CTaskSimpleDie::CTaskSimpleDie(nAnimGroup, nAnimID, fBlendDelta, fAnimSpeed);
    return this;
}

CTaskSimpleDie* CTaskSimpleDie::Constructor2(const char* animName, const char* animBlockName, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed)
{
    this->CTaskSimpleDie::CTaskSimpleDie(animName, animBlockName, nAnimFlags, fBlendDelta, fAnimSpeed);
    return this;
}

CTaskSimpleDie* CTaskSimpleDie::Constructor3(CAnimBlendHierarchy* pAnimHierarchy, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed)
{
    this->CTaskSimpleDie::CTaskSimpleDie(pAnimHierarchy, nAnimFlags, fBlendDelta, fAnimSpeed);
    return this;
}

// 0x62FB40
CTaskSimpleDie::~CTaskSimpleDie()
{
    if (m_pAnim)
        m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
}

// 0x635DA0
CTask* CTaskSimpleDie::Clone()
{
    return Clone_Reversed();
}

// 0x62FBA0
bool CTaskSimpleDie::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return MakeAbortable_Reversed(ped, priority, _event);
}

// 0x6397E0
bool CTaskSimpleDie::ProcessPed(CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

// 0x637520
void CTaskSimpleDie::StartAnim(CPed* ped)
{
    if (m_pAnimHierarchy)
        m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, m_pAnimHierarchy, m_nAnimFlags, m_fBlendDelta);
    else
        m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, m_nAnimGroup, m_nAnimID, m_fBlendDelta);

    m_pAnim->SetFinishCallback(FinishAnimDieCB, this);
    m_pAnim->m_nFlags &= ~ANIM_FLAG_UNLOCK_LAST_FRAME;
    if (m_fAnimSpeed > 0.0F)
        m_pAnim->m_fSpeed = m_fAnimSpeed;

    ped->ClearAll();
    ped->m_fHealth = 0.0F;
    ped->StopNonPartialAnims();
    ped->m_nDeathTime = CTimer::m_snTimeInMilliseconds;
}

// 0x62FC10
void CTaskSimpleDie::FinishAnimDieCB(CAnimBlendAssociation* pAnim, void* data)
{
    auto pTask = reinterpret_cast<CTaskSimpleDie*>(data);
    pTask->bAnimFinished = true;
    pTask->m_pAnim = nullptr;
}

CTask* CTaskSimpleDie::Clone_Reversed()
{
    if (m_pAnimHierarchy)
        return new CTaskSimpleDie(m_pAnimHierarchy, m_nAnimFlags, m_fBlendDelta, m_fAnimSpeed);
    else
        return new CTaskSimpleDie(m_nAnimGroup, m_nAnimID, m_fBlendDelta, m_fAnimSpeed);
}

bool CTaskSimpleDie::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    if (priority == ABORT_PRIORITY_IMMEDIATE)
    {
        if (m_pAnim)
            m_pAnim->m_fBlendDelta = -1000.0F;

        ped->SetPedState(PEDSTATE_IDLE);
        ped->SetMoveState(PEDMOVE_STILL);
        ped->SetMoveAnim();
        ped->bIsDyingStuck = false;
        return true;
    }
    else if (_event && _event->GetEventType() == EVENT_DEATH)
    {
        ped->bIsDyingStuck = false;
        return true;
    }
    else
        return false;
}

bool CTaskSimpleDie::ProcessPed_Reversed(CPed* ped)
{
    ped->m_pedIK.bSlopePitch = true;

    if (bAnimFinished || m_nAnimID == ANIM_ID_NO_ANIMATION_SET)
    {
        ped->bIsDyingStuck = true;
        if (!bDeathEventGenerated)
        {
            if (ped->physicalFlags.bSubmergedInWater
                || !ped->m_bUsesCollision
                || ped->physicalFlags.bDontApplySpeed
                || ped->bIsStanding && (ped->IsPlayer() || !ped->m_standingOnEntity || ped->m_standingOnEntity->AsPhysical()->physicalFlags.bDisableCollisionForce)
                )
            {
                CEventDeath eventDeath(m_nAnimID == ANIM_ID_DROWN);
                ped->GetIntelligence()->m_eventGroup.Add(&eventDeath, false);
                bDeathEventGenerated = true;
                ped->bIsDyingStuck = false;
            }
        }
    }
    else if (!m_pAnim)
    {
        StartAnim(ped);
        ped->SetPedState(PEDSTATE_DIE);
    }

    return false;
}
