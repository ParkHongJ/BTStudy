#include "Wait.h"
#include <iostream>
#include <Windows.h>
BTStatus Wait::tick(float TimeDelta)
{
    /*CurrentTime += TimeDelta;
	if (CurrentTime >= MaxTime)
	{
		CurrentTime = 0.f;
		std::cout << "���Ϸ�!" << std::endl;
		return BTStatus::SUCCESS;
	}*/

	CurrentTime = GetTickCount64();
	if (CurrentTime - lastIdleTime >= 1000)
	{
		lastIdleTime = CurrentTime;
		std::cout << "���Ϸ�!" << std::endl;
		return BTStatus::SUCCESS;
	}

    return BTStatus::RUNNING;
}
