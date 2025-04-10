#pragma once
#include "Action.h"
class FindEnemyNode : public ActionNode {
public:
    BTStatus tick(float deltaTime) override;
};