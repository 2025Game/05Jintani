//課題4.2 プレイヤーが重力の分だけ下へ移動する以下のプログラムを実装してく
//ださい。(加速は考慮しなくてよいです)
#include "CXPlayer.h"

#define GRAVITY 0.0625f // 重力

#define _USE_MATH_DEFINES
#include <math.h>
//ラジアンを度数に変換するための定数
const float RAD_TO_DEG = 180.0f / (float)M_PI;

void CXPlayer::Update()
{
	//状態?更新
	mpState->Update();
	//状態䛾切り替え
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
		case EState::EATTACK:
			mpState = mpAttack.get();
			break;
		case EState::EJUMP:
			mpState = mpJump.get();
			break;
		default:
			break;
		}
		mpState->Start(this);
	}
	//課題4.2 GRAVITYの大きさだけ、下方向へ移動させる
	mPosition = mPosition - CVector(0.0f, GRAVITY, 0.0f);
	CXCharacter::Update();
	//カメラの位置をプレイヤーの位置から、少し上にする
	CCamera::Instance()->Position(CVector(0.0f, 4.0f, 0.0f));
	mColliderCapsule.Update();
	// 剣コライダの更新
	mColliderSword.Update();
}

CXPlayer::CXPlayer()
	//: mColliderLine(this, &mMatrix,CVector(0.0f, 3.5f, 0.0f), CVector(0.0f, 0.0f, 0.0f))
	: mColliderCapsule(this, &mMatrix, CVector(0.0f, 3.5f, 0.0f), CVector(0.0f, 0.0f, 0.0f), 0.5f)
	, mColliderSword(this, nullptr, CVector(), CVector(), 0.1f)
{
	mPosition = CVector(1.0f, 0.0f, 0.0f);
	//待機状態の作成
	mpIdle = std::make_unique<CPlayerIdle>();
	//最初の待機状態
	//get()が、unique_ptrが保持しているポインタを取得する関数
	mpState = mpIdle.get();
	mpState->Start(this);
	mState = mpState->State();
	//歩く状態の作成
	mpWalk = std::make_unique<CPlayerWalk>();
	//攻撃状態を作成
	mpAttack = std::make_unique<CPlayerAttack>();
	//ジャンプ状態を作成
	mpJump = std::make_unique<CPlayerJump>();
	//カメラ䛾親をプレイヤー䛻する
	CCamera::Instance()->Parent(this);
}

void CXPlayer::Collision(CCollider* m, CCollider* o)
{
	if (o == &mColliderCapsule || o == &mColliderSword)
	{
		//相手がプレイヤーのコライダの時は、衝突処理を行わない
		return;
	}
	//状態クラスの衝突処理
	mpState->Collision(m, o);
	//自身のコライダタイプの判定
	switch (m->Type()) {
	//case CCollider::EType::ELINE://線分コライダ
	//	//相手のコライダが三角コライダの時
	//	if (o->Type() == CCollider::EType::ETRIANGLE)
	//	{
	//		CVector adjust;//調整用ベクトル
	//		//三角形と線分の衝突判定
	//		if (CCollider::CollisionTriangleLine(
	//			o, m, &adjust))
	//		{
	//			//位置の更新
	//			//現在のワールドでの位置
	//			mPosition = (CVector() * mMatrix + adjust);
	//			//前方の位置を求める
	//			CVector forward = (CVector(0.0f, 0.0f, 1.0f) * mMatrix + adjust);
	//			if (o->Parent())
	//			{
	//				//親のローカル座標へ変換
	//				mPosition = mPosition *
	//					o->Parent()->CombinedMatrix().Inverse();
	//				//親のローカル座標へ変換
	//				forward = forward *
	//					o->Parent()->CombinedMatrix().Inverse();
	//			}

	//			forward = forward - mPosition;

	//			mRotation = CVector(mRotation.X(),
	//				atan2f(forward.X(), forward.Z()) * RAD_TO_DEG,
	//				mRotation.Z());

	//			//親の設定
	//			mpParent = o->Parent();
	//			//行列の更新
	//			CTransform::Update();
	//		}
	//	}
	//	break;

	case CCollider::EType::ECAPSULE:

		if (o->Type() == CCollider::EType::ETRIANGLE)
		{
			CVector adjust;

			// カプセルと三角形の衝突判定
			if (CCollider::CollisionTriangleCapsule(o,m,&adjust))
			{
				// 押し戻し後のワールド座標
				mPosition =CVector() * mMatrix + adjust;

				// 前方位置
				CVector forward =CVector(0.0f, 0.0f, 1.0f) *mMatrix + adjust;

				if (o->Parent())
				{
					mPosition =mPosition *
						o->Parent()->CombinedMatrix().Inverse();

					forward =forward *
						o->Parent()->CombinedMatrix().Inverse();
				}

				forward = forward - mPosition;

				// 床の回転に合わせる
				mRotation = CVector(mRotation.X(),
					atan2f(forward.X(),forward.Z()) *RAD_TO_DEG,
					mRotation.Z());

				// 親に設定
				mpParent = o->Parent();

				// 行列更新
				CTransform::Update();
			}
		}
		else if (o->Type() == CCollider::EType::ECAPSULE)
		{
			CVector adjust;

			if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
			{
				mPosition = CVector() * mMatrix + adjust;

				CVector forward = CVector(0.0f, 0.0f, 1.0f) * mMatrix + adjust;

				if (mpParent)
				{
					mPosition = mPosition * mpParent->CombinedMatrix().Inverse();

					forward = forward * mpParent->CombinedMatrix().Inverse();
				}

				forward = forward - mPosition;

				CTransform::Update();
			}
		}
	}
}

//衝突処理
void CXPlayer::Collision()
{
	////コライダの優先度変更
	//mColliderLine.ChangePriority();
	////衝突処理を実行
	//CCollisionManager::Instance()->Collision(
	//	&mColliderLine, COLLISIONRANGE);

	// カプセルコライダの優先度更新
	mColliderCapsule.ChangePriority();
	// カプセルコライダの衝突処理
	CCollisionManager::Instance()->Collision(
		&mColliderCapsule, COLLISIONRANGE);

	//コライダの優先度変更
	mColliderSword.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(
		&mColliderSword,
		COLLISIONRANGE);
}

const CMatrix& CXPlayer::FrameCombinedMatrix(const char* name)
{
	//フレーム名䛛ら行列を取得䛩る
	for (size_t i = 0; i < mpModel->Frames().size(); i++) {
		if (strcmp(mpModel->Frames()[i]->Name(), name) == 0) {
			return mpModel->Frames()[i]->CombinedMatrix();
		}
	}
	static CMatrix dummy; //ダミー䛾行列
	return dummy;
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//剣コライダ䛾設定
	mColliderSword.Set(this,
		&FrameCombinedMatrix("RightHand"),
		CVector(-15.0f, 0.0f, 20.0f),
		CVector(-15.0f, 0.0f, 70.0f), 0.1f);

}