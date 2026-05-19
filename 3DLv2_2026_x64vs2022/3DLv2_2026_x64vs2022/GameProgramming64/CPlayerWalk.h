#pragma once
#include "CInput.h"
#include "CState.h"
#include "CXCharacter.h"

class CPlayerWalk :public CState
{
public:
	void Start(CXCharacter* parent)override;
	void Update()override;
private:
	CInput mInput;
};