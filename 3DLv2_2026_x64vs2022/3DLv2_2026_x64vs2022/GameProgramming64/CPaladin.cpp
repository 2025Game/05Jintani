#include "CPaladin.h"

#define PALADIN_MODEL "res\\paladin\\Paladin WProp J Nordstrom@Idle.fbx.x"
#define GRAVITY 0.0625f

#define _USE_MATH_DEFINES
#include <math.h>
#include "CCollisionManager.h"
//ラジアンを度数に変換するための定数
const float RAD_TO_DEG = 180.0f / (float)M_PI;


CModelX CPaladin::msModel;

CPaladin::CPaladin(const CVector& pos, const CVector& rot,

	const CVector& scale)
	: mColliderCapsule(this, &mCombinedMatrix, CVector(0.0f, 4.0f, 0.0f),
		CVector(0.0f, 0.0f, 0.0f), 0.5f)

{

	//static変数は初期値の状態で1つだけ作成され削除されない。
	//1つ作成されたらその後初期値の代入はされない。
	static bool first = true;
	if (first)
	{
		msModel.Load(PALADIN_MODEL);
		first = false;
	}
	Init(&msModel);
	mPosition = pos;
	mRotation = rot;
	mScale = scale;

	mpIdle = std::make_unique<CPaladinIdle>(this);
	mpState = mpIdle.get();
	mpState->Start(this);
	mState = mpState->State();
    mpDamage = std::make_unique<CPaladinDamage>(this);
}

void CPaladin::Update()
{
	mPosition = mPosition - CVector(0.0f, GRAVITY, 0.0f);

	CXCharacter::Update();

	mpState->Update();
    //状態の切り替え
    if (mState != mpState->State())
    {
        mState = mpState->State();
        switch (mState)
        {
        case EState::EIDLE:
            mpState = mpIdle.get();
            break;

        case EState::EDAMAGE:
            mpState = mpDamage.get();
            break;
        }
        mpState->Start(this);
    }

	mColliderCapsule.Update();
}

void CPaladin::Collision(CCollider* m, CCollider* o)
{
    mpState->Collision(m, o);
    
    switch (m->Type())
    {
    case CCollider::EType::ECAPSULE:

        // 相手が三角形コライダの場合
        if (o->Type() == CCollider::EType::ETRIANGLE)
        {
            CVector adjust;

            if (CCollider::CollisionTriangleCapsule( o, m,&adjust))
            {
                
                mPosition = CVector() * mMatrix + adjust;

                CVector forward = CVector(0.0f, 0.0f, 1.0f) * mMatrix + adjust;

                if (o->Parent())
                {
                    mPosition =
                        mPosition * o->Parent()->CombinedMatrix().Inverse();
                    
                    forward = forward *
                        o->Parent()->CombinedMatrix().Inverse();
                }

                mRotation = CVector(mRotation.X(),
                    atan2f(forward.X(), forward.Z()) * RAD_TO_DEG,
                    mRotation.Z());

                mpParent = o->Parent();

                CTransform::Update();
            }
        }
        break;

    default:
        break;
    }
}

void CPaladin::Collision()
{
    mColliderCapsule.ChangePriority();

    // 周囲のコライダとの衝突判定
    CCollisionManager::Instance()->Collision(
        &mColliderCapsule, COLLISIONRANGE);
}