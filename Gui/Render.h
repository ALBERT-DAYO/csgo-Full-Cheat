#pragma once
#include "overlay.h"
#include "../Entity/Entity.h"
#include <map>
#include "../Utils/Format.h"
#include "../Cheat/TriggerBot.h"
#include "../Cheat/AimBot.h"

void Overlay::m_Menu()

{
    ImGui::SetNextWindowSize({ 700, 700 }, 0);

    ImGui::Begin("##NULL", (bool*)NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::BeginChild("##SelectMenu", ImVec2(700.f, 60.f));

    static int menu = 0;

    if (ImGui::Button("Aim", ImVec2(230.f, 50.f)))
        menu = 0;
    ImGui::SameLine();
    if (ImGui::Button("ESP", ImVec2(230.f, 50.f)))
        menu = 1;
    ImGui::SameLine();
    if (ImGui::Button("Misc", ImVec2(230.f, 50.f)))
        menu = 2;

    ImGui::EndChild();


    ImGui::BeginChild("##MainMenu", ImVec2(700.f, 700.f));
    ImGui::NewLine();


    switch (menu)
    {
    case 0:
        ImGui::Text("AIM");
        ImGui::Separator();

        ImGui::Text("Aimbot");
        ToggleButton("Aimbot", &MenuConfig::AimBot);

        if (MenuConfig::AimBot)
        {
            float FovMin = 0.f, FovMax = 25.f;
            float SmoothMin = 0.f, SmoothMax = 5.f;
            
            ImGui::Text("Hotkey");
            ImGui::SameLine();
            if (ImGui::Combo("###AimKey", &MenuConfig::AimBotHotKey, "LALT\0LBUTTON\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL\0"))
            {
                AimControl::SetHotKey(MenuConfig::AimBotHotKey);
            }
            ImGui::Checkbox("Draw FOV", &ESPConfig::DrawFov);
            ImGui::SameLine();
            ImGui::ColorEdit4("##FOVColor", reinterpret_cast<float*>(&ESPConfig::FovCircleColor), ImGuiColorEditFlags_NoInputs);

            ImGui::SliderFloat("FOV:", &AimControl::AimFov, FovMin, FovMax, "%.1f");
            ImGui::SliderFloat("Smooth:", &AimControl::Smooth, SmoothMin, SmoothMax, "%.1f");

            ImGui::Checkbox("Enable RCS", &MenuConfig::RCS);
            ImGui::Checkbox("Visible Only", &MenuConfig::VisibleCheck);

            ImGui::Text("Bone");
            ImGui::SameLine();
            if (ImGui::Combo("###AimPos", &MenuConfig::AimPosition, "Head\0Neck\0Chest\0Penis\0"))
            {
                switch (MenuConfig::AimPosition)
                {
                case 0:
                    MenuConfig::AimPositionIndex = BONEINDEX::head;
                    break;
                case 1:
                    MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
                    break;
                case 2:
                    MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
                    break;
                case 3:
                    MenuConfig::AimPositionIndex = BONEINDEX::pelvis;
                    break;
                default:
                    break;
                }
            }
        }

        ImGui::Text("Triggerbot");

        ToggleButton("##ESP Triggerbot", &MenuConfig::TriggerBot);

        if (MenuConfig::TriggerBot)
        {
            int DelayMin = 10, DelayMax = 1000;
            int DurationMin = 0, DurationMax = 1000;
            if (!MenuConfig::TriggerAlways)
            {               
                    ImGui::Text("HotKeyList");
                    ImGui::SameLine();
                    if (ImGui::Combo("###TriggerbotKey", &MenuConfig::TriggerHotKey, "LALT\0LBUTTON\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL\0"))
                    {
                        TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
                    }
                
            }
            ImGui::Text("Always Active");
            ToggleButton("Always Active", &MenuConfig::TriggerAlways);
            ImGui::SliderInt("Shot Delay:", &TriggerBot::TriggerDelay, DelayMin, DelayMax, "%d ms");
            ImGui::SliderInt("Shot Duration:", &TriggerBot::FakeShotDelay, DurationMin, DurationMax, "%d ms");
        }

        break;
    case 1:
        ImGui::Text("ESP");
        ImGui::Separator();

        ToggleButton("ESP Enabled", &ESPConfig::ESPenbled);

        ImGui::Checkbox("ESPBox", &ESPConfig::ShowBoxESP);
        ImGui::SameLine();
        ImGui::ColorEdit4("##BoxColor", reinterpret_cast<float*>(&ESPConfig::BoxColor), ImGuiColorEditFlags_NoInputs);
        ImGui::SameLine();
        ImGui::Combo("##BoxStyle", &MenuConfig::BoxType, "Normal\0Edge\0Corner\0Corner Edge\0");

        ImGui::Checkbox("HealthBar", &ESPConfig::ShowHealthBar);
        ImGui::SameLine();
        ImGui::Combo("##BarStyle", &MenuConfig::HealthBarType, "Vertical\0Top\0");

        ImGui::Checkbox("BoneEsp", &ESPConfig::ShowBoneESP);
        ImGui::SameLine();
        ImGui::ColorEdit4("##BoneColor", reinterpret_cast<float*>(&ESPConfig::BoneColor), ImGuiColorEditFlags_NoInputs);

        ImGui::Checkbox("SnapLine", &ESPConfig::ShowLineToEnemy);
        ImGui::SameLine();
        ImGui::ColorEdit4("##LineToEnemyColor", reinterpret_cast<float*>(&ESPConfig::LineToEnemyColor), ImGuiColorEditFlags_NoInputs);
        ImGui::SameLine();
        ImGui::Combo("LinePosList", &MenuConfig::LinePos, "Top\0Center\0Bottom\0");

        ImGui::Checkbox("PlayerName", &ESPConfig::ShowPlayerName);
        ImGui::Checkbox("ShowHealthNum", &ESPConfig::ShowHealthNum);
        ImGui::Checkbox("ShowDistance", &ESPConfig::ShowDistance);
        break;
    case 2:
        ImGui::Text("Misc");
        ImGui::Separator();

        ImGui::Checkbox("BHOP", &MiscCFG::BunnyHop);
        ImGui::Checkbox("Glow", &MenuConfig::Glow);
        ImGui::Checkbox("TeamCheack", &MenuConfig::TeamCheck);
        ImGui::SliderInt("FOV: ", &MiscCFG::Fov, 50, 180, "%.1d");
        break;

    default:
        break;
    }

    ImGui::EndChild();

    ImGui::End();
}
namespace Render {

    void DrawFovCircle(const CEntity& LocalEntity)
    {
        if (!ESPConfig::DrawFov)
            return;

        Vec2 CenterPoint = { (float)Overlay::GameSize.right / 2,(float)Overlay::GameSize.bottom / 2 };
        float Radius = tan(AimControl::AimFov / 180.f * M_PI / 2.f) / tan(LocalEntity.Pawn.Fov / 180.f * M_PI / 2.f) * (float)Overlay::GameSize.right;
        Overlay::Circle(CenterPoint, Radius, ESPConfig::FovCircleColor, 1);
    }

    void DrawHealth(const CEntity& Entity, ImVec4 Rect)
    {
        if (!ESPConfig::ShowHealthNum)
            return;

        int health = Entity.Pawn.Health;
        std::string health_str = Format("%i", health);
        Overlay::StrokeText(health_str, { Rect.x + 2, Rect.y }, ImColor(0, 220, 0, 255), 12, false);
    }

    void DrawDistance(const CEntity& LocalEntity, CEntity& Entity, ImVec4 Rect)
    {
        if (!ESPConfig::ShowDistance)
            return;

        int distance = static_cast<int>(Entity.Pawn.Pos.DistanceTo(LocalEntity.Pawn.Pos) / 100);
        std::string dis_str = Format("%im", distance);
        Overlay::StrokeText(dis_str, { Rect.x + Rect.z + 4, Rect.y }, ImColor(255, 204, 0, 255), 14, false);
    }




    ImVec4 Get2DBox(const CEntity& Entity)
    {
        BoneJointPos Head = Entity.GetBone().BonePosList[BONEINDEX::head];

        Vec2 Size, Pos;
        Size.y = (Entity.Pawn.ScreenPos.y - Head.ScreenPos.y) * 1.09;
        Size.x = Size.y * 0.6;

        Pos = ImVec2(Entity.Pawn.ScreenPos.x - Size.x / 2, Head.ScreenPos.y - Size.y * 0.08);

        return ImVec4{ Pos.x,Pos.y,Size.x,Size.y };
    }


    ImVec4 Get2DBoneRect(const CEntity& Entity)
    {
        Vec2 Min, Max, Size;
        Min = Max = Entity.GetBone().BonePosList[0].ScreenPos;

        for (auto& BoneJoint : Entity.GetBone().BonePosList)
        {
            if (!BoneJoint.IsVisible)
                continue;
            Min.x = min(BoneJoint.ScreenPos.x, Min.x);
            Min.y = min(BoneJoint.ScreenPos.y, Min.y);
            Max.x = max(BoneJoint.ScreenPos.x, Max.x);
            Max.y = max(BoneJoint.ScreenPos.y, Max.y);
        }
        Size.x = Max.x - Min.x;
        Size.y = Max.y - Min.y;

        return ImVec4(Min.x, Min.y, Size.x, Size.y);
    }

    void DrawBone(const CEntity& Entity, ImColor Color, float Thickness)
    {
        if (!ESPConfig::ShowBoneESP)
            return;

        BoneJointPos Previous, Current;
        for (auto i : BoneJointList::List)
        {
            Previous.Pos = Vec3(0, 0, 0);
            for (auto Index : i)
            {
                Current = Entity.GetBone().BonePosList[Index];
                if (Previous.Pos == Vec3(0, 0, 0))
                {
                    Previous = Current;
                    //pGame->View->Gui->Text(Current.Name.c_str(), Current.ScreenPos, ImColor(255, 255, 0, 255));
                    continue;
                }
                if (Previous.IsVisible && Current.IsVisible)
                {
                    Overlay::Line(Previous.ScreenPos, Current.ScreenPos, Color, Thickness);
                    //pGame->View->Gui->Text(Current.Name.c_str(), Current.ScreenPos, ImColor(255, 255, 0, 255));
                }
                Previous = Current;
            }
        }
    }

    void LineToEnemy(ImVec4 Rect, ImColor Color, float Thickness)
    {
        if (!ESPConfig::ShowLineToEnemy)
            return;

        switch (MenuConfig::LinePos)
        {
        case 0:
            Overlay::Line({ Rect.x + Rect.z / 2,Rect.y }, { (float)Overlay::GameSize.right / 2,0 }, Color, Thickness);
            break;
        case 1:
            Overlay::Line({ Rect.x + Rect.z / 2,Rect.y }, { (float)Overlay::GameSize.right / 2, (float)Overlay::GameSize.bottom / 2 }, Color, Thickness);
            break;
        case 2:
            Overlay::Line({ Rect.x + Rect.z / 2,Rect.y }, { (float)Overlay::GameSize.right / 2, (float)Overlay::GameSize.bottom }, Color, Thickness);
            break;
        default:
            break;
        }

    }

    class HealthBar
    {


    private:



        float MaxHealth = 0.f;

        float CurrentHealth = 0.f;



        ImVec2 RectPos{};

        ImVec2 RectSize{};


    public:
        HealthBar() {}

        void DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size);

        void DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size);
    private:

        ImColor Mix(ImColor Col_1, ImColor Col_2, float t);

        ImColor FirstStageColor = ImColor(96, 246, 113, 220);

        ImColor SecondStageColor = ImColor(247, 214, 103, 220);

        ImColor ThirdStageColor = ImColor(255, 95, 95, 220);

        ImColor BackupHealthColor = ImColor(255, 255, 255, 220);

        ImColor FrameColor = ImColor(45, 45, 45, 220);

        ImColor BackGroundColor = ImColor(90, 90, 90, 220);
    };

    void HealthBar::DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size)
    {
        auto InRange = [&](float value, float min, float max) -> bool
            {
                return value > min && value <= max;
            };

        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

        this->MaxHealth = MaxHealth;
        this->CurrentHealth = CurrentHealth;
        this->RectPos = Pos;
        this->RectSize = Size;


        float Proportion = CurrentHealth / MaxHealth;

        float Width = RectSize.x * Proportion;

        ImColor Color;


        DrawList->AddRectFilled(RectPos,
            { RectPos.x + RectSize.x,RectPos.y + RectSize.y },
            BackGroundColor, 5, 15);


        float Color_Lerp_t = pow(Proportion, 2.5);
        if (InRange(Proportion, 0.5, 1))
            Color = Mix(FirstStageColor, SecondStageColor, Color_Lerp_t * 3 - 1);
        else
            Color = Mix(SecondStageColor, ThirdStageColor, Color_Lerp_t * 4);



        DrawList->AddRectFilled(RectPos,
            { RectPos.x + Width,RectPos.y + RectSize.y },
            Color, 5);


        DrawList->AddRect(RectPos,
            { RectPos.x + RectSize.x,RectPos.y + RectSize.y },
            FrameColor, 5, 15, 1);
    }

    void HealthBar::DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size)
    {
        auto InRange = [&](float value, float min, float max) -> bool
            {
                return value > min && value <= max;
            };

        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

        this->MaxHealth = MaxHealth;
        this->CurrentHealth = CurrentHealth;
        this->RectPos = Pos;
        this->RectSize = Size;


        float Proportion = CurrentHealth / MaxHealth;

        float Height = RectSize.y * Proportion;

        ImColor Color;


        DrawList->AddRectFilled(RectPos,
            { RectPos.x + RectSize.x,RectPos.y + RectSize.y },
            BackGroundColor, 5, 15);


        float Color_Lerp_t = pow(Proportion, 2.5);
        if (InRange(Proportion, 0.5, 1))
            Color = Mix(FirstStageColor, SecondStageColor, Color_Lerp_t * 3 - 1);
        else
            Color = Mix(SecondStageColor, ThirdStageColor, Color_Lerp_t * 4);




        DrawList->AddRectFilled({ RectPos.x,RectPos.y + RectSize.y - Height },
            { RectPos.x + RectSize.x,RectPos.y + RectSize.y },
            Color, 5);


        DrawList->AddRect(RectPos,
            { RectPos.x + RectSize.x,RectPos.y + RectSize.y },
            FrameColor, 5, 15, 1);
    }

    ImColor HealthBar::Mix(ImColor Col_1, ImColor Col_2, float t)
    {
        ImColor Col;
        Col.Value.x = t * Col_1.Value.x + (1 - t) * Col_2.Value.x;
        Col.Value.y = t * Col_1.Value.y + (1 - t) * Col_2.Value.y;
        Col.Value.z = t * Col_1.Value.z + (1 - t) * Col_2.Value.z;
        Col.Value.w = Col_1.Value.w;
        return Col;
    }

    void DrawHealthBar(DWORD Sign, float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool Horizontal)
    {
        static std::map<DWORD, HealthBar> HealthBarMap;
        if (!HealthBarMap.count(Sign))
        {
            HealthBarMap.insert({ Sign,HealthBar() });
        }
        if (HealthBarMap.count(Sign))
        {
            if (Horizontal)
                HealthBarMap[Sign].DrawHealthBar_Horizontal(MaxHealth, CurrentHealth, Pos, Size);
            else
                HealthBarMap[Sign].DrawHealthBar_Vertical(MaxHealth, CurrentHealth, Pos, Size);
        }
    }



}