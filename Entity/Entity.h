#pragma once
#include "Game.h"
#include "View.hpp"
#include "Bone.h"

template <typename T>
inline bool GetDataAddressWithOffset(const DWORD64& Address, DWORD Offset, T& Data)
{
	if (Address == 0)
		return false;

	if (!m.ReadMemory<T>(Address + Offset, Data))
		return false;

	return true;
}

struct C_UTL_VECTOR
{
	DWORD64 Count = 0;
	DWORD64 Data = 0;
};

class PlayerController
{
public:
	DWORD64 Address = 0;
	int TeamID = 0;
	int Health = 0;
	int AliveStatus = 0;
	DWORD Pawn = 0;
	std::string PlayerName;

public:
	bool GetTeamID();
	bool GetHealth();
	bool GetIsAlive();
	bool GetPlayerName();

	DWORD64 GetPlayerPawnAddress();
};


class PlayerPawn
{
public:
	enum class Flags
	{
		NONE,
		IN_AIR = 1 << 0
	};
	
	DWORD64 Address = 0;
	CBone BoneData;
	Vec2 ViewAngle;
	Vec3 Pos;
	Vec3 CameraPos;
	DWORD ShotsFired;
	Vec2 AimPunchAngle;
	C_UTL_VECTOR AimPunchCache;
	DWORD64 bSpottedByMask;
	Vec2 ScreenPos;
	int Health;
	int TeamID;
	int Fov;
	int fFlags;

	bool GetPos();
	bool GetViewAngle();
	bool GetCameraPos();
	bool GetFov();
	bool GetSpotted();
	bool GetShotsFired();
	bool GetAimPunchAngle();
	bool GetAimPunchCache();
	bool GetFFlags();
	bool GetHealth();
	bool GetTeamID();

	constexpr bool HasFlag(const Flags Flag) const noexcept {
		return fFlags & (int)Flag;
	}


};
class CEntity
{
public:
	PlayerController Controller;

	PlayerPawn Pawn;

	bool UpdateController(const DWORD64& PlayerControllerAddress);

	bool UpdatePawn(const DWORD64& PlayerPawnAddress);

	bool IsAlive();

	bool IsInScreen();

	CBone GetBone() const;


};