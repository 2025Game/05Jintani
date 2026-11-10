#include "CPlayerJump.h"

#define GRAVITY CVector(0.0f, -0.0312f, 0.0f) // 重力加速度
#define JUMP_V CVector(0.0f, 0.6f, 0.0f) // ジャンプ初速
#define VELOCITY 0.1f //移動速度

void CPlayerJump::Start(CXCharacter* parent)
{
	//親ポインタを保存
	mpParent = parent;
	//アニメーションを変更
	mpParent->ChangeAnimation(7, false, 60);
	mState = EState::EJUMP; //状態種類をジャンプにする
	mJumpV = JUMP_V; //ジャンプの初速度
}

void CPlayerJump::Update()
{
	//ジャンプの速度分だけ、上方向へ移動させる
	mpParent->Position(mpParent->Position() + mJumpV);
	//重力加速度分だけ、下方向への速度を増やす
	mJumpV = mJumpV + GRAVITY;

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
		mState = EState::EJUMP;
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
	mpParent->Rotation(mpParent->Rotation() + rot);

	CCamera::Instance()->Rotation(CCamera::Instance()->Rotation() - rot);
}

void CPlayerJump::Collision(CCollider* m, CCollider* o)
{
	//自身のコライダタイプ?判定
	switch (m->Type()) {
	case CCollider::EType::ECAPSULE://カプセルコライダ
		//相手のコライダがカプセルコライダの時
		if (o->Type() ==
			CCollider::EType::ETRIANGLE)
		{
			CVector adjust;//調整用ベクトル
			//三角形とカプセルの衝突判定
			if (CCollider::CollisionTriangleCapsule(
				o, m, &adjust))

			{
				//待機状態にする
				mState = EState::EIDLE;
			}
		}
		break;
	}
}
