#pragma once
#include "Action.h"
class Wait : public ActionNode
{
public:
	virtual BTStatus tick(float TimeDelta) override;

private:
	float CurrentTime = 0.f;
	//float MaxTime = 30000.f;
	float lastIdleTime = 0.f;
};

