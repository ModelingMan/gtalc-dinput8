#pragma once

#include "vcclasses.h"

namespace VCGlobals
{
	extern CCamera &TheCamera;
	extern CText &TheText;
	extern cDMAudio &DMAudio;
	extern cSampleManager &SampleManager;
	extern cAudioManager &AudioManager;
	extern CPathFind &ThePaths;

	extern char *ScrollCharSet;

	extern unsigned short &MI_CARMINE;
	extern unsigned short &MI_NAUTICALMINE;
	extern unsigned short &MI_LITTLEHA_POLICE;
	extern unsigned short &MI_LIGHTBEAM;

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
	extern CPhoneInfo &gPhoneInfo;
	extern RwTexture *&gpShadowHeliTex;
	extern RwTexture *&gpShadowExplosionTex;
	extern RwTexture *&gpShadowCarTex;
	struct RsGlobalType
	{
		const char *appName;
		int windowWidth;
		int windowHeight;
		int currentWidth;
		int currentHeight;
		unsigned int frameLimit;
		int quit;
		void *ps;
		void *keyboard;
		void *mouse;
		void *pad;
	};
	extern RsGlobalType &RsGlobal;
	extern RwTexture *&gpShadowPedTex;
	extern RwTexture *&gpBloodPoolTex;
	extern RwTexture *&gpShadowHeadLightsTex;
	extern bool &gbFastTime;

	void VehicleCheat(int);
	CPlayerPed *FindPlayerPed(void);
	CVehicle *FindPlayerVehicle(void);
	CVector *FindPlayerCoors(CVector *);
	char *strcpy(char *dest, const char *src);
	char *strncpy(char *dest, const char *src, size_t n);
	int sprintf(char *s, const char *format, ...);
	int rand(void);
	int sscanf(const char *s, const char *format, ...);
}
