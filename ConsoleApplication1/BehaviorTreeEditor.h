#pragma once
#include <d3d11.h>
#include <vector>
#include "Node.h"

extern Pin* newNodeLinkPin;
extern Pin* newLinkPin;

//namespace ed = ax::NodeEditor;

static inline ImRect ImRect_Expanded(const ImRect& rect, float x, float y)
{
    auto result = rect;
    result.Min.x -= x;
    result.Min.y -= y;
    result.Max.x += x;
    result.Max.y += y;
    return result;
}

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
    ImGuiContext* m_ImguiContext = nullptr;


    int GetNextId()
    {
        return m_NextId++;
    }

    Node* SpawnTreeSequenceNode()
    {
        m_Nodes.emplace_back(GetNextId(), "Sequence");
        m_Nodes.back().Type = NodeType::Composite;
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    Node* SpawnTreeTaskNode()
    {
        m_Nodes.emplace_back(GetNextId(), "Move To");
        m_Nodes.back().Type = NodeType::Action;
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);

        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    Node* SpawnRootNode()
    {
        m_Nodes.emplace_back(GetNextId(), "Root");
        m_Nodes.back().Type = NodeType::Root;
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    Node* SpawnTreeTask2Node()
    {
        m_Nodes.emplace_back(GetNextId(), "Random Wait");
        m_Nodes.back().Type = NodeType::Action;
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

    Pin* FindPin(ed::PinId id)
    {
        if (!id)
            return nullptr;

        for (auto& node : m_Nodes)
        {
            for (auto& pin : node.Inputs)
                if (pin.ID == id)
                    return &pin;

            for (auto& pin : node.Outputs)
                if (pin.ID == id)
                    return &pin;
        }

        return nullptr;
    }

    ImColor GetIconColor(PinType type)
    {
        switch (type)
        {
        default:
        case PinType::Flow:     return ImColor(255, 255, 255);
        case PinType::Bool:     return ImColor(220, 48, 48);
        case PinType::Int:      return ImColor(68, 201, 156);
        case PinType::Float:    return ImColor(147, 226, 74);
        case PinType::String:   return ImColor(124, 21, 153);
        case PinType::Object:   return ImColor(51, 150, 215);
        case PinType::Function: return ImColor(218, 0, 183);
        case PinType::Delegate: return ImColor(255, 48, 48);
        }
    };

    std::vector<Node>    m_Nodes;

    std::vector<Link>    m_Links;
    int m_NextId = 1;

};
