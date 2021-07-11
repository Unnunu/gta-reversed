#include "CTaskSimple.h"

//class CAnimBlendHierarchy;
//class CAnimBlendAssociation;

class CTaskSimpleDie : public CTaskSimple
{
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
            unsigned char b1 : 1;
            unsigned char b2 : 1;
        };
    };
    char _pad[3];
    CAnimBlendAssociation* m_pAnim;

    CTaskSimpleDie(eAnimGroup nAnimGroup, eAnimID nAnimID, float fBlendDelta, float fAnimSpeed);
    CTaskSimpleDie(const char* animName, const char* animBlockName, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed);
    CTaskSimpleDie(CAnimBlendHierarchy* pAnimHierarchy, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed);

private:
    CTaskSimpleDie* Constructor(eAnimGroup nAnimGroup, eAnimID nAnimID, float fBlendDelta, float fAnimSpeed);
    CTaskSimpleDie* Constructor2(const char* animName, const char* animBlockName, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed);
    CTaskSimpleDie* Constructor3(CAnimBlendHierarchy* pAnimHierarchy, unsigned int nAnimFlags, float fBlendDelta, float fAnimSpeed);

public:
    ~CTaskSimpleDie() override;
};

VALIDATE_SIZE(CTaskSimpleDie, 0x28);
