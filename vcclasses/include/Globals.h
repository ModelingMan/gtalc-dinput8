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
	extern char *String_DigitalClock;

	extern unsigned short &MI_SINGLESTREETLIGHTS1;
	extern unsigned short &MI_DOUBLESTREETLIGHTS;
	extern unsigned short &MI_CARMINE;
	extern unsigned short &MI_NAUTICALMINE;
	extern unsigned short &MI_PICKUP_ADRENALINE;
	extern unsigned short &MI_PICKUP_BODYARMOUR;
	extern unsigned short &MI_PICKUP_INFO;
	extern unsigned short &MI_PICKUP_HEALTH;
	extern unsigned short &MI_PICKUP_BONUS;
	extern unsigned short &MI_PICKUP_BRIBE;
	extern unsigned short &MI_PICKUP_KILLFRENZY;
	extern unsigned short &MI_PICKUP_CAMERA;
	extern unsigned short &MI_LITTLEHA_POLICE;
	extern unsigned short &MI_LIGHTBEAM;
	extern short *WeatherTypesList;
	extern RwTexture *&gpWhiteTexture;

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
	extern CProjectileInfo *gaProjectileInfo;
	extern wchar_t *gUString2;
	extern CPhoneInfo &gPhoneInfo;
	extern wchar_t *gUString;
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

	void MatchModelString(char *, unsigned short);
	void InitModelIndices(void);
	void VehicleCheat(int);
	float FindPlayerHeading(void);
	CPlayerPed *FindPlayerPed(void);
	CVehicle *FindPlayerVehicle(void);
	CVector *FindPlayerCoors(CVector *);
	CVector *CrossProduct(CVector *, CVector const &, CVector const &);
	void DefinedState(void);
	char *strcpy(char *dest, const char *src);
	char *strncpy(char *dest, const char *src, size_t n);
	char *strcat(char *dest, const char *src);
	int strcmp(const char *s1, const char *s2);
	int strncmp(const char *s1, const char *s2, size_t n);
	int sprintf(char *s, const char *format, ...);
	int rand(void);
	int sscanf(const char *s, const char *format, ...);
}
