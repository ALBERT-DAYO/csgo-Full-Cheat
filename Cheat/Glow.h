#pragma once

#include "../Entity/Entity.h"
#include "..\MenuConfig.hpp"

namespace Glow
{
	void Run(const CEntity& aLocalPlayer)
	{
		float on = 86400.f;
		float off = 0.f;
		if (!MenuConfig::Glow)
		{
			m.WriteMemory(aLocalPlayer.Pawn.Address + Offset::Entity.EnemySensor, off);
		}
		else {
			m.WriteMemory(aLocalPlayer.Pawn.Address + Offset::Entity.EnemySensor, on);
		}

	}
}