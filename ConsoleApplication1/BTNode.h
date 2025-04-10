#pragma once

#include <vector>
#include <memory>
#include <functional>
// 행동트리 상태 정의
enum class BTStatus {
    SUCCESS,
    FAILURE,
    RUNNING
};

// 행동트리 노드의 기본 인터페이스
class BTNode {
public:
    virtual ~BTNode() {}
    virtual BTStatus tick(float TimeDelta) = 0;
protected:
    virtual void Enter() {};
    virtual void Exit() {};
};
