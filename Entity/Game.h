#pragma once
#include "../Utils/Memory/Memory.h"
#include "Offsets.h"
#include "View.hpp"

class CGame
{
private:
	struct
	{
		DWORD64 EntityListEntry;
		DWORD64 LocalController;
		DWORD64 EntityList;
		DWORD64 Matrix;
		DWORD64 ViewAngle;
		DWORD64 ClientDLL;
		DWORD64 LocalPawn;
		DWORD64 ForceJump;
	}Address;

public:
	CView View;

	bool InitAddress();
	DWORD64 GetViewAngleAddress();
	DWORD64 GetClientDLLAddress();
	DWORD64 GetMatrixAddress();
	DWORD64 GetLocalPawnAddress();
	DWORD64 GetEntityListAddress();
	DWORD64 GetEntityListEntry();
	DWORD64 GetLocalControllerAddress();

	bool UpdateEntityListEntry();

	bool SetForceJump(int Value);
	bool GetForceJump(int& Value);

};

inline CGame gGame;
