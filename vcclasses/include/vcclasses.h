#ifndef __VCCLASSES_H__
#define __VCCLASSES_H__

#include "renderware.h"

//########################################################################
//# CVector
//########################################################################

class CVector
{
public:
	float x, y, z;
};

//########################################################################
//# CRGBA
//########################################################################

class CRGBA
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	CRGBA() : r(0), g(0), b(0), a(0){}
	CRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a){}
};

//########################################################################
//# CRect
//########################################################################

class CRect
{
public:
	float left;
	float bottom;
	float right;
	float top;

	CRect() {}
	CRect(float left, float bottom, float right, float top) : left(left), bottom(bottom), right(right), top(top) {}
};

//########################################################################
//# CMatrix
//########################################################################

class CMatrix
{
public:
	CVector right;
	unsigned int flags;
	CVector up;
	unsigned int pad1;
	CVector at;
	unsigned int pad2;
	CVector pos;
	unsigned int pad3;
};

//########################################################################
//# cAudioManager
//########################################################################

class cAudioManager
{
protected:
	unsigned char space1[0x14];		//0x0000
	unsigned int m_Unk13;			//0x0014
	unsigned int m_Unk7;			//0x0018
	unsigned int m_SampleID;		//0x001C
	unsigned char m_Unk0;			//0x0020
	unsigned char m_Unk1;			//0x0021
	unsigned char space2[0x02];		//0x0022
	unsigned int m_Unk2;			//0x0024
	unsigned int m_Frequency;		//0x0028
	unsigned char m_Volume;			//0x002C
	unsigned char space3[0x03];		//0x002D
	float m_Unk3;					//0x0030
	unsigned int m_Unk8;			//0x0034
	unsigned int m_LoopStartOff;	//0x0038
	unsigned int m_LoopEndOff;		//0x003C
	unsigned char m_Unk11;			//0x0040
	unsigned char space6[0x03];		//0x0041
	float m_Unk4;					//0x0044
	float m_Unk5;					//0x0048
	unsigned char m_Unk9;			//0x004C
	unsigned char space8[0x03];		//0x004D
	CVector m_Position;				//0x0050
	unsigned char m_Unk10;			//0x005C
	unsigned char space5;			//0x005D
	unsigned char m_Unk12;			//0x005E
	unsigned char space7[0x05];		//0x005F
	unsigned int m_Unk6;			//0x0064
	unsigned char spaceend[0x54F0];

public:
	void AddSampleToRequestedQueue();
	unsigned char ComputeVolume(unsigned char, float, float);
	float GetDistanceSquared(const CVector &); // INLINED!
	void ProcessLoopingScriptObject(unsigned char);
	unsigned int GetPedCommentSfxFromRange(int &, unsigned long, int, int);
};

//########################################################################
//# CPlaceable
//########################################################################

class CPlaceable
{
protected:
	CMatrix matrix;

public:
	CMatrix &GetMatrix() { return matrix; }
};

//########################################################################
//# CCamera
//########################################################################

class CCamera : public CPlaceable
{
protected:

public:
};

//########################################################################
//# CClock
//########################################################################

class CClock
{
public:
	static unsigned char& ms_nGameClockHours;
	static unsigned char& ms_nGameClockMinutes;
	static unsigned short& ms_nGameClockSeconds;
};

//########################################################################
//# cDMAudio
//########################################################################

class cDMAudio
{
public:
	static int &garageEntity;

	void PlayFrontEndSound(int id, int unk);
	void PlayOneShot(int, unsigned short, float);
};

//########################################################################
//# CFont
//########################################################################

class CFont
{
public:
	static void DrawFonts();
	static void GetNumberOfLines(float x, float y, wchar_t *text);
	static void GetTextRect(CRect *rectOut, float x, float y, wchar_t *text);
	static void Initialise();
	static void PrintString(float x, float y, wchar_t *text);
	static void SetAlphaFade(float alpha);
	static void SetBackGroundOnlyTextOff();
	static void SetBackGroundOnlyTextOn();
	static void SetBackgroundColor(CRGBA *color);
	static void SetBackgroundOff();
	static void SetBackgroundOn();
	static void SetCentreOff();
	static void SetCentreOn();
	static void SetCentreSize(float size);
	static void SetColor(CRGBA *color);
	static void SetDropColor(CRGBA *color);
	static void SetDropShadowPosition(short pos);
	static void SetFontStyle(short style);
	static void SetJustifyOff();
	static void SetJustifyOn();
	static void SetPropOff();
	static void SetPropOn();
	static void SetRightJustifyOff();
	static void SetRightJustifyOn();
	static void SetRightJustifyWrap(float wrap);
	static void SetScale(float x, float y);
	static void SetWrapx(float wrapx);

	struct CharInfo
	{
		char ascii;
		float x;
		float y;
	};
};

//########################################################################
//# CHud
//########################################################################

class CHud
{
public:
	static void SetHelpMessage(wchar_t*, bool, bool);
};

//########################################################################
//# CMessages
//########################################################################

class CMessages
{
public:
	static void AddToPreviousBriefArray(wchar_t *, int, int, int, int, int, int, unsigned short *);
};

//########################################################################
//# CPager
//########################################################################

class CPager
{
protected:
	struct Pager
	{
		wchar_t*		Text;		// Pointer to pager message
		unsigned short	Delay;		// How fast the text scrolls
		unsigned short	Scroll;		// Index of start letter of currently scrolling text
		unsigned short	TextLength;	// Length of the pager message
		unsigned short	Unk1;
		unsigned int	Unk2;
		unsigned short	Unk3;
		unsigned short	Unk4;
		unsigned int	Unk5;
		unsigned int	Unk6;
		unsigned int	Unk7;
		unsigned int	Unk8;
		unsigned int	Unk9;
		unsigned int	Unk10;
	};

	unsigned int MaxLength;	// Maximum length of the pager message. (DEF: 8)
	Pager Pagers[8];	// Queue of a maximum of 8 pager messages.
};

//########################################################################
//# CWanted
//########################################################################

class CWanted
{
public:
	unsigned char space1[0x001E];
	unsigned char activity;       // 0x1E
	unsigned char space2;
	int           level;          // 0x20

	void SetWantedLevelCheat(int);
};

//########################################################################
//# CEntity
//########################################################################

class CEntity
{
public:
	void RegisterReference(CEntity **);
};

//########################################################################
//# CPed
//########################################################################

class CPed : public CEntity
{
public:
	void GiveWeapon(int, unsigned int, bool);
};

//########################################################################
//# CPlayerInfo
//########################################################################

class CPlayerInfo
{
public:
	unsigned char space1[0x00A0];
	unsigned int m_Money;
	unsigned int m_MoneyCounter;
	unsigned int m_HiddenPackagesFound;
	unsigned int m_TotalHiddenPackages;
	unsigned char space2[0x00C0];
};

//########################################################################
//# CPlayerPed
//########################################################################

class CPlayerPed : public CPed
{
public:
	unsigned char space1[0x0244];
	unsigned int state;           // 0x244
	unsigned char space2[0x010C];
	float health;                 // 0x354
	float armour;                 // 0x358
	unsigned char space3[0x0298];
	CWanted *wanted;              // 0x5F4
};

//########################################################################
//# CRunningScript
//########################################################################

class CRunningScript
{
protected:
	// Thanks to CyQ, PatrickW and spookie for this info.
	void *m_pNext;						//0x00
	void *m_pPrev;						//0x04
	char m_strName[8];					//0x08
	unsigned int m_dwScriptIP;			//0x10
	unsigned int m_dwReturnStack[6];	//0x14
	unsigned short m_dwStackPointer;	//0x2C
	unsigned char pad1[2];				//0x2E
	unsigned int m_dwLocalVar[18];		//0x30
	bool m_bStartNewScript;				//0x78
	bool m_bJumpFlag;					//0x79
	bool m_bWorky;						//0x7A
	bool m_bAwake;						//0x7B
	unsigned int m_dwWakeTime;			//0x7C
	unsigned short m_wIfParam;			//0x80
	bool m_bNotFlag;					//0x82
	bool m_bWastedBustedCheck;			//0x83
	bool m_bWastedBustedFlag;			//0x84
	bool m_bMissionThread;				//0x85

	static unsigned long m_pCollectParameters;
	static unsigned long m_pProcessOneCommand;
	static unsigned long m_pUpdateCompareFlag;

	template <class T>
	T SCM_Read(bool bIncreaseIP);
public:
	void CollectParameters(unsigned int *scriptIP, int paramCount);
	bool ProcessOneCommand();
	void UpdateCompareFlag(bool flag);
};

//########################################################################
//# cSampleManager
//########################################################################

class cSampleManager
{
public:
	unsigned int GetSampleBaseFrequency(unsigned int);
	unsigned int GetSampleLoopEndOffset(unsigned int);
	unsigned int GetSampleLoopStartOffset(unsigned int);
};

//########################################################################
//# CSprite2d
//########################################################################

class CSprite2d
{
private:
	void *m_Texture; //RwTexture *

public:
	CSprite2d();
	~CSprite2d();
	void Draw(const CRect& rect, const CRGBA& colour, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void Draw(const CRect& rect, const CRGBA& colour);
	static void DrawRect(const CRect& rect, const CRGBA& colour);
	void SetTexture(char *name, char *maskName);
};

//########################################################################
//# CText
//########################################################################

class CText
{
public:
	wchar_t *Get(const char *);
};

//########################################################################
//# CTheScripts
//########################################################################

class CTheScripts
{
public:
	static unsigned short& CommandsExecuted;
	static unsigned char *ScriptSpace;
};

//########################################################################
//# CTimer
//########################################################################

class CTimer
{
public:
	static unsigned int& m_snTimeInMilliseconds;
	static unsigned int& m_FrameCounter;
};

//########################################################################
//# CTxdStore
//########################################################################

class CTxdStore
{
public:
	static void	AddRef(int);
	static int AddTxdSlot(const char *);
	static int FindTxdSlot(const char *);
	static void LoadTxd(int, const char *);
	static void PopCurrentTxd(void);
	static void PushCurrentTxd(void);
	static void SetCurrentTxd(int);
};

//########################################################################
//# CUserDisplay
//########################################################################

class CUserDisplay
{
public:
	static CPager& Pager;
};

//########################################################################
//# CWorld
//########################################################################

class CWorld
{
public:
	static CPlayerInfo *Players;
	static float FindGroundZForCoord(float x, float y);
};

//########################################################################
//# CScrollBar
//########################################################################

class CScrollBar
{
public:
	unsigned long count;			//0x0
	char *text;						//0x4
	float xStart;					//0x8
	float yStart;					//0x0C
	float zStart;					//0x10
	unsigned long charCount;		//0x14
	unsigned long textLength;		//0x18
	float xEndOffset;				//0x1C
	float yEndOffset;				//0x20
	float zEndOffset;				//0x24
	float thickness;				//0x28
	unsigned char letterBuffer[40];	//0x2C
	unsigned char messageSet;		//0x54
	bool draw;						//0x55
	unsigned char r;				//0x56
	unsigned char g;				//0x57
	unsigned char b;				//0x58
	unsigned char padding[7];		//0x59

	void Init(float xStart, float yStart, float zStart, float xEndOffset, float yEndOffset, float zEndOffset,
		unsigned char messages, unsigned char red, unsigned char green, unsigned char blue, float thickness);
	void Render();
};

//########################################################################
//# CSprite
//########################################################################

class CSprite
{
public:
	static void InitSpriteBuffer();
	static bool CalcScreenCoors(const RwV3d &, RwV3d *, float *, float *, bool);
	static void RenderBufferedOneXLUSprite(float, float, float, float, float, unsigned char, unsigned char, unsigned char, short, float, unsigned char);
	static void FlushSpriteBuffer();
};

//########################################################################
//# CCrane
//########################################################################

class CCrane
{
public:
	unsigned int  object;             // 0x00, pointer to crane object
	unsigned int  hook;               // 0x04, pointer to hook object
	float         pickupX1;           // 0x08
	float         pickupX2;           // 0x0C
	float         pickupY1;           // 0x10
	float         pickupY2;           // 0x14
	float         dropoffX;           // 0x18
	float         dropoffY;           // 0x1C
	float         dropoffZ;           // 0x20
	float         dropoffHeading;     // 0x24
	float         armPickupRotation;  // 0x28
	float         armDropoffRotation; // 0x2C
	float         armPickupDistance;  // 0x30
	float         armDropoffDistance; // 0x34
	float         armPickupHeight;    // 0x38
	float         armDropoffHeight;   // 0x3C
	float         armCurrentRotation; // 0x40
	float         armCurrentDistance; // 0x44
	float         armCurrentHeight;   // 0x48
	float         hookInitialX;       // 0x4C
	float         hookInitialY;       // 0x50
	float         hookInitialZ;       // 0x54
	float         hookCurrentX;       // 0x58
	float         hookCurrentY;       // 0x5C
	float         hookCurrentZ;       // 0x60
	float         unk1;               // 0x64
	float         unk2;               // 0x68
	unsigned int  vehicle;            // 0x6C, pointer to vehicle to be picked up
	unsigned int  timer;              // 0x70
	unsigned char activity;           // 0x74
	unsigned char status;             // 0x75
	unsigned char countCollected;     // 0x76
	unsigned char isCrusher;          // 0x77
	unsigned char isMilitary;         // 0x78
	unsigned char unk3;               // 0x79
	unsigned char isNotCab;           // 0x7A
	unsigned char padding;            // 0x7B
};

//########################################################################
//# CCranes
//########################################################################

class CCranes
{
public:
	static int &carsCollectedMilitaryCrane;
	static int &numCranes;
	static CCrane *cranes;
};

//########################################################################
//# CGeneral
//########################################################################

class CGeneral
{
public:
	static float GetATanOfXY(float, float);
};

//########################################################################
//# CAutomobile
//########################################################################

class CAutomobile : public CEntity
{

};

//########################################################################
//# CVehicle
//########################################################################

class CVehicle : public CAutomobile
{
public:
	unsigned char  space1[0x0034];
	float          x;               // 0x034
	float          y;               // 0x038
	float          z;               // 0x03C
	unsigned char  space2[0x0010];
	unsigned char  availability;    // 0x050
	unsigned char  space3[0x000B];
	unsigned short model;           // 0x05C
	unsigned char  space4[0x01A6];
	float          health;          // 0x204
	unsigned char  space5[0x0094];
	unsigned int   type;            // 0x29C
	float          damageManager;   // 0x2A0
	unsigned char  space6[0x02BC];
	float          burningDuration; // 0x560
};

//########################################################################
//# CDamageManager
//########################################################################

class CDamageManager
{
public:
	void SetEngineStatus(unsigned int);
	void SetWheelStatus(int, unsigned int);
	unsigned int GetEngineStatus();
};

//########################################################################
//# CWeather
//########################################################################

class CWeather
{
public:
	static void ForceWeatherNow(short);
};

//########################################################################
//# CStreaming
//########################################################################

class CStreaming
{
public:
	static void RequestModel(int, int);
	static void LoadAllRequestedModels(bool);
	static void SetModelIsDeletable(int);
};

//########################################################################
//# CFire
//########################################################################

class CFire
{
public:
	unsigned char space1[0x07];
	unsigned char sfx;          // 0x07
	unsigned char space2[0x28];
};

//########################################################################
//# CFireManager
//########################################################################

class CFireManager
{
public:
	static CFire *fires;
};

//########################################################################
//# CGarage
//########################################################################

class CGarage
{
public:
	unsigned char type;              // 0x00
	unsigned char doorState;         // 0x01
	unsigned char space1[0x06];
	unsigned int  modelToCollect;    // 0x08
	unsigned char space2[0x0D];
	unsigned char rotatingDoor;      // 0x19
	unsigned char space3[0x1E];
	float         ceilingHeight;     // 0x38
	unsigned char space4[0x08];
	float         lowerX;            // 0x44
	float         upperX;            // 0x48
	float         lowerY;            // 0x4C
	float         upperY;            // 0x50
	float         doorCurrentHeight; // 0x54
	float         doorMaximumHeight; // 0x58
	unsigned char space5[0x10];
	float         centerHeight;      // 0x6C
	unsigned char space6[0x04];
	unsigned int  gameTimeToOpen;    // 0x74
	unsigned char space7[0x04];
	CVehicle *    targetVehicle;     // 0x7C
	unsigned char space8[0x28];

	bool IsEntityEntirelyInside3D(CEntity *, float);
	bool IsEntityEntirelyOutside(CEntity *, float);
	bool IsAnyOtherCarTouchingGarage(CVehicle *);
};

//########################################################################
//# CGarages
//########################################################################

class CGarages
{
public:
	static int *carsCollected;
	static int &bankVansCollected;
	static int &policeCarsCollected;
	static CGarage *garages;

	static void TriggerMessage(char *, short, unsigned short, short);
};

//########################################################################
//# CExplosion
//########################################################################

class CExplosion
{
public:
	struct Explosion
	{
		unsigned int  type;         // 0x00
		float         x;            // 0x04
		float         y;            // 0x08
		float         z;            // 0x0C
		unsigned char space1[0x14];
		unsigned char activity;     // 0x24
		unsigned char space2[0x10];
	};
	static Explosion *explosions;
};

//########################################################################
//# CPad
//########################################################################

class CPad
{
public:
	static unsigned long GetPad(int);
};

#endif
