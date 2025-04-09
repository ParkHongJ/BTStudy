#include <iostream>
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
};

// Sequence 노드: 모든 자식 노드가 SUCCESS여야 SUCCESS 반환
class Sequence : public BTNode
{
public:
    void addChild(std::shared_ptr<BTNode> child) {
        children.push_back(child);
    }

    virtual BTStatus tick(float TimeDelta) override {
        for (auto& child : children) {
            BTStatus status = child->tick(TimeDelta);
            // 자식 노드 중 하나라도 실패하거나 실행중이면 그 상태를 즉시 반환
            if (status != BTStatus::SUCCESS) {
                return status;
            }
        }
        return BTStatus::SUCCESS;
    }

private:
    std::vector<std::shared_ptr<BTNode>> children;
};

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

// Selector 노드: 자식 노드 중 하나라도 SUCCESS이면 SUCCESS 반환
class Selector : public BTNode
{
public:
    void addChild(std::shared_ptr<BTNode> child) {
        children.push_back(child);
    }

    virtual BTStatus tick(float TimeDelta) override {
        for (auto& child : children) {
            BTStatus status = child->tick(TimeDelta);
            // 성공한 자식이 있으면 즉시 SUCCESS 반환
            if (status == BTStatus::SUCCESS) {
                return BTStatus::SUCCESS;
            }
        }
        return BTStatus::FAILURE;
    }

private:
    std::vector<std::shared_ptr<BTNode>> children;
};

// Action 노드: 실제 행동(혹은 조건)을 수행하는 리프 노드
class ActionNode : public BTNode 
{
public:
    // 함수 객체를 받아서 tick 호출 시 실행
    using ActionFunc = std::function<BTStatus()>;
    ActionNode(ActionFunc func) : action(func) {}

    virtual BTStatus tick(float TimeDelta) override {
        return action();
    }

private:
    ActionFunc action;
};

// 예시 동작 함수들
BTStatus actionSuccess() {
    std::cout << "Action: Success\n";
    return BTStatus::SUCCESS;
}

BTStatus actionFail() {
    std::cout << "Action: Fail\n";
    return BTStatus::FAILURE;
}

int main() {
    // Sequence 노드 생성
    auto sequenceNode = std::make_shared<Sequence>();

    // 리프 노드들을 생성하여 Sequence에 추가
    auto actionNode1 = std::make_shared<ActionNode>(actionSuccess);
    auto actionNode2 = std::make_shared<ActionNode>(actionFail);   // 이 노드가 실패하므로 전체가 실패하게 됨
    auto actionNode3 = std::make_shared<ActionNode>(actionSuccess);

    sequenceNode->addChild(actionNode1);
    sequenceNode->addChild(actionNode2);
    sequenceNode->addChild(actionNode3);

    // 행동트리 실행 (tick)
    BTStatus result = sequenceNode->tick();

    if (result == BTStatus::SUCCESS)
        std::cout << "Sequence succeeded\n";
    else
        std::cout << "Sequence failed\n";

    return 0;
}
