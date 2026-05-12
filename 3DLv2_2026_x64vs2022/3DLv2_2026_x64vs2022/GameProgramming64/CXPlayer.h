#pragma once
#ifndef CXPLAYER_H
#define CXPLAYER_H
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CCollisionManager.h"
class CXPlayer : public CXCharacter
{
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
