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
	void PlayFrontEndSound(int id, int unk);
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
	static void SetHelpMessage(unsigned short*, bool, bool);
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

class CPlayerPed
{

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
public:;
	static void InitSpriteBuffer();
	static bool CalcScreenCoors(const RwV3d &, RwV3d *, float *, float *, bool);
	static void RenderBufferedOneXLUSprite(float, float, float, float, float, unsigned char, unsigned char, unsigned char, short, float, unsigned char);
	static void FlushSpriteBuffer();
};

#endif
