#include "BehaviorTreeEditor.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_node_editor.h"

#include <tchar.h>
namespace ed = ax::NodeEditor;

// static 윈도우 프로시저
static BehaviorTreeEditor* g_editorInstance = nullptr;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
    switch (msg)
    {
    case WM_SIZE:
		if (g_editorInstance && g_editorInstance->device && wParam != SIZE_MINIMIZED)
			g_editorInstance->CreateRenderTarget();
		/*if (g_editorInstance->device && wParam != SIZE_MINIMIZED) {
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}*/
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

BehaviorTreeEditor::BehaviorTreeEditor() 
{ 
    g_editorInstance = this; 
}

BehaviorTreeEditor::~BehaviorTreeEditor() 
{
    CleanupD3D();
}

int BehaviorTreeEditor::Run(HINSTANCE hInstance, int nCmdShow)
{
    InitWindow(hInstance, nCmdShow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(device, context);

    ed::Config config;
    config.SettingsFile = "BTEditor.json";

    g_editorContext = ed::CreateEditor(&config);
    ed::SetCurrentEditor(g_editorContext);

    MainLoop();

    ed::DestroyEditor(g_editorContext);
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

void BehaviorTreeEditor::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0, hInstance,
        nullptr, nullptr, nullptr, nullptr, _T("BTEditorWindow"), nullptr };
    RegisterClassEx(&wc);
    hWnd = /*CreateWindow(wc.lpszClassName, _T("Behavior Tree Editor"),
        WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720,
        nullptr, nullptr, hInstance, nullptr);*/
        CreateWindow(wc.lpszClassName, TEXT("BT Editor - ImGui + DX11"),
            WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720, nullptr, nullptr, wc.hInstance, nullptr);

    if (!InitD3D(hWnd)) 
        return;

    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
}

bool BehaviorTreeEditor::InitD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    return D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
        nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swapChain,
        &device, nullptr, &context) == S_OK;
}

void BehaviorTreeEditor::CreateRenderTarget()
{
    if (renderTargetView) renderTargetView->Release();
    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();
}

void BehaviorTreeEditor::CleanupRenderTarget()
{
    if (renderTargetView) { renderTargetView->Release(); renderTargetView = nullptr; }
}

void BehaviorTreeEditor::CleanupD3D()
{
    CleanupRenderTarget();
    if (swapChain) swapChain->Release();
    if (context) context->Release();
    if (device) device->Release();
}

void BehaviorTreeEditor::MainLoop()
{
    MSG msg{};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 실제 UI 그리기
       /* ed::Begin("Behavior Tree Editor");
        ed::BeginNode(1); ImGui::Text("Sequence"); ed::EndNode();
        ed::End();*/

        Render();


        ImGui::Render();
        context->OMSetRenderTargets(1, &renderTargetView, nullptr);
        const float clearColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        context->ClearRenderTargetView(renderTargetView, clearColor);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        swapChain->Present(1, 0);
        
        //    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        //    const float clear_color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        //    g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color);
        //    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        //    g_pSwapChain->Present(1, 0);
    }
}

void BehaviorTreeEditor::Render()
{
	ed::Begin("Behavior Tree Editor");
	ed::BeginNode(1); ImGui::Text("Sequence"); ed::EndNode();
	ed::End();
}
