
#include "Gui/Render.h"
#include "Cheat/BunnyHop.h"
#include "Cheat/Glow.h"
#include "Cheat/ESP.h"
#include "Cheat/TriggerBot.h"
#include "Cheat/Aimbot.h"
#include "Cheat/Misc.h"

void Overlay::Cheat()
{
    
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)GameSize.right, (float)GameSize.bottom));
    ImGui::Begin("", (bool*)NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);

	ImGui::Text("CSGO2 Practice Cheat   [%.1f FPS]", ImGui::GetIO().Framerate);
	if (!m.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
		return;

    gGame.UpdateEntityListEntry();

    DWORD64 LocalControllerAddress = 0;

    DWORD64 LocalPawnAddress = 0;

    if (!m.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
        return;
    if (!m.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
        return;

    // LocalEntity
    CEntity LocalEntity;
    if (!LocalEntity.UpdateController(LocalControllerAddress))
        return;
    if (!LocalEntity.UpdatePawn(LocalPawnAddress) && !MiscCFG::WorkInSpec)
        return;
    static int LocalPlayerControllerIndex = 1;
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	float DistanceToSight = 0;
	float MaxAimDistance = 10000;

	Vec3  AimPos{ 0,0,0 };

	for (int i = 0; i < 60; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!m.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.Controller.Address)
		{
			LocalPlayerControllerIndex = i;
			continue;
		}
		
		if (!Entity.UpdateController(EntityAddress))
			continue;
		
		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;
		
		if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;
		if (!Entity.IsAlive())
			continue;

		if (!Entity.IsInScreen())
			continue;
		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ (float)Overlay::GameSize.right / 2,(float)Overlay::GameSize.bottom / 2 });


		if (DistanceToSight < MaxAimDistance)
		{
			MaxAimDistance = DistanceToSight;

			if (!MenuConfig::VisibleCheck ||
				Entity.Pawn.bSpottedByMask & (DWORD64(1) << (LocalPlayerControllerIndex)) ||
				LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << (i)))
			{
				AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
				if (MenuConfig::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;
			}
		}

		

		if (ESPConfig::ESPenbled)
		{

			ImVec4 Rect = ESP::GetBoxRect(Entity, MenuConfig::BoxType);
			ESP::RenderPlayerESP(LocalEntity, Entity, Rect, LocalPlayerControllerIndex, i);
			if (ESPConfig::ShowHealthBar)
			{
				ImVec2 HealthBarPos, HealthBarSize;
				switch (MenuConfig::HealthBarType == 0)
				{
				case 0:
					HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
					HealthBarSize = { 70,8 };
					break;
				case 1:
					HealthBarPos = { Rect.x - 6.f,Rect.y };
					HealthBarSize = { 5 ,Rect.w };
					break;
				}
				Render::DrawHealthBar(EntityAddress, 100, Entity.Pawn.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
			}
			Render::DrawDistance(LocalEntity, Entity, Rect);
			Render::DrawHealth(Entity, Rect);
		}


		Glow::Run(Entity);

	}

	if (MenuConfig::TriggerBot && (GetAsyncKeyState(TriggerBot::HotKey) || MenuConfig::TriggerAlways))
		TriggerBot::Run(LocalEntity);

	if (MenuConfig::AimBot)
	{
		Render::DrawFovCircle(LocalEntity);

		if (MenuConfig::AimAlways)
		{
			if (AimPos != Vec3(0, 0, 0))
			{
				AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
			}
		}
		else
		{
			if (GetAsyncKeyState(AimControl::HotKey))
			{
				if (AimPos != Vec3(0, 0, 0))
				{

					AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
				}
			}
		}

	}
	Misc::FovChanger(LocalEntity);


    Bunnyhop::Run(LocalEntity);

    ImGui::End();
}
