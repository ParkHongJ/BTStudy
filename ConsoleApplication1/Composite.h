#pragma once
#include "BTNode.h"
// Composite ���: ���� �ڽ� ��带 �����ϴ� ���̽� Ŭ����
class CompositeNode : public BTNode {
public:
    // �ڽ� ��带 �߰��ϴ� �޼���
    void addChild(const std::shared_ptr<BTNode>& child) {
        children.push_back(child);
    }

protected:
    // �ڽ� ��� ���
    std::vector<std::shared_ptr<BTNode>> children;
};

