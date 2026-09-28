#include "CPlayerWalk.h"
#include "CCamera.h"

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
		// カメラの右方向ベクトルを取得する
		CVector cx;
		cx = CCamera::Instance()->ModelViewInverse().VectorX();

		// プレイヤーの前方向ベクトルを取得する
		CVector fwd = mpParent->CombinedMatrix().VectorZ();

		// 内積を計算して、回転量を求める
		CVector rot(0.0f, cx.Dot(fwd) * 10.0f, 0.0f);

		// プレイヤーをカメラ方向へ回転させる
		mpParent->Rotation(mpParent->Rotation() + rot);

		CCamera::Instance()->Rotation(CCamera::Instance()->Rotation() - rot);

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
	//Iで攻撃
	if (mInput.Key('I'))
	{
		mState = EState::EATTACK;
	}

	//左クリックで攻撃
	if (mInput.Key(VK_LBUTTON))
	{
		mState = EState::EATTACK;
	}

	//スペースでジャンプ
	if (mInput.Key(' '))
	{
		mState = EState::EJUMP;
	}
}

