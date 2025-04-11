#pragma once
#include "BTNode.h"
class Decorator : public BTNode
{
protected:
    std::shared_ptr<BTNode> child;

public:
    Decorator(std::shared_ptr<BTNode> childNode)
        : child(childNode) {
    }

    virtual BTStatus tick(float deltaTime) override = 0;
};

