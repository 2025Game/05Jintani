#pragma once
#ifndef CXPLAYER_H
#define CXPLAYER_H
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CState.h"
#include "CPlayerIdle.h"
#include "CPlayerWalk.h"
#include "CPlayerJump.h"
#include "CCamera.h"
#include "CColliderCapsule.h"
#include "CCollisionManager.h"

class CXPlayer : public CXCharacter
{
public:
	//衝突処理
//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
	void Update() override;
	CXPlayer();
	CColliderCapsule mColliderCapsule; //カプセルコライダ
	const CMatrix& FrameCombinedMatrix(const char* name);
private:
	EState mState;//状態の保持
	CState* mpState;//状態処理
	std::unique_ptr<CPlayerIdle> mpIdle;//待機状態
	std::unique_ptr<CPlayerWalk> mpWalk; //歩く状態
	std::unique_ptr<CPlayerJump> mpJump; //ジャンプ状態
};
#endif