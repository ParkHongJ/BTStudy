#pragma once
#include "Composite.h"
// Sequence ���: ��� �ڽ� ��尡 SUCCESS���� SUCCESS ��ȯ
class Sequence : public CompositeNode
{
public:
    virtual BTStatus tick(float TimeDelta) override {
        while (CurrentIndex < children.size()) {
            BTStatus result = children[CurrentIndex]->tick(TimeDelta);

            if (result == BTStatus::RUNNING)
                return BTStatus::RUNNING;

            if (result == BTStatus::FAILURE) {
                CurrentIndex = 0;
                return BTStatus::FAILURE;
            }

            ++CurrentIndex; // Success�� ���� ����
        }

        CurrentIndex = 0;

        return BTStatus::SUCCESS;
    }
private:
    uint16_t CurrentIndex = 0;
};
