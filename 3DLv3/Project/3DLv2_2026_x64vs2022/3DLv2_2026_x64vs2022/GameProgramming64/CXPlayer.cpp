#include "CXPlayer.h"

#define GRAVITY CVector(0.0f, -0.0625f, 0.0f) 
#define _USE_MATH_DEFINES
#include <math.h>
//ラジアンを度数に変換するための定数
const float RAD_TO_DEG = 180.0f / (float)M_PI;

// 重力加速度
void CXPlayer::Update()
{
	//状態の更新
	mpState->Update();
	//状態?切り替え
	if (mState != mpState->State())
	{
		mState = mpState->State();
		switch (mState) {
		case EState::EIDLE:
			mpState = mpIdle.get();
			break;
		case EState::EWALK:
			mpState = mpWalk.get();
			break;
		case EState::EJUMP:
			mpState = mpJump.get();
			break;
		default:
			break;
		}
		mpState->Start(this);
	}

	//GRAVITYの大きさだけ、下方向へ移動させる
	mPosition = mPosition + GRAVITY;

	//親クラスの更新
	CXCharacter::Update();

	//カメラの位置をプレイヤーの位置から、少し上にする
	CCamera::Instance()->Position(CVector(0.0f, 4.0f, 0.0f));

	mColliderCapsule.Update();
}

CXPlayer::CXPlayer()
	: mColliderCapsule(this, &mMatrix, CVector(0.0f, 3.5f, 0.0f), CVector(0.0f, 0.0f, 0.0f), 0.5f)
{
	mPosition = CVector(-20.0f,5.0f,10.0f);
	//待機状態の作成
	mpIdle = std::make_unique<CPlayerIdle>();
	//最初は待機状態
	//get()は、unique_ptrが保持しているポインタを取得する関数
	mpState = mpIdle.get();
	mpState->Start(this);
	mState = mpState->State();
	//歩く状態の作成
	mpWalk = std::make_unique<CPlayerWalk>();
	mpJump = std::make_unique<CPlayerJump>();
	//カメラの親をプレイヤーにする
	CCamera::Instance()->Parent(this);
}

void CXPlayer::Collision(CCollider* m, CCollider* o)
{
	//状態クラスの衝突処理
	mpState->Collision(m, o);
	switch (m->Type()) {
	case CCollider::EType::ECAPSULE:

		if (o->Type() == CCollider::EType::ETRIANGLE)
		{
			CVector adjust;

			// カプセルと三角形の衝突判定
			if (CCollider::CollisionTriangleCapsule(o, m, &adjust))
			{
				// 押し戻し後のワールド座標
				mPosition = CVector() * mMatrix + adjust;

				// 前方位置
				CVector forward = CVector(0.0f, 0.0f, 1.0f) * mMatrix + adjust;

				if (o->Parent())
				{
					mPosition = mPosition *
						o->Parent()->CombinedMatrix().Inverse();

					forward = forward *
						o->Parent()->CombinedMatrix().Inverse();
				}

				forward = forward - mPosition;

				// 親に設定
				mpParent = o->Parent();

				// 行列更新
				CTransform::Update();
			}
		}
	}
}

void CXPlayer::Collision()
{
	// カプセルコライダの優先度更新
	mColliderCapsule.ChangePriority();
	// カプセルコライダの衝突処理
	CCollisionManager::Instance()->Collision(
		&mColliderCapsule, COLLISIONRANGE);
}

const CMatrix& CXPlayer::FrameCombinedMatrix(const char* name)
{
	//フレーム名から行列を取得する
	for (size_t i = 0; i < mpModel->Frames().size(); i++) {
		if (strcmp(mpModel->Frames()[i]->Name(), name) == 0) {
			return mpModel->Frames()[i]->CombinedMatrix();
		}
	}
	static CMatrix dummy; //ダミーの行列
	return dummy;
}