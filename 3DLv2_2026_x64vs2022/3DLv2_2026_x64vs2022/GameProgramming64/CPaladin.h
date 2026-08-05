#pragma once
#ifndef CPALADIN_H
#define CPALADIN_H
#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CPaladinIdle.h"
#include "CState.h"
#include "CPaladinDamage.h"

class CPaladin : public CXCharacter
{
public:
	//CPaladin(位置, 回転, 拡大縮小)
	CPaladin(const CVector& pos, const CVector& rot = CVector()
		, const CVector& scale = CVector(2.5f, 2.5f, 2.5f));
	void Update() override;
	void Collision(CCollider* m, CCollider* o);
	void Collision();
private:
	static CModelX msModel;
	//CColliderCapsule mCollider; //カプセルコライダ
	//EState mState;      // 状態の保持
	CState* mpState;    // 状態処理
	std::unique_ptr<CPaladinIdle> mpIdle; // 待機状態
	std::unique_ptr<CPaladinDamage> mpDamage; //ダメージ状態
	CColliderCapsule mColliderCapsule;
};
#endif