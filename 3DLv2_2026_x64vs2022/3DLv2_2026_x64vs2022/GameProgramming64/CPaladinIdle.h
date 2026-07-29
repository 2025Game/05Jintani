#pragma once
#pragma once
#include "CState.h"

class CPaladinIdle : public CState
{
public:
	CPaladinIdle(CXCharacter* parent);
	void Start(CXCharacter* parent) override;
	void Update() override;
private:
	static int msAnimNo; //アニメーション番号
};