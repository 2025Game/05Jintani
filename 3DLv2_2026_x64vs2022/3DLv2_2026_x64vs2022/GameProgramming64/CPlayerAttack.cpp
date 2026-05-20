#include "CPlayerAttack.h"

void CPlayerAttack::Start(CXCharacter* parent)
{
	//親ポインタを保存
	mpParent = parent;
	//アニメーションを変更
	mpParent->ChangeAnimation(3, false, 30);
	mState = EState::EATTACK; //状態を攻撃にする
	// 硬直時間
	mStopTimer = 20;
}

void CPlayerAttack::Update()
{
	//アニメーション䛜終了䛧䛶いる䛛
	if (mpParent->IsAnimationFinished())
	{
		mStopTimer--;

		if (mStopTimer <= 0)
		{
			mState = EState::EIDLE;
		}
	}
}