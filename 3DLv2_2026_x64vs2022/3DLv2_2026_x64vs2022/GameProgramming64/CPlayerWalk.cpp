#include "CPlayerWalk.h"

//移動速度
#define VELOCITY 0.1f
//回転速度
#define ROTATIONSPEED 2.0f


void CPlayerWalk::Start(CXCharacter* parent)
{
	//親䛾ポインタを保存
	mpParent = parent;
	//アニメーション䛾変更
	mpParent->ChangeAnimation(1, true, 60);
	mState = EState::EWALK; //状態䛾種類を歩く䛻する
}

void CPlayerWalk::Update()
{
	if (mInput.Key('W'))
	{
		CVector p = mpParent->Position();
		mpParent->Position(p +
			mpParent->MatrixRotate().VectorZ() * VELOCITY);
	}
	else
	{
		//Wキーが押され䛶い䛺い䛸き䛿待機状態䛻する
		mState = EState::EIDLE;
	}
	// Aで左回転
	if (mInput.Key('A'))
	{
		CVector r = mpParent->Rotation() +
			CVector(0.0f, ROTATIONSPEED, 0.0f);
		mpParent->Rotation(r);
	}

	// Dで右回転
	if (mInput.Key('D'))
	{
		CVector r = mpParent->Rotation() +
			CVector(0.0f, -ROTATIONSPEED, 0.0f);
		mpParent->Rotation(r);
	}
}

