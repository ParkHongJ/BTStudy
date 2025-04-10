#pragma once
#include "BTNode.h"
// Action 노드: 실제 행동(혹은 조건)을 수행하는 리프 노드
class ActionNode : public BTNode
{
public:
    virtual BTStatus tick(float TimeDelta) override {
        return BTStatus::SUCCESS;
    }
private:
    std::shared_ptr<class Blackboard> blackBoard;
};

