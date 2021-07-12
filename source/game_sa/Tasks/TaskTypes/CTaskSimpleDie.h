#include "CTaskSimple.h"

class CTaskSimpleDie : public CTaskSimple
{
public:
    eAnimGroup m_nAnimGroup;
    eAnimID m_nAnimID;
    CAnimBlendHierarchy* m_pAnimHierarchy;
    unsigned int m_nAnimFlags;
    float m_fBlendDelta;
    float m_fAnimSpeed;
    union {
        unsigned char m_nFlags;
        struct
        {
            unsigned char bAnimFinished : 1;
            unsigned char bDeathEventGenerated : 1;
        };
    };
    char _pad[3];
    CAnimBlendAssociation* m_pAnim;

    static void InjectHooks();

    CTaskSimpleDie(eAnimGroup nAnimGroup, eAnimID nAnimID, float fBlendDelta, float fAnimSpeed);
    CTaskSimpleDie(const char* animName, const char* animBlockName, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed);
    CTaskSimpleDie(CAnimBlendHierarchy* pAnimHierarchy, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed);

private:
    CTaskSimpleDie* Constructor(eAnimGroup nAnimGroup, eAnimID nAnimID, float fBlendDelta, float fAnimSpeed);
    CTaskSimpleDie* Constructor2(const char* animName, const char* animBlockName, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed);
    CTaskSimpleDie* Constructor3(CAnimBlendHierarchy* pAnimHierarchy, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed);

public:
    ~CTaskSimpleDie() override;
    eTaskType GetId() override { return TASK_SIMPLE_DIE; }
    CTask* Clone() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    bool ProcessPed(CPed* ped) override;
    void StartAnim(CPed* ped);
    static void FinishAnimDieCB(CAnimBlendAssociation* pAnim, void* data);

    CTask* Clone_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);
    bool ProcessPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleDie, 0x28);
