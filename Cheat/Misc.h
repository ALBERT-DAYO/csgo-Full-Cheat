#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <time.h>
#include <Windows.h>
#include "AimBot.h"
#include "..\Entity/Entity.h"
#include "..\MenuConfig.hpp"
#include "..\imgui\imgui.h"

namespace Misc
{
	void FovChanger(const CEntity& aLocalPlayer) noexcept;

}