#pragma once

#include <windows.h>
#include <d3d11.h>
#include "imgui_node_editor.h"


namespace ed = ax::NodeEditor;

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
    void Render();

    HWND hWnd = nullptr;
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11RenderTargetView* renderTargetView = nullptr;
    ed::EditorContext* g_editorContext = nullptr;
};

