#pragma once
#pragma once
#include "CState.h"
class CPaladinDamage : public CState
{
public:
	CPaladinDamage(CXCharacter* parent);
	void Start(CXCharacter* parent) override;
	void Update() override;
private:
	static int msAnimNo;
};