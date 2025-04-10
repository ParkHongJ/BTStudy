#pragma once
#include "BTNode.h"
// Action ���: ���� �ൿ(Ȥ�� ����)�� �����ϴ� ���� ���
class ActionNode : public BTNode
{
public:
    virtual BTStatus tick(float TimeDelta) override {
        return BTStatus::SUCCESS;
    }
private:
    std::shared_ptr<class Blackboard> blackBoard;
};

