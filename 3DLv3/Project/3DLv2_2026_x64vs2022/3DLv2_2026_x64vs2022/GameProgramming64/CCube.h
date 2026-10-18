#pragma once
#include "CCharacter3.h"
#include "CColliderTriangle.h"

class CCube : public CCharacter3
{
public:
	CCube();
	void Update();
private:
	//モデルデータのインスタンス
	static CModel msModel;
	//コライダは底面以外に付ける
	CColliderTriangle mCollider[10];
};
