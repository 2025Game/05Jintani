#include "CPlayerIdle.h"
#include "CXCharacter.h"
//回転速度
#define ROTATIONSPEED 2.0f
void CPlayerIdle::Start(CXCharacter* parent)
{
	//親?ポインタを保存
	mpParent = parent;
	//アニメーション?変更
	mpParent->ChangeAnimation(0, true, 60);
	mState = EState::EIDLE; //状態?種類を待機?する
}
void CPlayerIdle::Update()
{
	//Aキー?左回転、Dキー?右回転
	if (mInput.Key('D'))
	{
		CVector r = mpParent->Rotation() +
			CVector(0.0f, -ROTATIONSPEED, 0.0f);
		mpParent->Rotation(r);
	}
	else if (mInput.Key('A'))
	{
		CVector r = mpParent->Rotation() +
			CVector(0.0f, ROTATIONSPEED, 0.0f);
		mpParent->Rotation(r);
	}
}