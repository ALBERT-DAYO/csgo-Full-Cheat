#pragma once
#include <chrono>
#include <thread>
#include "../Entity/Entity.h"
#include "../MenuConfig.hpp"

namespace TriggerBot
{
	inline int TriggerDelay = 90; 
	inline int FakeShotDelay = 200; 
	inline int HotKey = VK_LMENU;
	inline std::vector<int> HotKeyList{ VK_LMENU,VK_LBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL };

	inline void SetHotKey(int Index)
	{
		HotKey = HotKeyList.at(Index);
	}

	// Triggerbot
	void ReleaseMouseButton();
	void Run(const CEntity& LocalEntity);
	
}