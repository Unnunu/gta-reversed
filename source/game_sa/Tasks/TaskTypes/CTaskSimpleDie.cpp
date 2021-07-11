#include "StdInc.h"

// 0x62FA00
CTaskSimpleDie::CTaskSimpleDie(eAnimGroup nAnimGroup, eAnimID nAnimID, float fBlendDelta, float fAnimSpeed)
{
    m_nAnimGroup = nAnimGroup;
    m_nAnimID = nAnimID;
    m_fBlendDelta = fBlendDelta;
    m_fAnimSpeed = fAnimSpeed;
    b1 = false;
    b2 = false;
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
    b1 = false;
    b2 = false;
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
    b1 = false;
    b2 = false;
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
