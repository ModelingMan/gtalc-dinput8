#include "CTheZonesHack.h"
#include <Windows.h>
#include "Globals.h"
#include "Offset.h"
#include "SilentCall.h"

static CZone NavigationZoneArray[TOTAL_NAVIG_ZONES];
static bool navigHasBeenInitialised;

bool CTheZonesHack::initialise()
{
	// navigation zones
	navigHasBeenInitialised = false;
	InjectHook(0x004A4C3E, &CTheZonesHack::InitHack);                // CGame::Initialise
	InjectHook(0x004DBCBE, &CTheZonesHack::InitHack);                // CTheZones::LoadAllZones
	Patch<void *>(0x004DC399 + 2, &NavigationZoneArray);             // CTheZones::FindAudioZone
	Patch<void *>(0x004DC430 + 1, &NavigationZoneArray);             // CTheZones::InitialiseAudioZoneArray
	Patch<void *>(0x004DC43A + 1, &NavigationZoneArray);             // CTheZones::InitialiseAudioZoneArray
	Patch<void *>(0x004DC463 + 1, &NavigationZoneArray);             // CTheZones::InitialiseAudioZoneArray
	Patch<unsigned char>(0x004DC472 + 3, TOTAL_NAVIG_ZONES);         // CTheZones::InitialiseAudioZoneArray
	Patch<void *>(0x004DC4B2 + 1, &NavigationZoneArray);             // CTheZones::InitialiseAudioZoneArray
	Patch<unsigned char>(0x004DC4C1 + 3, TOTAL_NAVIG_ZONES);         // CTheZones::InitialiseAudioZoneArray
	Patch<void *>(0x004DCC28 + 1, &NavigationZoneArray);             // CTheZones::GetNavigationZone
	Patch<void *>(0x004DD07A + 2, &NavigationZoneArray->type);       // CTheZones::FindSmallestNavigationZoneForPosition
	Patch<void *>(0x004DD087 + 2, &NavigationZoneArray->type);       // CTheZones::FindSmallestNavigationZoneForPosition
	Patch<void *>(0x004DD090 + 1, &NavigationZoneArray);             // CTheZones::FindSmallestNavigationZoneForPosition
	Patch<void *>(0x004DD09B + 2, &NavigationZoneArray->childZone);  // CTheZones::FindSmallestNavigationZoneForPosition
	Patch<void *>(0x004DD5AF + 2, &NavigationZoneArray);             // CTheZones::FindNextZoneByLabelAndReturnIndex
	Patch<void *>(0x004DD644 + 1, &NavigationZoneArray);             // CTheZones::FindZoneByLabelAndReturnIndex
	Patch<void *>(0x004DDAA6 + 1, &NavigationZoneArray[1]);          // CTheZones::PostZoneCreation
	Patch<void *>(0x004DDAB0 + 1, &NavigationZoneArray);             // CTheZones::PostZoneCreation
	Patch<void *>(0x004DDAB6 + 2, &NavigationZoneArray->childZone);  // CTheZones::PostZoneCreation
	Patch<void *>(0x004DDAC0 + 2, &NavigationZoneArray->parentZone); // CTheZones::PostZoneCreation
	Patch<void *>(0x004DDACA + 2, &NavigationZoneArray->unk);        // CTheZones::PostZoneCreation
	Patch<void *>(0x004DDC60 + 1, &NavigationZoneArray->name);       // CTheZones::CreateZone
	Patch<void *>(0x004DDC82 + 2, &NavigationZoneArray->type);       // CTheZones::CreateZone
	Patch<void *>(0x004DDC88 + 2, &NavigationZoneArray->corner1.x);  // CTheZones::CreateZone
	Patch<void *>(0x004DDC92 + 2, &NavigationZoneArray->corner1.y);  // CTheZones::CreateZone
	Patch<void *>(0x004DDC9C + 2, &NavigationZoneArray->corner1.z);  // CTheZones::CreateZone
	Patch<void *>(0x004DDCA6 + 2, &NavigationZoneArray->corner2.x);  // CTheZones::CreateZone
	Patch<void *>(0x004DDCB0 + 2, &NavigationZoneArray->corner2.y);  // CTheZones::CreateZone
	Patch<void *>(0x004DDCBA + 2, &NavigationZoneArray->corner2.z);  // CTheZones::CreateZone
	Patch<void *>(0x004DDCC0 + 2, &NavigationZoneArray->level);      // CTheZones::CreateZone
	Patch<void *>(0x005FCF50 + 2, &NavigationZoneArray);             // cAudioManager::PlaySuspectLastSeen
	Patch<void *>(0x005FDC16 + 2, &NavigationZoneArray);             // cAudioManager::SetupCrimeReport

	return true;
}

void CTheZonesHack::InitHack()
{
	if (!navigHasBeenInitialised) { // prevents initialising twice by the game
		memset(NavigationZoneArray, 0, sizeof(NavigationZoneArray));
		VCGlobals::strncpy(NavigationZoneArray[0].name, "CITYZON", 8);
		NavigationZoneArray[0].corner1.x = -4000.0 + OFFSETX;
		NavigationZoneArray[0].corner1.y = -4000.0;
		NavigationZoneArray[0].corner1.z = -500.0 + OFFSETZ;
		NavigationZoneArray[0].corner2.x = 4000.0 + OFFSETX;
		NavigationZoneArray[0].corner2.y = 4000.0;
		NavigationZoneArray[0].corner2.z = 500.0 + OFFSETZ;
		NavigationZoneArray[0].level = 0;
		NavigationZoneArray[0].type = 0;
		navigHasBeenInitialised = true;
	}
	CTheZones::Init();
}
