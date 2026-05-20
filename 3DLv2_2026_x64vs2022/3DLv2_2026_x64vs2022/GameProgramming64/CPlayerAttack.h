#pragma once
#include "CState.h"
#include "CXCharacter.h"

class CPlayerAttack :public CState
{
public:
	void Start(CXCharacter* parent)override;
	void Update()override;
private:
	int mStopTimer;
};