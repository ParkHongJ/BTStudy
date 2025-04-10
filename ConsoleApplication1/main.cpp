
#pragma region 파일입출력
#include <fstream>
#include "json.hpp"
#pragma endregion

#pragma region 행동트리 헤더
#include "BTNode.h"
#include "Action.h"
#include "Sequence.h"
#include "Selector.h"

#include "MoveToEnemyNode.h"
#include "FindEnemyNode.h"

#include "ActionFactory.h"
#include "autoregister.h"
#pragma endregion

#include "BehaviorTreeEditor.h"

#pragma comment(lib, "d3d11.lib")

using json = nlohmann::json;

std::shared_ptr<BTNode> buildTree(const json& j) {
    std::string type = j["type"].get<std::string>();

    if (type == "Sequence") {
        auto node = std::make_unique<Sequence>();
        if (j.contains("children")) {
            for (const auto& child : j["children"]) {
                node->addChild(buildTree(child)); // 재귀!
            }
        }
        return node;
    }

    if (type == "Selector") {
        auto node = std::make_unique<Selector>();
        if (j.contains("children")) {
            for (const auto& child : j["children"]) {
                node->addChild(buildTree(child)); // 재귀!
            }
        }
        return node;
    }

    if (type == "Action") {
        std::string name = j["name"].get<std::string>();
        auto it = getActionFactory().find(name);
        if (it == getActionFactory().end()) {
            throw std::runtime_error("Unknown Action: " + name);
        }
        return it->second(); // 팩토리 호출해서 ActionNode 리턴
    }
    throw std::runtime_error("Unknown node type: " + type);
}

#pragma region 콘솔 main (Load있음)
//int main() {
//
//    std::ifstream file("behavior.json");
//    if (!file) {
//        std::cerr << "behavior.json 파일을 열 수 없습니다." << std::endl;
//        return 1;
//    }
//
//    json j;
//    file >> j;
//
//    std::shared_ptr<BTNode> g_BehaviorTreeRoot;
//    g_BehaviorTreeRoot = buildTree(j);
//
//    while (true)
//    {
//        g_BehaviorTreeRoot->tick(0.00001f);
//    }
//    
//    return 0;
//}
#pragma endregion

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {

    BehaviorTreeEditor editor;
    editor.Run(hInstance, nCmdShow);
    return 0;
}