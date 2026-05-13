#pragma once
#ifndef CXPLAYER_H
#define CXPLAYER_H
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CCollisionManager.h"
#include "CPlayerIdle.h"
#include "CState.h"

class CXPlayer : public CXCharacter
{
private:
	EState mState; //状態䛾保持
	CState* mpState; //状態処理
	std::unique_ptr<CPlayerIdle> mpIdle; //待機状態

public:
	void Update() override;
	CXPlayer();
	CColliderLine mColliderLine; //ラインコライダ
	//衝突処理
//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();

};
#endif
