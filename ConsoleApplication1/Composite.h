#pragma once
#include "BTNode.h"
// Composite 노드: 여러 자식 노드를 관리하는 베이스 클래스
class CompositeNode : public BTNode {
public:
    // 자식 노드를 추가하는 메서드
    void addChild(const std::shared_ptr<BTNode>& child) {
        children.push_back(child);
    }

protected:
    // 자식 노드 목록
    std::vector<std::shared_ptr<BTNode>> children;
};

