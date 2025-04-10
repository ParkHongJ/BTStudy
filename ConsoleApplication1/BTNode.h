#pragma once

#include <vector>
#include <memory>
#include <functional>
// �ൿƮ�� ���� ����
enum class BTStatus {
    SUCCESS,
    FAILURE,
    RUNNING
};

// �ൿƮ�� ����� �⺻ �������̽�
class BTNode {
public:
    virtual ~BTNode() {}
    virtual BTStatus tick(float TimeDelta) = 0;
protected:
    virtual void Enter() {};
    virtual void Exit() {};
};
