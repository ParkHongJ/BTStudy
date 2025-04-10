#pragma once
#include "Action.h"
class MoveToEnemyNode : public ActionNode {
public:
    BTStatus tick(float deltaTime) override;
};