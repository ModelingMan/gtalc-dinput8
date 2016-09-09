#pragma once

#include "vcclasses.h"

namespace VCGlobals
{
	extern CCamera &TheCamera;
	extern CText &TheText;
	extern cDMAudio &DMAudio;
	extern cSampleManager &SampleManager;
	extern cAudioManager &AudioManager;
	extern CPhoneInfo &ThePhoneInfo;
	extern CMissionCleanup &TheMissionCleanup;
	extern CPathFind &ThePaths;

	extern char *ScrollCharSet;

	extern unsigned short &MI_CARMINE;
	extern unsigned short &MI_NAUTICALMINE;
	extern unsigned short &MI_LITTLEHA_POLICE;
	extern unsigned short &MI_LIGHTBEAM;
	extern unsigned int &resolutionX;
	extern unsigned int &resolutionY;
	extern float &resolutionXMultiplier;
	extern float &resolutionYMultiplier;

	union ScriptParameter
	{
		char int8;
		short int16;
		int int32;
		unsigned char uint8;
		unsigned short uint16;
		unsigned int uint32;
		float float32;
	};
	extern ScriptParameter *ScriptParams;

	struct RsGlobalType
	{
		const char *appName;
		int maximumWidth;
		int maximumHeight;
		int currentWidth;
		int currentHeight;
		int  quit;
		void *ps;
		int keyboard[3];
		int mouse[3];
		int pad[3];
	};
	extern RsGlobalType& Globals;

	CPlayerPed *FindPlayerPed(void);
	CVehicle *FindPlayerVehicle(void);
	CVector *FindPlayerCoors(CVector *);
	char *strcpy(char *dest, const char *src);
	char *strncpy(char *dest, const char *src, size_t n);
	int rand();
	int sscanf(const char *s, const char *format, ...);
}
