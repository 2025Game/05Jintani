#include "CPlayerIdle.h"
#include "CXCharacter.h"
//回転速度
#define ROTATIONSPEED 2.0f

void CPlayerIdle::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(0, true, 60);
	mState = EState::EIDLE; //状態の種類を待機にする
}

void CPlayerIdle::Update()
{
	
	if (mInput.Key('D'))
	{
		mState = EState::EWALK;
	}
	
	if (mInput.Key('A'))
	{
		mState = EState::EWALK;
	}

	if (mInput.Key('W'))
	{
		mState = EState::EWALK;
	}

	if (mInput.Key('S'))
	{
		mState = EState::EWALK;
	}

	CVector fwd;
	CVector cfwd;
	//プレイヤーの前方向ベクトルを取得する
	fwd = mpParent->CombinedMatrix().VectorZ();
	//カメラが向いている方向を取得する
	cfwd = CCamera::Instance()->ModelViewInverse().VectorX();
	// 内積を計算して、回転量を求める
	float dx = cfwd.Dot(fwd);
	float dz = fwd.Dot(fwd);
	if (abs(dx) < 0.01f)
	{
		if (dz < 0.0f)
		{
			dx = 1.0f;
		}
	}
	CVector rot(0.0f, dx * 10.0f, 0.0f);
	//プレイヤーをカメラ方向へ回転させる
	mpParent->Rotation(mpParent->Rotation() + rot);

	CCamera::Instance()->Rotation(CCamera::Instance()->Rotation() - rot);

	//スペースでジャンプ
	if (mInput.Key(' '))
	{
		mState = EState::EJUMP;
	}
}
