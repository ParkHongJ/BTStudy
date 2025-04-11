#include "Node.h"


Pin* newNodeLinkPin = nullptr;
Pin* newLinkPin = nullptr;


Pin::Pin(int id, const char* name, PinType type) :
    ID(id), Node(nullptr), Name(name), Type(type), Kind(PinKind::Input)
{
}

Node::Node(int id, const char* name, ImColor color) :
    ID(id), Name(name), Color(color), Type(NodeType::None), Size(0, 0)
{
}


Link::Link(ed::LinkId id, ed::PinId startPinId, ed::PinId endPinId) :
    ID(id), StartPinID(startPinId), EndPinID(endPinId), Color(255, 255, 255)
{
}



void Node::Render()
{
    const float rounding = 5.0f;
    const float padding = 12.0f;

    const auto pinBackground = ed::GetStyle().Colors[ed::StyleColor_NodeBg];

    ed::PushStyleColor(ed::StyleColor_NodeBg, ImColor(128, 128, 128, 200));
    ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(32, 32, 32, 200));
    ed::PushStyleColor(ed::StyleColor_PinRect, ImColor(60, 180, 255, 150));
    ed::PushStyleColor(ed::StyleColor_PinRectBorder, ImColor(60, 180, 255, 150));

    ed::PushStyleVar(ed::StyleVar_NodePadding, ImVec4(0, 0, 0, 0));
    ed::PushStyleVar(ed::StyleVar_NodeRounding, rounding);
    ed::PushStyleVar(ed::StyleVar_SourceDirection, ImVec2(0.0f, 1.0f));
    ed::PushStyleVar(ed::StyleVar_TargetDirection, ImVec2(0.0f, -1.0f));
    ed::PushStyleVar(ed::StyleVar_LinkStrength, 0.0f);
    ed::PushStyleVar(ed::StyleVar_PinBorderWidth, 1.0f);
    ed::PushStyleVar(ed::StyleVar_PinRadius, 5.0f);

#pragma region 노드 그리기
    ed::BeginNode(ID);

    ImGui::BeginVertical(ID.AsPointer());
#pragma region Inputs
    ImGui::BeginHorizontal("inputs");
    ImGui::Spring(0, padding * 2);

    ImRect inputsRect;
    int inputAlpha = 200;
    if (!Inputs.empty())
    {
        auto& pin = Inputs[0];
        ImGui::Dummy(ImVec2(0, padding));
        ImGui::Spring(1, 0);
        inputsRect = ImGui_GetItemRect();

        ed::PushStyleVar(ed::StyleVar_PinArrowSize, 10.0f);
        ed::PushStyleVar(ed::StyleVar_PinArrowWidth, 10.0f);
        ed::PushStyleVar(ed::StyleVar_PinCorners, ImDrawFlags_RoundCornersBottom);
        ed::BeginPin(pin.ID, ed::PinKind::Input);
        ed::PinPivotRect(inputsRect.GetTL(), inputsRect.GetBR());
        ed::PinRect(inputsRect.GetTL(), inputsRect.GetBR());
        ed::EndPin();
        ed::PopStyleVar(3);

        if (newLinkPin && !CanCreateLink(newLinkPin, &pin) && &pin != newLinkPin)
            inputAlpha = (int)(255 * ImGui::GetStyle().Alpha * (48.0f / 255.0f));
    }
    else
        ImGui::Dummy(ImVec2(0, padding));

    ImGui::Spring(0, padding * 2);
    ImGui::EndHorizontal();
#pragma endregion Inputs
#pragma region ContentFrame

    ImGui::BeginHorizontal("content_frame");
    ImGui::Spring(1, padding);

#pragma region Content

    ImGui::BeginVertical("content", ImVec2(0.0f, 0.0f));

    int decoratorCount = Decorators.size();
    float decoratorHeight = 24.0f;

    ImGui::Dummy(ImVec2(160, (float)decoratorCount * decoratorHeight));  // Node 위 공간을 확보
    ImGui::Spring(1);
    ImGui::TextUnformatted(Name.c_str());

    ImGui::Spring(1);
    ImGui::EndVertical();

#pragma endregion Content

    auto contentRect = ImGui_GetItemRect();
    ImGui::Spring(1, padding);
    ImGui::EndHorizontal();

#pragma endregion ContentFrame

#pragma region Outputs
    ImGui::BeginHorizontal("outputs");
    ImGui::Spring(0, padding * 2);

    ImRect outputsRect;
    int outputAlpha = 200;
    if (!Outputs.empty())
    {
        auto& pin = Outputs[0];
        ImGui::Dummy(ImVec2(0, padding));
        ImGui::Spring(1, 0);
        outputsRect = ImGui_GetItemRect();

        ed::PushStyleVar(ed::StyleVar_PinCorners, ImDrawFlags_RoundCornersTop);
        ed::BeginPin(pin.ID, ed::PinKind::Output);
        ed::PinPivotRect(outputsRect.GetTL(), outputsRect.GetBR());
        ed::PinRect(outputsRect.GetTL(), outputsRect.GetBR());
        ed::EndPin();
        ed::PopStyleVar();

        if (newLinkPin && !CanCreateLink(newLinkPin, &pin) && &pin != newLinkPin)
            outputAlpha = (int)(255 * ImGui::GetStyle().Alpha * (48.0f / 255.0f));
    }
    else
        ImGui::Dummy(ImVec2(0, padding));

    ImGui::Spring(0, padding * 2);
    ImGui::EndHorizontal();
#pragma endregion Outputs

    ImGui::EndVertical();
    ed::EndNode();

#pragma endregion 노드 그리기
    ed::PopStyleVar(7);
    ed::PopStyleColor(4);

    // 이걸로 해당 노드 영역의 drawList를 받아오고
    auto drawList = ed::GetNodeBackgroundDrawList(ID);

    const auto topRoundCornersFlags = ImDrawFlags_RoundCornersTop;
    const auto bottomRoundCornersFlags = ImDrawFlags_RoundCornersBottom;

    if (ImGui::IsKeyPressed(VK_ADD) && ed::IsNodeSelected(ID))
    {
        if (Type == NodeType::Composite)
        {
            //TODO Deco추가
            DecoratorInfo decoInfo;
            decoInfo.Type = "DecoInfo";
            Decorators.push_back(decoInfo);
        }
        ImGui::OpenPopup("Create New Node");
    }

#pragma region 데코레이터 박스 개별적으로 그리기
    for (int i = 0; i < decoratorCount; ++i)
    {
        ImVec2 dTL = contentRect.GetTL() + ImVec2(0, i * decoratorHeight);
        ImVec2 dBR = dTL + ImVec2(contentRect.GetWidth(), decoratorHeight);

        drawList->AddRectFilled(dTL, dBR, IM_COL32(200, 140, 50, 180), 4.0f);
        drawList->AddText(dTL + ImVec2(6, 4), IM_COL32_WHITE, Decorators[i].Type.c_str());
    }
#pragma endregion 데코레이터 박스 개별적으로 그리기

#pragma region 핀 그리기
    drawList->AddRectFilled(inputsRect.GetTL() + ImVec2(0, 1), inputsRect.GetBR(),
        IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), inputAlpha), 4.0f, bottomRoundCornersFlags);
    drawList->AddRect(inputsRect.GetTL() + ImVec2(0, 1), inputsRect.GetBR(),
        IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), inputAlpha), 4.0f, bottomRoundCornersFlags);
    drawList->AddRectFilled(outputsRect.GetTL(), outputsRect.GetBR() - ImVec2(0, 1),
        IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), outputAlpha), 4.0f, topRoundCornersFlags);
    drawList->AddRect(outputsRect.GetTL(), outputsRect.GetBR() - ImVec2(0, 1),
        IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), outputAlpha), 4.0f, topRoundCornersFlags);
#pragma endregion 핀 그리기            


#pragma region 메인노드 상자그리기
    drawList->AddRectFilled(
        contentRect.GetTL() + ImVec2(0.f, (float)decoratorCount * decoratorHeight),
        contentRect.GetBR(), IM_COL32(24, 64, 128, 200), 0.0f);

    drawList->AddRect(
        contentRect.GetTL() + ImVec2(0.f, (float)decoratorCount * decoratorHeight),
        contentRect.GetBR(),
        IM_COL32(48, 128, 255, 100), 0.0f);
#pragma endregion 메인노드 상자그리기
}



bool CanCreateLink(Pin* a, Pin* b)
{
    if (!a || !b || a == b || a->Kind == b->Kind || a->Type != b->Type || a->Node == b->Node)
        return false;

    return true;
}