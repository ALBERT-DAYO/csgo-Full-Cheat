#include "Game.h"

bool CGame::InitAddress()
{
	this->Address.ClientDLL = m.Client_DLL;
	this->Address.LocalPawn = GetClientDLLAddress() + Offset::LocalPlayerPawn;
	this->Address.ForceJump = GetClientDLLAddress() + Offset::ForceJump;
	this->Address.EntityList = GetClientDLLAddress() + Offset::EntityList;
	this->Address.LocalController = GetClientDLLAddress() + Offset::LocalPlayerController;
	this->Address.Matrix = GetClientDLLAddress() + Offset::Matrix;
	this->Address.ViewAngle = GetClientDLLAddress() + Offset::ViewAngle;

	return this->Address.ClientDLL != 0;
}

DWORD64 CGame::GetViewAngleAddress()
{
	return this->Address.ViewAngle;
}

DWORD64 CGame::GetEntityListAddress()
{
	return this->Address.EntityList;
}
DWORD64 CGame::GetMatrixAddress()
{
	return this->Address.Matrix;
}
DWORD64 CGame::GetEntityListEntry()
{
	return this->Address.EntityListEntry;
}
DWORD64 CGame::GetLocalControllerAddress()
{
	return this->Address.LocalController;
}

bool CGame::UpdateEntityListEntry()
{
	DWORD64 EntityListEntry = 0;
	if (!m.ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityListEntry))
		return false;
	if (!m.ReadMemory<DWORD64>(EntityListEntry + 0x10, EntityListEntry))
		return false;

	this->Address.EntityListEntry = EntityListEntry;

	return this->Address.EntityListEntry != 0;
}

DWORD64 CGame::GetClientDLLAddress()
{
	return this->Address.ClientDLL;
}


DWORD64 CGame::GetLocalPawnAddress()
{
	return this->Address.LocalPawn;
}


bool CGame::SetForceJump(int value)
{
	if (!m.WriteMemory<int>(this->Address.ForceJump, value))
		return false;

	return true;
}
bool CGame::GetForceJump(int& value)
{
	if (!m.ReadMemory<int>(this->Address.ForceJump, value))
		return false;

	return true;
}