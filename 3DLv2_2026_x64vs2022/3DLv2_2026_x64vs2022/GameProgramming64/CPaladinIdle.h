#pragma once
#pragma once
#include "CState.h"
#include "CCollider.h"

class CPaladinIdle : public CState
{
public:
	CPaladinIdle(CXCharacter* parent);
	void Start(CXCharacter* parent) override;
	void Update() override;
	void Collision(CCollider* m, CCollider* o) override;
private:
	static int msAnimNo; //アニメーション番号
};