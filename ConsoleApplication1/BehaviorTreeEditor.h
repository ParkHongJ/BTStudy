#pragma once

#include <windows.h>
#include <d3d11.h>
#include <vector>

#include "Node.h"

namespace ed = ax::NodeEditor;

struct Node;

class BehaviorTreeEditor
{
public:
    BehaviorTreeEditor();
    ~BehaviorTreeEditor();

    int Run(HINSTANCE hInstance, int nCmdShow);

public:
    void InitWindow(HINSTANCE hInstance, int nCmdShow);
    bool InitD3D(HWND hWnd);
    void CleanupD3D();
    void CreateRenderTarget();
    void CleanupRenderTarget();
    void MainLoop();
    void Update();
    void RenderBegin();
    void RenderEnd();
    void Render();

    HWND hWnd = nullptr;
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11RenderTargetView* renderTargetView = nullptr;
    ed::EditorContext* g_editorContext = nullptr;


    int GetNextId()
    {
        return m_NextId++;
    }

    Node* SpawnTreeSequenceNode()
    {
        m_Nodes.emplace_back(GetNextId(), "Sequence");
        m_Nodes.back().Type = NodeType::Tree;
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    Node* SpawnTreeTaskNode()
    {
        m_Nodes.emplace_back(GetNextId(), "Move To");
        m_Nodes.back().Type = NodeType::Tree;
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);

        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    Node* SpawnTreeTask2Node()
    {
        m_Nodes.emplace_back(GetNextId(), "Random Wait");
        m_Nodes.back().Type = NodeType::Tree;
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);

        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }


    void BuildNode(Node* node)
    {
        for (auto& input : node->Inputs)
        {
            input.Node = node;
            input.Kind = PinKind::Input;
        }

        for (auto& output : node->Outputs)
        {
            output.Node = node;
            output.Kind = PinKind::Output;
        }
    }

    void BuildNodes()
    {
        for (auto& node : m_Nodes)
            BuildNode(&node);
    }

    std::vector<Node>    m_Nodes;
    int m_NextId = 1;

};

