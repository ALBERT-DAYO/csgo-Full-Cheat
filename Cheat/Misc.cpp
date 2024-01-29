#include "Misc.h"

namespace Misc
{
	void FovChanger(const CEntity& aLocalPlayer) noexcept
	{
		DWORD64 CameraServices = 0;
		UINT CurrentFOV;
		bool isScoped;
		if (!m.ReadMemory<DWORD64>(aLocalPlayer.Pawn.Address + Offset::Pawn.CameraServices, CameraServices))
			return;

		
		 m.ReadMemory(CameraServices + Offset::Pawn.iFov, CurrentFOV);
		
		 int Dfov = MiscCFG::Fov;

		m.ReadMemory(aLocalPlayer.Pawn.Address + Offset::Pawn.isScoped, isScoped);
		if (!isScoped&&CurrentFOV!= Dfov)
		{
			m.WriteMemory<int>(CameraServices + Offset::Pawn.iFov, Dfov);
		}
	}
}