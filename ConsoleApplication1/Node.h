#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <windows.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <imgui_internal.h>
#include "utilities/builders.h"
#include <imgui_node_editor.h>

namespace ed = ax::NodeEditor;
namespace util = ax::NodeEditor::Utilities;

static inline ImRect ImGui_GetItemRect()
{
    return ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
}

enum class NodeType
{
    None,
    Root,
    Composite,
    Action,
    Decorator
};

enum class PinType
{
    Flow,
    Bool,
    Int,
    Float,
    String,
    Object,
    Function,
    Delegate,
};

enum class PinKind
{
    Output,
    Input
};

struct DecoratorInfo {
    std::string Type;  // 예: "Repeat", "Cooldown", "Inverter"
    std::unordered_map<std::string, std::string> Params;  // 키-값 파라미터
};

struct Node;


struct Pin
{
    ed::PinId   ID;
    ::Node* Node;
    std::string Name;
    PinType     Type;
    PinKind     Kind;

    Pin(int id, const char* name, PinType type);
};


struct Node
{
    ed::NodeId ID;
    std::string Name;
    std::vector<Pin> Inputs;
    std::vector<Pin> Outputs;

    std::vector<DecoratorInfo> Decorators;

    ImColor Color;
    NodeType Type;
    ImVec2 Size;

    std::string State;
    std::string SavedState;

    Node(int id, const char* name, ImColor color = ImColor(255, 255, 255));
    void Render();
};

struct Link
{
    ed::LinkId ID;

    ed::PinId StartPinID;
    ed::PinId EndPinID;

    ImColor Color;

    Link(ed::LinkId id, ed::PinId startPinId, ed::PinId endPinId);
};


bool CanCreateLink(Pin* a, Pin* b);