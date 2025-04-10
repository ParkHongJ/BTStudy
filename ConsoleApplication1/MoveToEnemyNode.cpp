#include "MoveToEnemyNode.h"
#include <iostream>
BTStatus MoveToEnemyNode::tick(float deltaTime)
{
	std::cout << "[MoveToEnemy] ½ÇÇà Áß!" << std::endl;
	return BTStatus::SUCCESS;
}
