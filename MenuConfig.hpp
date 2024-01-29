#pragma once
#include "Entity/Bone.h"
#include "Entity/Game.h"
#include "Utils/Random.h"




namespace MenuConfig
{

	inline bool Active = true;
	inline bool ShowMenu = false;
	inline bool Glow = false;

	inline bool TeamCheck = true;
	inline int BoxType = 0;
	inline int  LinePos = 0;
	inline int HealthBarType = 0;

	inline bool TriggerBot = false;
	inline bool TriggerAlways = false;
	inline int TriggerHotKey = 0;

	inline bool AimBot = false;
	inline bool AimAlways = false;
	inline bool AimToggleMode = false;
	inline int AimBotHotKey = 0;
	inline int  AimPosition = 0;
	inline DWORD  AimPositionIndex = 6;
	inline bool RCS = false;
	inline bool VisibleCheck = false;

	
}
namespace ESPConfig
{
	inline bool ESPenbled = false;
	inline bool ShowBoxESP = false;
	inline float BoxRounding = RandomPara<float>(0.0f, 5.0f);;
	inline bool ShowHealthBar = false;
	inline bool ShowBoneESP = false;
	inline bool ShowLineToEnemy = false;
	inline bool ShowPlayerName = false;
	inline bool ShowDistance = false;
	inline bool ShowHealthNum = false;
	inline bool DrawFov = false;

	inline ImColor FovCircleColor = ImColor(180, 255, 0, 255);
	inline ImColor BoxColor(255, 255, 255, 255);
	inline ImColor BoneColor(255, 255, 255, 255);
	inline ImColor LineToEnemyColor = ImColor(255, 255, 255, 220);

}
namespace CrosshairsCFG
{
	inline bool TeamCheck = true;

	//inline bool isAim = false;
}


namespace MiscCFG
{

	inline bool BunnyHop = true;

	inline bool WorkInSpec = true;

	inline int Fov = 90;

}