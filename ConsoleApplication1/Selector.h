#pragma once
#include "Composite.h"
// Selector ���: �ڽ� ��� �� �ϳ��� SUCCESS�̸� SUCCESS ��ȯ
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

            ++CurrentIndex; // ���� �ڽ� ���������� ��������
        }

        CurrentIndex = 0;
        return BTStatus::FAILURE; // ��� �ڽ� ����
    }

private:
    uint16_t CurrentIndex = 0;
};