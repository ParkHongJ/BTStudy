#include <iostream>
#include <fstream>
#include "json.hpp"
#include "BTNode.h"
#include "Action.h"
#include "Sequence.h"
#include "Selector.h"

#include "MoveToEnemyNode.h"
#include "FindEnemyNode.h"

#include "ActionFactory.h"
#include "autoregister.h"

//#include <windows.h>
//#include <d3d11.h>
//#include <imgui.h>
//#include <imgui_impl_win32.h>
//#include <imgui_impl_dx11.h>
//#include <imgui_node_editor.h>
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

//namespace ed = ax::NodeEditor;
//
//static ID3D11Device* g_pd3dDevice = nullptr;
//static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
//static IDXGISwapChain* g_pSwapChain = nullptr;
//static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
//static ed::EditorContext* g_editorContext = nullptr;
//
//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
//// 렌더 타겟 생성
//void CreateRenderTarget() {
//    ID3D11Texture2D* pBackBuffer;
//    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
//    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
//    pBackBuffer->Release();
//}
//
//// 렌더 타겟 삭제
//void CleanupRenderTarget() {
//    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
//}
//
//// 디바이스 초기화
//bool CreateDeviceD3D(HWND hWnd) {
//    DXGI_SWAP_CHAIN_DESC sd{};
//    sd.BufferCount = 2;
//    sd.BufferDesc.Width = 0;
//    sd.BufferDesc.Height = 0;
//    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//    sd.OutputWindow = hWnd;
//    sd.SampleDesc.Count = 1;
//    sd.Windowed = TRUE;
//    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//
//    return D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
//        nullptr, 0, D3D11_SDK_VERSION, &sd,
//        &g_pSwapChain, &g_pd3dDevice, nullptr, &g_pd3dDeviceContext) == S_OK;
//}
//
//// 디바이스 종료
//void CleanupDeviceD3D() {
//    CleanupRenderTarget();
//    if (g_pSwapChain) g_pSwapChain->Release();
//    if (g_pd3dDeviceContext) g_pd3dDeviceContext->Release();
//    if (g_pd3dDevice) g_pd3dDevice->Release();
//}

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {

    BehaviorTreeEditor editor;
    editor.Run(hInstance, nCmdShow);
    //// 윈도우 클래스 등록
    //WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0,
    //    GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
    //    TEXT("NodeEditorWindow"), nullptr };
    //RegisterClassEx(&wc);
    //HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("BT Editor - ImGui + DX11"),
    //    WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720, nullptr, nullptr, wc.hInstance, nullptr);

    //// 디바이스 생성
    //if (!CreateDeviceD3D(hwnd)) return 1;
    //CreateRenderTarget();
    //ShowWindow(hwnd, SW_SHOWDEFAULT);
    //UpdateWindow(hwnd);

    //// ImGui 초기화
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;

    //ImGui::StyleColorsDark();
    //ImGui_ImplWin32_Init(hwnd);
    //ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    //// Node Editor 초기화
    //ed::Config config;
    //config.SettingsFile = "BTEditor.json";
    //g_editorContext = ed::CreateEditor(&config);
    //ed::SetCurrentEditor(g_editorContext);

    //// 루프
    //bool done = false;
    //while (!done) {
    //    MSG msg;
    //    while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //        if (msg.message == WM_QUIT)
    //            done = true;
    //    }
    //    if (done) break;

    //    ImGui_ImplDX11_NewFrame();
    //    ImGui_ImplWin32_NewFrame();
    //    ImGui::NewFrame();

    //    // NodeEditor 시작
    //    ed::Begin("Behavior Tree Editor");
    //    ed::BeginNode(1); ImGui::Text("Root Node"); ed::EndNode();
    //    ed::End(); // Editor 끝

    //    ImGui::Render();
    //    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
    //    const float clear_color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    //    g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color);
    //    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    //    g_pSwapChain->Present(1, 0);
    //}

    //// 종료 처리
    //ed::DestroyEditor(g_editorContext);
    //ImGui_ImplDX11_Shutdown();
    //ImGui_ImplWin32_Shutdown();
    //ImGui::DestroyContext();

    //CleanupDeviceD3D();
    //DestroyWindow(hwnd);
    //UnregisterClass(wc.lpszClassName, wc.hInstance);
    return 0;
}

// 윈도우 메시지 처리
//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
//        return true;
//    switch (msg) {
//    case WM_SIZE:
//        if (g_pd3dDevice && wParam != SIZE_MINIMIZED) {
//            CleanupRenderTarget();
//            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
//            CreateRenderTarget();
//        }
//        return 0;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        return 0;
//    default:
//        return DefWindowProc(hWnd, msg, wParam, lParam);
//    }
//}
