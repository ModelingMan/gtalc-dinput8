/*************************************************************************
    vcclasses

    Developed for the Grand Theft Auto: Liberty City project
    http://gtaforums.com/forum/333-
*************************************************************************/

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
	CVector right;      // 0x00
	unsigned int flags; // 0x0C
	CVector up;         // 0x10
	unsigned int pad1;  // 0x1C
	CVector at;         // 0x20
	unsigned int pad2;  // 0x2C
	CVector pos;        // 0x30
	unsigned int pad3;  // 0x3C

	void SetRotate(float, float, float);
	void SetRotateZ(float);
	void SetRotateZOnly(float);
	void ResetOrientation(void);
	void UpdateRW(void);
};

//########################################################################
//# cPedParams
//########################################################################

struct cPedParams
{
	unsigned char unk1;            // 0x0
	unsigned char padding[3];      // 0x1
	float         distanceSquared; // 0x4
	class CPed    *ped;            // 0x8
};

//########################################################################
//# cAudioManager
//########################################################################

class cAudioManager
{
protected:
	unsigned char space1[0x14];     // 0x0000
	int m_AudioEntity;              // 0x0014
	unsigned int m_Unk7;            // 0x0018
	unsigned int m_SampleID;        // 0x001C
	unsigned char m_Unk0;           // 0x0020
	unsigned char m_Unk1;           // 0x0021
	unsigned char space2[0x02];     // 0x0022
	unsigned int m_Unk2;            // 0x0024
	unsigned int m_Frequency;       // 0x0028
	unsigned char m_Volume;         // 0x002C
	unsigned char space3[0x03];     // 0x002D
	float m_DistanceToCamera;       // 0x0030
	unsigned int m_Unk8;            // 0x0034
	int m_LoopStartOff;             // 0x0038
	int m_LoopEndOff;               // 0x003C
	unsigned char m_MaxVolume;      // 0x0040
	unsigned char space6[0x03];     // 0x0041
	float m_Unk4;                   // 0x0044
	float m_MaxRange;               // 0x0048
	unsigned char m_Unk9;           // 0x004C
	unsigned char space8[0x03];     // 0x004D
	CVector m_Position;             // 0x0050
	unsigned char m_Unk10;          // 0x005C
	unsigned char space5;           // 0x005D
	unsigned char m_Unk12;          // 0x005E
	unsigned char space7[0x05];     // 0x005F
	unsigned int m_Unk6;            // 0x0064
	unsigned char spaceend[0x54F0];

public:
	unsigned int GetPhrase(unsigned int &, unsigned int &, unsigned int, unsigned int);
	void ProcessLoopingScriptObject(unsigned char);
	unsigned int GetPlayerTalkSfx(class CPed *, unsigned short);
	void SetupPedComments(cPedParams &, unsigned short);
	void AddSampleToRequestedQueue();
	unsigned int RandomDisplacement(unsigned int);
	unsigned char ComputeVolume(unsigned char, float, float);
	void PlayOneShot(int, unsigned short, float);
	float GetDistanceSquared(const CVector &); // INLINED!
};

//########################################################################
//# CPlaceable
//########################################################################

class CPlaceable
{
public:
	CMatrix matrix;

	bool IsWithinArea(float, float, float, float, float, float);
	bool IsWithinArea(float, float, float, float);
	void SetHeading(float);
};

//########################################################################
//# CEntity
//########################################################################

class CEntity // public CPlaceable
{
public:
	unsigned long  vtbl;                   // 0x000
	CPlaceable     placeable;              // 0x004, offset due to virtual table
	unsigned char  espace1[0x0008];
	unsigned long  RpClump;                // 0x04C
	unsigned char  status;                 // 0x050
	unsigned char  field_051;              // 0x051
	unsigned char  field_052;              // 0x052
	unsigned char  field_053;              // 0x053
	unsigned char  espace2[0x0008];
	unsigned short modelIndex;             // 0x05C
	unsigned char  espace3[0x0006];
	// 0x064

	float GetDistanceFromCentreOfMassToBaseOfModel(void);
	void UpdateRwFrame(void);
	void RegisterReference(CEntity **);

	CMatrix &GetMatrix() { return placeable.matrix; }
	CVector &GetPos() { return placeable.matrix.pos; }
	float &GetX() { return placeable.matrix.pos.x; }
	float &GetY() { return placeable.matrix.pos.y; }
	float &GetZ() { return placeable.matrix.pos.z; }
};

static_assert(sizeof(CEntity) == 0x064, "Size of CEntity is not 0x064 bytes.");

//########################################################################
//# CCamera
//########################################################################

class CCamera : public CPlaceable
{
public:
	void CamShake(float, float, float, float);
	CMatrix &GetMatrix() { return matrix; }
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

	void PlayRadioAnnouncement(unsigned char);
	void PlayFrontEndSound(int id, int unk);
	void PlayOneShot(int, unsigned short, float);
	void SetEntityStatus(int, unsigned char);
	void DestroyEntity(int);
	int CreateEntity(int, void *);
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
	static void SetHelpMessage(wchar_t *, bool, bool);
};

//########################################################################
//# CMessages
//########################################################################

class CMessages
{
public:
	static void AddMessageJumpQWithNumber(wchar_t *, unsigned int, unsigned short, int, int, int, int, int, int);
	static void AddMessageWithNumber(wchar_t *, unsigned int, unsigned short, int, int, int, int, int, int);
	static void InsertStringInString(wchar_t *, wchar_t *);
	static void InsertNumberInString(wchar_t *, int, int, int, int, int, int, wchar_t *);
	static void AddToPreviousBriefArray(wchar_t *, int, int, int, int, int, int, unsigned short *);
	static void AddBigMessageQ(wchar_t *, unsigned int, unsigned short);
	static void AddBigMessage(wchar_t *, unsigned int, unsigned short);
	static void AddMessageJumpQ(wchar_t *, unsigned int, unsigned short);
	static void AddMessage(wchar_t *, unsigned int, unsigned short);
	static void Display(void);
};

//########################################################################
//# CPager
//########################################################################

class CPager
{
protected:
	struct Pager
	{
		wchar_t*       Text;       // Pointer to pager message
		unsigned short Delay;      // How fast the text scrolls
		unsigned short Scroll;     // Index of start letter of currently scrolling text
		unsigned short TextLength; // Length of the pager message
		unsigned short Unk1;
		unsigned int   Unk2;
		unsigned short Unk3;
		unsigned short Unk4;
		unsigned int   Unk5;
		unsigned int   Unk6;
		unsigned int   Unk7;
		unsigned int   Unk8;
		unsigned int   Unk9;
		unsigned int   Unk10;
	};

	unsigned int MaxLength; // Maximum length of the pager message. (DEF: 8)
	Pager Pagers[8];        // Queue of a maximum of 8 pager messages.
};

//########################################################################
//# CWanted
//########################################################################

class CWanted
{
public:
	unsigned int   counter;                    // 0x000
	unsigned char  space1[0x014];
	unsigned char  numberOfPoliceInPursuit;    // 0x018
	unsigned char  maxNumberOfPoliceInPursuit; // 0x019
	unsigned char  space2[0x002];
	unsigned short roadblockChance;            // 0x01C
	unsigned char  activity;                   // 0x01E
	unsigned char  space3;
	int            level;                      // 0x020
	unsigned char  space4[0x1C4];
	unsigned long  policeInPursuit[10];        // 0x1E8

	static unsigned int &MaximumWantedLevel;

	void SetMaximumWantedLevel(int);
	void SetWantedLevelCheat(int);
	void UpdateWantedLevel(void);
};

//########################################################################
//# CPhysical
//########################################################################

class CPhysical : public CEntity
{
public:
	// 0x064
	int            audioEntity;            // 0x064
	unsigned char  pspace1[0x0008];
	CVector        movement;               // 0x070
	unsigned char  pspace2[0x003C];
	float          mass;                   // 0x0B8
	float          turnResistance;         // 0x0BC
	float          accelerationResistance; // 0x0C0
	unsigned char  pspace3[0x003C];
	float          speed;                  // 0x100
	unsigned char  pspace4[0x0016];
	unsigned char  field_11A;              // 0x11A
	unsigned char  pspace5[0x0002];
	char           originLevel;            // 0x11D
	unsigned char  pspace6[0x0002];
	// 0x120

	bool GetHasCollidedWith(CEntity *);
	void RemoveAndAdd(void);
};

static_assert(sizeof(CPhysical) == 0x120, "Size of CPhysical is not 0x120 bytes.");

//########################################################################
//# CVehicle
//########################################################################

class CVehicle : public CPhysical
{
public:
	// 0x120
	unsigned long  handlingData;           // 0x120
	unsigned char  space1[0x0032];
	unsigned char  targetBehavior;         // 0x156
	unsigned char  space2[0x0009];
	unsigned char  cruiseSpeed;            // 0x160
	unsigned char  space3[0x003B];
	CEntity        *targetEntity;          // 0x19C
	unsigned char  firstColour;            // 0x1A0
	unsigned char  secondColour;           // 0x1A1
	unsigned char  space4[0x000A];
	class CPed     *passengers[8];         // 0x1AC
	unsigned char  space5[0x02D];
	unsigned char  field_1F9;              // 0x1F9
	unsigned char  field_1FA;              // 0x1FA
	unsigned char  field_1FB;              // 0x1FB
	unsigned char  field_1FC;              // 0x1FC
	unsigned char  field_1FD;              // 0x1FD
	unsigned char  bombState;              // 0x1FE
	unsigned char  field_1FF;              // 0x1FF
	unsigned char  field_200;              // 0x200
	unsigned char  powerPillsCarried;      // 0x201
	unsigned char  field_202;              // 0x202
	unsigned char  field_203;              // 0x203
	float          health;                 // 0x204
	unsigned char  space6[0x0008];
	CEntity        *bombOwner;             // 0x210
	unsigned char  space7[0x01C];
	unsigned int   lock;                   // 0x230
	unsigned char  space8[0x0068];
	unsigned int   type;                   // 0x29C
	float          damageManager;          // 0x2A0
	unsigned char  space9[0x025D];
	unsigned char  field_501;              // 0x501
	unsigned char  space10[0x005E];
	float          burningDuration;        // 0x560
	unsigned char  space11[0x0061];
	unsigned char  numberOfWheelsOnGround; // 0x5C5
	unsigned char  space12[0x0016];
	// 0x5DC

	static bool &bCheat3;
	static bool &bAllDodosCheat;
	static bool &bWheelsOnlyCheat;
	bool IsSphereTouchingVehicle(float, float, float, float);
	CPed *SetUpDriver(void);
	int FindTyreNearestPoint(float, float);
	void *operator new(unsigned int);
};

static_assert(sizeof(CVehicle) == 0x5DC, "Size of CVehicle is not 0x5DC bytes.");

//########################################################################
//# CAutomobile
//########################################################################

class CAutomobile : public CVehicle
{
public:
	static unsigned char &m_sAllTaxiLights;

	CAutomobile(int, unsigned char);
};

//########################################################################
//# CPed
//########################################################################

class CPed : public CPhysical
{
public:
	// 0x120
	unsigned char  space1[0x002E];
	unsigned char  field_14E;      // 0x14E
	unsigned char  space2[0x00F5];
	unsigned int   state;          // 0x244
	unsigned char  space3[0x0004];
	unsigned int   moveState;      // 0x24C
	unsigned char  space4[0x0104];
	float          health;         // 0x354
	float          armour;         // 0x358
	unsigned char  space5[0x004C];
	CVehicle       *vehicle;       // 0x3A8
	unsigned char  isInAnyVehicle; // 0x3AC
	unsigned char  space6[0x0027];
	unsigned int   pedType;        // 0x3D4
	unsigned char  space7[0x0030];
	struct Weapon
	{
		unsigned int type;  // 0x00
		unsigned int state; // 0x04
		unsigned int clip;  // 0x08
		unsigned int ammo;  // 0x0C
		unsigned int unk1;  // 0x10
		unsigned int unk2;  // 0x14
	} weapons[10];                 // 0x408
	unsigned char  space8[0x002C];
	void           *activeFire;    // 0x524
	unsigned char  space9[0x00B2];
	unsigned short talkType;       // 0x5DA
	unsigned char  space10[0x0004];
	unsigned int   phrase;         // 0x5E0
	unsigned char  space11[0x0010];
	CWanted        *wanted;        // 0x5F4
	unsigned char  space12[0x0040];
	unsigned char  drunkenness;    // 0x638
	unsigned char  space13[0x009F];
	// 0x6D8

	void SetAmmo(int, unsigned int);
	void GrantAmmo(int, unsigned int);
	void GiveWeapon(int, unsigned int, bool);
	bool IsPedInControl(void);
	void Say(unsigned short);
};

static_assert(sizeof(CPed) == 0x6D8, "Size of CPed is not 0x6D8 bytes.");

//########################################################################
//# CPlayerPed
//########################################################################

class CPlayerPed : public CPed
{
public:
};

//########################################################################
//# CObject
//########################################################################

class CObject : public CPhysical
{
public:
	// 0x120
	unsigned char space1[0x004C];
	unsigned char field_16C;      // 0x16C
	unsigned char field_16D;      // 0x16D
	unsigned char space2[0x0032];
	// 0x1A0

	void ObjectDamage(float);
	void *operator new(unsigned int);
	CObject(int, bool);
	CObject(void);
};

static_assert(sizeof(CObject) == 0x1A0, "Size of CObject is not 0x1A0 bytes.");

//########################################################################
//# CCutsceneHead
//########################################################################

class CCutsceneHead : public CObject
{

};

//########################################################################
//# CBuilding
//########################################################################

class CBuilding : public CEntity
{
	// 0x64
};

//########################################################################
//# CPool
//########################################################################

template <class T1, class T2 = T1>
class CPool
{
public:
	T2            *entities;   // 0x00
	unsigned char *flags;      // 0x04
	int           totalCount;  // 0x08

	int GetIndex(T1 *);
	T1 *GetAt(int);
};

//########################################################################
//# CPools
//########################################################################

class CPools
{
public:
	static CPool<CObject, CCutsceneHead> *&ms_pObjectPool;
	static CPool<CBuilding> *&ms_pBuildingPool;
	static CPool<CPed, CPlayerPed> *&ms_pPedPool;
	static CPool<CVehicle, CAutomobile> *&ms_pVehiclePool;
};

//########################################################################
//# CPlayerInfo
//########################################################################

class CPlayerInfo
{
public:
	CPlayerPed    *playerEntity;         // 0x000
	unsigned char space1[0x009C];
	unsigned int  m_Money;               // 0x0A0
	unsigned int  m_MoneyCounter;        // 0x0A4
	unsigned int  m_HiddenPackagesFound; // 0x0A8
	unsigned int  m_TotalHiddenPackages; // 0x0AC
	unsigned char space2[0x0004];
	unsigned int  timeTaxiTimer;         // 0x0B4
	bool          isTaxiTimerOn;         // 0x0B8
	unsigned char space3[0x0013];
	unsigned char deathArrestState;      // 0x0CC
	unsigned char space4[0x0003];
	unsigned int  timeDeathArrest;       // 0x0D0
	unsigned char space5[0x0002];
	unsigned char fadeJumpCutRcExplode;  // 0x0D6
	unsigned char space6[0x006C];
	unsigned char maxHealth;             // 0x143
	unsigned char maxArmour;             // 0x144
	unsigned char getOutOfJailFree;      // 0x145
	unsigned char freeHealthCare;        // 0x146
	unsigned char space7[0x0029];
	// 0x170
};

static_assert(sizeof(CPlayerInfo) == 0x170, "Size of CPlayerInfo is not 0x170 bytes.");

//########################################################################
//# CRunningScript
//########################################################################

class CRunningScript
{
public:
	// Thanks to CyQ, PatrickW and spookie for this info.
	void *m_pNext;                   // 0x00
	void *m_pPrev;                   // 0x04
	char m_strName[8];               // 0x08
	unsigned int m_dwScriptIP;       // 0x10
	unsigned int m_dwReturnStack[6]; // 0x14
	unsigned short m_dwStackPointer; // 0x2C
	unsigned char pad1[2];           // 0x2E
	unsigned int m_dwLocalVar[18];   // 0x30
	bool m_bStartNewScript;          // 0x78
	bool m_bJumpFlag;                // 0x79
	bool m_bWorky;                   // 0x7A
	bool m_bAwake;                   // 0x7B
	unsigned int m_dwWakeTime;       // 0x7C
	unsigned short m_wIfParam;       // 0x80
	bool m_bNotFlag;                 // 0x82
	bool m_bWastedBustedCheck;       // 0x83
	bool m_bWastedBustedFlag;        // 0x84
	bool m_bMissionThread;           // 0x85

	template <class T>
	T SCM_Read(bool bIncreaseIP);

	void StoreParameters(unsigned int *, short);
	void CollectParameters(unsigned int *scriptIP, int paramCount);
	bool ProcessOneCommand();
	int CollectNextParameterWithoutIncreasingPC(unsigned int);
	void UpdateCompareFlag(bool flag);
	short GetPadState(unsigned short, unsigned short);
};

//########################################################################
//# cSampleManager
//########################################################################

class cSampleManager
{
public:
	unsigned int GetSampleBaseFrequency(unsigned int);
	int GetSampleLoopEndOffset(unsigned int);
	int GetSampleLoopStartOffset(unsigned int);
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
//# IntroTextLine
//########################################################################

struct IntroTextLine
{
	float         scaleX;             // 0x00
	float         scaleY;             // 0x04
	unsigned char colorR;             // 0x08
	unsigned char colorG;             // 0x09
	unsigned char colorB;             // 0x0A
	unsigned char colorA;             // 0x0B
	unsigned char justify;            // 0x0C
	unsigned char centre;             // 0x0D
	unsigned char background;         // 0x0E
	unsigned char backgroundOnlyText; // 0x0F
	float         wrapX;              // 0x10
	float         centreWidth;        // 0x14
	unsigned char backgroundColorR;   // 0x18
	unsigned char backgroundColorG;   // 0x19
	unsigned char backgroundColorB;   // 0x1A
	unsigned char backgroundColorA;   // 0x1B
	unsigned char proportional;       // 0x1C
	unsigned char drawBeforeFade;     // 0x1D
	unsigned char alignRight;         // 0x1E
	unsigned char padding;
	short         font;               // 0x20
	unsigned char padding2[2];
	float         positionX;          // 0x24
	float         positionY;          // 0x28
	wchar_t       text[100];          // 0x2C
};

//########################################################################
//# CTheScripts
//########################################################################

class CTheScripts
{
public:
	static IntroTextLine *IntroTextLines;
	static unsigned char *ScriptSpace;
	static class CMissionCleanup &MissionCleanUp;
	static unsigned short &NumberOfIntroTextLinesThisFrame;
	static unsigned short &CommandsExecuted;

	static void HighlightImportantArea(unsigned int, float, float, float, float, float);
	static void ClearSpaceForMissionEntity(CVector const &, CEntity *);
};

//########################################################################
//# CTimer
//########################################################################

class CTimer
{
public:
	static unsigned int &m_snTimeInMilliseconds;
	static float &ms_fTimeStepNonClipped;
	static float &ms_fTimeStep;
	static float &ms_fTimeScale;
	static unsigned int &m_FrameCounter;

	static void Resume(void);
	static void Suspend(void);
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
//# CColPoint
//########################################################################

class CColPoint
{
public:
	CVector point;
	unsigned char space1[0x1C];
	// 0x28
};

//########################################################################
//# CWorld
//########################################################################

class CWorld
{
public:
	static unsigned char &PlayerInFocus;
	static CPlayerInfo *Players;

	static void RepositionOneObject(CEntity *);
	static float FindGroundZFor3DCoord(float, float, float, bool *);
	static float FindGroundZForCoord(float x, float y);
	static bool ProcessVerticalLine(CVector const &, float, CColPoint &, CEntity *&, bool, bool, bool, bool, bool, bool, unsigned long);
	static void Remove(CEntity *);
	static void Add(CEntity *);
};

//########################################################################
//# CScrollBar
//########################################################################

class CScrollBar
{
public:
	unsigned long count;            // 0x00
	char *text;                     // 0x04
	float xStart;                   // 0x08
	float yStart;                   // 0x0C
	float zStart;                   // 0x10
	unsigned long charCount;        // 0x14
	unsigned long textLength;       // 0x18
	float xEndOffset;               // 0x1C
	float yEndOffset;               // 0x20
	float zEndOffset;               // 0x24
	float thickness;                // 0x28
	unsigned char letterBuffer[40]; // 0x2C
	unsigned char messageSet;       // 0x54
	bool draw;                      // 0x55
	unsigned char r;                // 0x56
	unsigned char g;                // 0x57
	unsigned char b;                // 0x58
	unsigned char padding[7];       // 0x59

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
	static void RenderOneXLUSprite(float, float, float, float, float, unsigned char, unsigned char, unsigned char, short, float, unsigned char);
	static void RenderBufferedOneXLUSprite(float, float, float, float, float, unsigned char, unsigned char, unsigned char, short, float, unsigned char);
	static void InitSpriteBuffer();
	static void FlushSpriteBuffer();
	static bool CalcScreenCoors(const RwV3d &, RwV3d *, float *, float *, bool);
};

//########################################################################
//# CCrane
//########################################################################

class CCrane
{
public:
	CEntity       *object;            // 0x00
	CObject       *hook;              // 0x04, pointer to hook object
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
	CVehicle      *vehicle;           // 0x6C
	unsigned int  timer;              // 0x70
	unsigned char activity;           // 0x74
	unsigned char status;             // 0x75
	unsigned char countCollected;     // 0x76
	bool          isCrusher;          // 0x77
	bool          isMilitary;         // 0x78
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
	static int &CarsCollectedMilitaryCrane;
	static int &NumCranes;
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
	static float &Foggyness;
	static float &Rain;
	static float &InterpolationValue;
	static float &WetRoads;
	static short &NewWeatherType;
	static short &ForcedWeatherType;
	static short &OldWeatherType;
	static bool &bScriptsForceRain;

	static void ForceWeatherNow(short);
};

//########################################################################
//# CStreaming
//########################################################################

class CStreaming
{
public:
	static void SetModelTxdIsDeletable(int);
	static void SetModelIsDeletable(int);
	static void LoadAllRequestedModels(bool);
	static void RequestModel(int, int);
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
	unsigned char type;               // 0x00
	unsigned char state;              // 0x01
	unsigned char maxCarsInSave;      // 0x02
	unsigned char unk1;               // 0x03
	unsigned char closedUnserviced;   // 0x04
	unsigned char isInactive;         // 0x05
	unsigned char hasResprayHappened; // 0x06
	unsigned char padding1;           // 0x07
	unsigned int  targetModel;        // 0x08
	unsigned long doorObject;         // 0x0C
	unsigned long crusherTopObject;   // 0x10
	unsigned char unk2;               // 0x14
	unsigned char unk3;               // 0x15
	unsigned char doorInDummys;       // 0x16
	unsigned char crusherTopInDummys; // 0x17
	unsigned char unk4;               // 0x18
	unsigned char rotatingDoor;       // 0x19
	unsigned char leaveCameraAlone;   // 0x1A
	unsigned char padding2;           // 0x1B
	float         positionX;          // 0x1C
	float         positionY;          // 0x20
	float         positionZ;          // 0x24
	float         rotationX;          // 0x28
	float         rotationY;          // 0x2C
	float         rotationZ;          // 0x30
	float         rotationW;          // 0x34
	float         ceilingHeight;      // 0x38
	float         unk5;               // 0x3C
	float         unk6;               // 0x40
	float         lowerX;             // 0x44
	float         upperX;             // 0x48
	float         lowerY;             // 0x4C
	float         upperY;             // 0x50
	float         doorCurrentHeight;  // 0x54
	float         doorMaximumHeight;  // 0x58
	float         doorX;              // 0x5C
	float         doorY;              // 0x60
	float         crusherTopX;        // 0x64
	float         crusherTopY;        // 0x68
	float         doorZ;              // 0x6C
	float         crusherTopZ;        // 0x70
	unsigned int  gameTimeToOpen;     // 0x74
	unsigned char unk7;               // 0x78
	unsigned char padding3[3];        // 0x79
	CVehicle      *targetVehicle;     // 0x7C
	unsigned char unk8[0x28];

	bool IsAnyCarBlockingDoor(void);
	void UpdateDoorsHeight(void);
	bool IsAnyOtherCarTouchingGarage(CVehicle *);
	bool IsEntityEntirelyOutside(CEntity *, float);
	bool IsEntityEntirelyInside3D(CEntity *, float);
	bool IsStaticPlayerCarEntirelyInside(void);
};

//########################################################################
//# CGarages
//########################################################################

class CGarages
{
public:
	static int *CarTypesCollected;
	static int &BankVansCollected;
	static int &PoliceCarsCollected;
	static unsigned char &RespraysAreFree;
	static unsigned char &BombsAreFree;
	static CGarage *garages;

	static void TriggerMessage(char *, short, unsigned short, short);
	static void ChangeGarageType(short, unsigned char, unsigned int);
};

//########################################################################
//# CExplosion
//########################################################################

class CExplosion
{
public:
	struct Explosion
	{
		int           type;                   // 0x00
		CVector       position;               // 0x04
		float         radius;                 // 0x10
		float         expansionRate;          // 0x14
		CEntity       *owner;                 // 0x18
		CEntity       *victim;                // 0x1C
		unsigned int  timeExpire;             // 0x20
		unsigned char counter;                // 0x24
		unsigned char isCounterInitialised;   // 0x25
		unsigned char noVehicleJetExplosion;  // 0x26
		unsigned char hasSound;               // 0x27
		unsigned int  timeVehicleExplosion;   // 0x28
		unsigned int  timeExtendEffect;       // 0x2C
		float         force;                  // 0x30
		float         molotovGroundZ;         // 0x34
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

//########################################################################
//# CDarkel
//########################################################################

class CDarkel
{
public:
	static void StartFrenzy(int, int, unsigned short, int, wchar_t *, int, int, int, bool, bool);
	static void ResetOnPlayerDeath(void);
};

//########################################################################
//# CRadar
//########################################################################

class CRadar
{
public:
	static void SetBlipSprite(int, int);
	static void ChangeBlipScale(int, int);
	static int SetEntityBlip(int, int, unsigned int, int);
	static int SetShortRangeCoordBlip(int, CVector, unsigned int, int);
	static int GetActualBlipArrayIndex(int);
};

//########################################################################
//# CPickup
//########################################################################

class CPickup
{
public:
	unsigned char space1[0x10];
	CObject       *object;      // 0x10
	unsigned char space2[0x20];
};

//########################################################################
//# CPickups
//########################################################################

class CPickups
{
public:
	static int GetActualPickupIndex(int);
	static int GenerateNewOne(CVector, unsigned int, unsigned int, unsigned int, unsigned char, unsigned char, char *);
	static CPickup *pickups;
};

//########################################################################
//# CPhoneInfo
//########################################################################

class CPhoneInfo
{
public:
	unsigned int numberOfPhones;
	unsigned int numberOfActivePhones;
	struct CPhone
	{
		CVector       position;            // 0x00
		wchar_t       *message1;           // 0x0C
		wchar_t       *message2;           // 0x10
		wchar_t       *message3;           // 0x14
		wchar_t       *message4;           // 0x18
		wchar_t       *message5;           // 0x1C
		wchar_t       *message6;           // 0x20
		unsigned int  timeMessageEnded;    // 0x24
		unsigned int  object;              // 0x28
		unsigned int  state;               // 0x2C
		unsigned char isPlayerWithinRange; // 0x30
		unsigned char padding[3];          // 0x31
	} phones[50];

	void SetPhoneMessage_JustOnce(int, wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *);
};

//########################################################################
//# CRestart
//########################################################################

class CRestart
{
public:
	static unsigned char &OverridePoliceStationLevel;
	static unsigned char &OverrideHospitalLevel;

	static void OverrideNextRestart(CVector const &, float);
};

//########################################################################
//# CWeaponInfo
//########################################################################

class CWeaponInfo
{
public:
	static unsigned long GetWeaponInfo(int);
};

//########################################################################
//# CMissionCleanup
//########################################################################

class CMissionCleanup
{
public:
	void RemoveEntityFromList(int, unsigned char);
};

//########################################################################
//# CProjectileInfo
//########################################################################

class CProjectileInfo
{
public:
	struct ProjectileInfo
	{
		unsigned int  weaponType;          // 0x00
		unsigned long thrower;             // 0x04
		unsigned int  timeToExpire;        // 0x08
		unsigned char doesProjectileExist; // 0x0C
		unsigned char padding[3];          // 0x0D
		CVector       position;            // 0x10
	};

	static ProjectileInfo *projectiles;
};

//########################################################################
//# CZone
//########################################################################

class CZone
{
public:
	char name[8];
	CVector corner1;
	CVector corner2;
	unsigned int type;
	unsigned int level;
	unsigned short night;
	unsigned short day;
	unsigned int childZone;
	unsigned int parentZone;
	unsigned int unk;
};

//########################################################################
//# CZoneInfo
//########################################################################

struct CZoneInfo
{
	unsigned short carDensity;   // 0x00
	unsigned char  space1[0x2A];
	unsigned short pedDensity;   // 0x2C
	unsigned char  space2[0x16];
};

//########################################################################
//# CTheZones
//########################################################################

class CTheZones
{
public:
	static CZoneInfo *ZoneInfoArray;
	static CZone *InfoZoneArray;
	static CZone *NavigationZoneArray;
	static unsigned short &TotalNumberOfInfoZones;
	static unsigned short &TotalNumberOfNavigationZones;

	static void InitialiseAudioZoneArray(void);
	static int GetLevelFromPosition(CVector const *);
};

//########################################################################
//# CStats
//########################################################################

class CStats
{
public:
	static float &ShootingRangeRank;
	static int &TotalNumberMissions;
	static float &GarbagePickups;
	static float &LoanSharks;
	static int &IndustrialPassed;
	static int &HighestLevelFireMission;
	static int &SuburbanPassed;
	static float &StoresKnockedOff;
	static int &CommercialPassed;
	static float &TopShootingRangeScore;
	static float &MovieStunts;
	static int &MissionsGiven;
	static float &AutoPaintingBudget;
	static float &Assassinations;

	static void AnotherKillFrenzyPassed(void);
};

//########################################################################
//# CCarCtrl
//########################################################################

class CCarCtrl
{
public:
	static unsigned int &LastTimeFireTruckCreated;
	static unsigned int &LastTimeAmbulanceCreated;

	static void ReInit(void);
};

//########################################################################
//# CPathInfoForObject
//########################################################################

class CPathInfoForObject
{
public:
	struct PathNode
	{
		CVector       Pos;
		char          NodeType;
		char          NextNode;
		char          LeftLanes;
		char          RightLanes;
		char          SpeedLimit;
		char          Median;
		bool          IsCrossroad : 1;
		bool          Unknown2 : 1;
		bool          IsRoadblock : 1;
		bool          IgnoredByTraffic : 1;
		bool          BoatNode : 1;
		bool          RestrictedNode : 1;
		unsigned char SpawnRate : 4;
	} m_node[12];

	void SwapConnectionsToBeRightWayRound(void);
};

//########################################################################
//# CPathFind
//########################################################################

class CPathFind
{
public:
	static CPathInfoForObject *&InfoForTileCars;
	static CPathInfoForObject *&InfoForTilePeds;

	void FindNodeCoorsForScript(CVector &, int);
	void StoreDetachedNodeInfoPed(int, char, int, float, float, float, float, bool, bool, bool, unsigned char);
	int FindNthNodeClosestToCoors(CVector, unsigned char, float, bool, bool, int, bool);
};

//########################################################################
//# CRenderer
//########################################################################

class CRenderer
{
public:
	static void ConstructRenderList(void);
};

//########################################################################
//# CFileMgr
//########################################################################

class CFileMgr
{
public:
	static int CloseFile(int);
	static bool ReadLine(int, char *, int);
	static int OpenFile(char const *, char const *);
};

//########################################################################
//# CGame
//########################################################################

class CGame
{
public:
	static unsigned char &nastyGame;
	static unsigned int &currArea;
	static int &currLevel;
};

//########################################################################
//# CParticleObject
//########################################################################

class CParticleObject
{
public:
	static void AddObject(unsigned short, CVector const &, unsigned char);
};

//########################################################################
//# CPointLights
//########################################################################

class CPointLights
{
public:
	static void AddLight(unsigned char, CVector, CVector, float, float, float, float, unsigned char, bool);
};

//########################################################################
//# CParticle
//########################################################################

class CParticle
{
public:
	static void AddParticle(int, CVector const &, CVector const &, CEntity *, float, RwRGBA const &, int, int, int, int);
};

//########################################################################
//# CShadows
//########################################################################

class CShadows
{
public:
	static void StoreShadowToBeRendered(unsigned char, RwTexture *, CVector *, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, bool, float, unsigned long, bool);
};

//########################################################################
//# CGangs
//########################################################################

class CGangs
{
public:
	int vehicleModel;         // 0x00
	int pedModel1;            // 0x04
	int pedModel2;            // 0x08
	char pedModelPreference;  // 0x0C
	unsigned char padding[3]; // 0x0D
	int weapon1;              // 0x10
	int weapon2;              // 0x14

	static CGangs *Gang;
};

//########################################################################
//# CPopulation
//########################################################################

class CPopulation
{
public:
	static bool &ms_bGivePedsWeapons;
};

//########################################################################
//# CVehicleModelInfo
//########################################################################

class CVehicleModelInfo
{
public:
	static unsigned int GetMaximumNumberOfPassengersFromNumberOfDoors(int);
};

//########################################################################
//# CMenuManager
//########################################################################

class CMenuManager
{
public:
	static unsigned int &m_PrefsLanguage;
};

//########################################################################
//# CModelInfo
//########################################################################

class CModelInfo
{
public:
	static unsigned long *ms_modelInfoPtrs;

	static bool IsBikeModel(int);
	static bool IsBoatModel(int);
};

//########################################################################
//# CBoat
//########################################################################

class CBoat : public CVehicle
{
public:
	CBoat(int, unsigned char);
};

//########################################################################
//# CBike
//########################################################################

class CBike : public CVehicle
{
public:
	CBike(int, unsigned char);
};

//########################################################################
//# CBulletInfo
//########################################################################

class CBulletInfo
{
public:
	static bool TestForSniperBullet(float, float, float, float, float, float);
};

//########################################################################
//# CScriptPaths
//########################################################################

class CScriptPaths
{
public:
	char space1[0x10];
	float distanceAlongPath;
	char space2[0x20];

	static CScriptPaths *ScriptPath;
};

//########################################################################
//# CGameLogic
//########################################################################

class CGameLogic
{
public:
	static void AddShortCutDropOffPointForMission(CVector, float);
};

//########################################################################
//# CTrafficLights
//########################################################################

class CTrafficLights
{
public:
	static bool &bGreenLightsCheat;

	static unsigned char LightForPeds(void);
};

//########################################################################
//# CShinyTexts
//########################################################################

class CShinyTexts
{
public:
	CVector vec1;
	CVector vec2;
	CVector vec3;
	CVector vec4;
	float unk[8];
	float distance;
	unsigned char type;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	static CShinyTexts *aShinyTexts;
	static unsigned int &NumShinyTexts;
};

static_assert(sizeof(CShinyTexts) == 0x58, "Size of CShinyTexts is not 0x58 bytes.");

#endif
