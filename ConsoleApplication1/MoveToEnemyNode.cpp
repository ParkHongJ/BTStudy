#include "MoveToEnemyNode.h"
#include <iostream>
BTStatus MoveToEnemyNode::tick(float deltaTime)
{
	std::cout << "[MoveToEnemy] ���� ��!" << std::endl;
	return BTStatus::SUCCESS;
}
