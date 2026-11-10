#include "CPlayerWalk.h"

//移動速度
#define VELOCITY 0.1f
//回転速度
#define ROTATIONSPEED 2.0f

void CPlayerWalk::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(1, true, 60);
	mState = EState::EWALK; //状態の種類を歩くにする
}

void CPlayerWalk::Update()
{
	//進行すべき前方向のベクトルを取得する
	CVector cz;
	//．カメラの右方向ベクトルを取得する
	CVector cx;

	if (mInput.Key('W'))
	{
		cx = CCamera::Instance()->ModelViewInverse().VectorX();
		cz = CCamera::Instance()->ModelViewInverse().VectorZ() * -1;
	}

	if (mInput.Key('S'))
	{
		cx = CCamera::Instance()->ModelViewInverse().VectorX() * -1;
		cz = CCamera::Instance()->ModelViewInverse().VectorZ();
	}

	if (mInput.Key('A'))
	{
		cx = CCamera::Instance()->ModelViewInverse().VectorZ() * -1;
		cz = CCamera::Instance()->ModelViewInverse().VectorX() * -1;
	}

	if (mInput.Key('D'))
	{
		cx = CCamera::Instance()->ModelViewInverse().VectorZ();
		cz = CCamera::Instance()->ModelViewInverse().VectorX();
	}

	if (mInput.Key('W')
		|| mInput.Key('S')
		|| mInput.Key('D')
		|| mInput.Key('A'))
	{
		CVector p = mpParent->Position();
		mpParent->Position(p + mpParent->MatrixRotate().VectorZ() * VELOCITY);
	}
	else
	{
		//Wキーが押されていないときは待機状態にする
		mState = EState::EIDLE;
	}

	//プレイヤーの前方向ベクトルを取得する
	CVector fwd = mpParent->CombinedMatrix().VectorZ();
	// 内積を計算して、回転量を求める
	float dx = cx.Dot(fwd);
	float dz = cz.Dot(fwd);
	if (abs(dx) < 0.01f)
	{
		if (dz < 0.0f)
		{
			dx = 1.0f;
		}
	}
	CVector rot(0.0f, dx * 10.0f, 0.0f);
	//プレイヤーをカメラ方向へ回転させる
	mpParent->Rotation(mpParent->Rotation() +rot);

	CCamera::Instance()->Rotation(CCamera::Instance()->Rotation() - rot);

	//スペースでジャンプ
	if (mInput.Key(' '))
	{
		mState = EState::EJUMP;
	}
}
