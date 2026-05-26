#pragma once
#include "CState.h"
#include "CXCharacter.h"
#include "CCollider.h"


class CPlayerJump :public CState
{
public:
	void Start(CXCharacter* parent)override;
	void Update()override;
private:
	CVector mJumpV; //ジャンプの速度
	//衝突処理
//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o) override;

};