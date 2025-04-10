#pragma once
#include "Composite.h"
// Sequence 노드: 모든 자식 노드가 SUCCESS여야 SUCCESS 반환
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

            ++CurrentIndex; // Success면 다음 노드로
        }

        CurrentIndex = 0;

        return BTStatus::SUCCESS;
    }
private:
    uint16_t CurrentIndex = 0;
};
