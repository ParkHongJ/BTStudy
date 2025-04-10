#pragma once
#include "Composite.h"
// Selector 노드: 자식 노드 중 하나라도 SUCCESS이면 SUCCESS 반환
class Selector : public CompositeNode
{
public:
    virtual BTStatus tick(float TimeDelta) override {
        while (CurrentIndex < children.size()) {
            BTStatus result = children[CurrentIndex]->tick(TimeDelta);

            if (result == BTStatus::RUNNING)
                return BTStatus::RUNNING;

            if (result == BTStatus::SUCCESS) {
                CurrentIndex = 0;
                return BTStatus::SUCCESS;
            }

            ++CurrentIndex; // 현재 자식 실패했으면 다음으로
        }

        CurrentIndex = 0;
        return BTStatus::FAILURE; // 모든 자식 실패
    }

private:
    uint16_t CurrentIndex = 0;
};