#include "cAudioManagerHack.h"
#include "Globals.h"
#include "vcversion.h"
#include <math.h>
#include <fstream>

unsigned long JumpTableForFrontEnd = vcversion::AdjustOffset(0x006B28B8);
unsigned long OffsetIfWeHackedFrontEnd = vcversion::AdjustOffset(0x005DBE5E);

bool cAudioManagerHack::initialise()
{
	unsigned long ProcessFrontEndHackAddr = vcversion::AdjustOffset(0x005DBCA7);
	unsigned long *ProcessLoopingScriptObjectHackAddr = reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x005F58F4));

	//Memory is protected from write (write protection of .text section removed at startup)
	*reinterpret_cast<unsigned char *>(ProcessFrontEndHackAddr) = 0xB9;						// mov ecx,
	*reinterpret_cast<void (**)()>(ProcessFrontEndHackAddr + 1) = ProcessFrontEndHackProxy; //          ProcessFrontEndHackProxy
	*reinterpret_cast<unsigned short *>(ProcessFrontEndHackAddr + 5) = 0xE1FF;				// jmp ecx

	union { void (cAudioManagerHack::*func)(unsigned char); unsigned long offset; } nasty = { &cAudioManagerHack::ProcessLoopingScriptObjectHack };
	*reinterpret_cast<unsigned long *>(ProcessLoopingScriptObjectHackAddr) = nasty.offset - reinterpret_cast<unsigned long>(ProcessLoopingScriptObjectHackAddr + 1);

	std::ifstream fileName("vehicleSfx.dat");
	if (fileName.is_open()) {
		int value = 0, i = 0, j = 0;
		while (fileName >> value) {
			*(unsigned int *)(vcversion::AdjustOffset(0x6AD1A0) + i * 28 + j * 4) = value;
			if (++j > 6) {
				i++;
				j = 0;
			}
		}
		fileName.close();
	} else {
		int vehicleSfx[107][7] =
		{ { 277, 13, 0, 26513, 52, 9935, 1 },
		{ 278, 14, 4, 11487, 52, 9900, 0 },
		{ 274, 10, 6, 10400, 52, 9890, 1 },
		{ 272, 8, 7, 29711, 52, 9960, 2 },
		{ 278, 14, 4, 12893, 52, 9500, 0 },
		{ 271, 7, 1, 10706, 52, 9600, 1 },
		{ 268, 0, 7, 29711, 52, 9700, 1 },
		{ 272, 8, 7, 29711, 27, 11556, 2 },
		{ 272, 8, 7, 31478, 52, 9800, 2 },
		{ 278, 14, 1, 9538, 52, 9900, 1 },
		{ 278, 14, 4, 10842, 52, 10000, 0 },
		{ 269, 5, 1, 12017, 52, 9900, 1 },
		{ 277, 13, 0, 22293, 52, 9800, 1 },
		{ 270, 6, 3, 18000, 52, 9700, 1 },
		{ 270, 6, 2, 18286, 52, 9600, 2 },
		{ 274, 10, 6, 10000, 52, 9500, 0 },
		{ 270, 6, 0, 22295, 29, 8795, 2 },
		{ 268, 4, 3, 17900, 27, 10511, 2 },
		{ 278, 14, 4, 12170, 52, 9400, 1 },
		{ 278, 14, 3, 12345, 52, 9300, 0 },
		{ 277, 13, 1, 10796, 52, 9200, 1 },
		{ 271, 7, 1, 9003, 52, 9100, 1 },
		{ 277, 13, 5, 10924, 52, 9000, 1 },
		{ 278, 14, 5, 11025, 31, 11025, 0 },
		{ 273, 9, 0, 26513, 52, 9100, 1 },
		{ 453, 30, 0, 26513, 52, 9200, 1 },
		{ 271, 7, 1, 10706, 27, 13596, 1 },
		{ 270, 6, 2, 17260, 27, 13000, 2 },
		{ 270, 6, 5, 8670, 52, 9300, 0 },
		{ 274, 10, 6, 10400, 52, 9400, 1 },
		{ 268, 0, 0, 26513, 27, 11912, 1 },
		{ 272, 8, 3, 11652, 52, 9500, 3 },
		{ 272, 8, 7, 29711, 52, 9600, 2 },
		{ 272, 8, 7, 28043, 52, 9700, 2 },
		{ 273, 9, 0, 25400, 52, 9800, 0 },
		{ 268, 0, 0, 26513, 52, 9900, 1 },
		{ 284, 20, 0, 26313, 52, 10000, 1 },
		{ 272, 8, 2, 16291, 52, 10100, 3 },
		{ 278, 14, 4, 10842, 52, 9900, 0 },
		{ 278, 14, 4, 10233, 52, 9800, 0 },
		{ 270, 6, 5, 8670, 52, 9700, 0 },
		{ 423, 17, 5, 20000, 52, 9600, 1 },
		{ 278, 14, 0, 26513, 52, 9500, 0 },
		{ 272, 8, 7, 29000, 52, 9400, 2 },
		{ 270, 6, 0, 21043, 52, 9300, 0 },
		{ 271, 7, 6, 9271, 52, 9200, 1 },
		{ 268, 0, 3, 15554, 52, 9100, 1 },
		{ 268, 0, 3, 13857, 52, 9000, 2 },
		{ 285, 21, 0, 30000, 52, 9100, 1 },
		{ 270, 6, 0, 21043, 52, 9200, 2 },
		{ 268, 0, 0, 21043, 52, 9300, 1 },
		{ 268, 0, 0, 21043, 52, 9400, 1 },
		{ 268, 0, 0, 21043, 52, 9500, 1 },
		{ 268, 0, 0, 21043, 52, 9600, 1 },
		{ 268, 0, 0, 21043, 52, 9700, 1 },
		{ 272, 8, 7, 28043, 52, 9800, 2 },
		{ 270, 6, 2, 18286, 52, 9900, 2 },
		{ 279, 15, 0, 28500, 52, 9800, 1 },
		{ 278, 14, 4, 10842, 52, 9700, 0 },
		{ 270, 6, 3, 18000, 52, 9700, 1 },
		{ 461, 35, 0, 26513, 52, 9700, 1 },
		{ 287, 23, 0, 27000, 52, 9600, 1 },
		{ 285, 21, 0, 31000, 52, 9500, 1 },
		{ 284, 20, 5, 11000, 52, 9400, 1 },
		{ 423, 17, 0, 30000, 52, 15000, 0 },
		{ 425, 18, 0, 30000, 52, 15000, 1 },
		{ 276, 12, 4, 10300, 52, 9100, 0 },
		{ 276, 12, 4, 10500, 52, 9000, 0 },
		{ 286, 22, 0, 30000, 52, 9000, 1 },
		{ 268, 0, 0, 26513, 52, 9100, 2 },
		{ 270, 6, 7, 29711, 52, 9200, 2 },
		{ 274, 10, 5, 11200, 52, 9300, 1 },
		{ 268, 0, 0, 26513, 52, 9400, 1 },
		{ 268, 0, 0, 26513, 52, 9500, 1 },
		{ 276, 12, 4, 10700, 52, 9600, 0 },
		{ 273, 9, 1, 9200, 52, 9700, 0 },
		{ 273, 9, 3, 13857, 52, 9800, 0 },
		{ 274, 10, 0, 26513, 52, 9900, 1 },
		{ 278, 14, 4, 10540, 52, 9935, 2 },
		{ 275, 11, 5, 11000, 52, 9700, 1 },
		{ 274, 10, 6, 11025, 52, 9800, 1 },
		{ 274, 10, 1, 9700, 52, 9700, 1 },
		{ 275, 11, 3, 18000, 52, 9600, 0 },
		{ 273, 9, 6, 10500, 52, 9500, 0 },
		{ 268, 0, 0, 26513, 52, 9400, 1 },
		{ 275, 11, 0, 27513, 52, 9300, 1 },
		{ 268, 4, 4, 10842, 52, 9200, 0 },
		{ 268, 0, 0, 26513, 52, 9100, 2 },
		{ 268, 0, 0, 26513, 52, 9000, 2 },
		{ 277, 13, 3, 18000, 52, 9100, 2 },
		{ 271, 7, 6, 9271, 27, 16168, 1 },
		{ 271, 7, 0, 26513, 52, 9200, 1 },
		{ 275, 11, 1, 9600, 52, 9300, 1 },
		{ 271, 0, 0, 26513, 52, 9400, 1 },
		{ 274, 10, 6, 11025, 52, 9500, 1 },
		{ 273, 9, 5, 10924, 52, 9600, 0 },
		{ 277, 13, 0, 22295, 52, 9700, 1 },
		{ 268, 0, 0, 26513, 52, 9800, 1 },
		{ 270, 6, 0, 21043, 52, 9900, 0 },
		{ 270, 6, 0, 21043, 52, 9800, 0 },
		{ 268, 4, 0, 26513, 52, 9700, 1 },
		{ 425, 18, 0, 26513, 52, 9600, 1 },
		{ 273, 9, 79, 26513, 52, 9700, 1 },
		{ 274, 10, 3, 15554, 52, 9600, 1 },
		{ 268, 4, 0, 26513, 52, 9500, 1 },
		{ 271, 7, 6, 12375, 52, 9400, 1 },
		{ 269, 5, 6, 11025, 27, 11000, 1 } };
		for (int i = 0; i < 107; i++) {
			for (int j = 0; j < 7; j++) {
				*(unsigned int *)(vcversion::AdjustOffset(0x6AD1A0) + i * 28 + j * 4) = vehicleSfx[i][j];
			}
		}
	}

	return true;
}

void __declspec(naked) cAudioManagerHack::ProcessFrontEndHackProxy()
{
	__asm
	{
		push	eax
		add		eax, 3Bh
		push	eax
		mov		ecx, ebp
		call	ProcessFrontEndHack
		pop		ecx
		cmp		al, 1
		je		wehackedthisone
		mov		eax, JumpTableForFrontEnd
		lea		eax, [eax+ecx*4]
		jmp		dword ptr [eax]
	wehackedthisone:
		jmp		OffsetIfWeHackedFrontEnd
	}
}

bool cAudioManagerHack::ProcessFrontEndHack(unsigned char id)
{
	switch (id)
	{
	/*case 59:
		this->m_SampleID = 330; // sniper rifle
		break;
	case 60:
		this->m_SampleID = 329; // rocket launcher
		break;*/
	case 61:
		this->m_SampleID = 490;
		break;
	case 62:
		this->m_SampleID = 491;
		break;
	case 63:
		this->m_SampleID = 492;
		break;
	case 64:
		this->m_SampleID = 493;
		break;
	case 65:
		this->m_SampleID = 494;
		break;
	case 66:
		this->m_SampleID = 495;
		break;
	case 96: //Pager sound
		this->m_SampleID = 458;
		break;
	default:
		return false;
	}

	return true;
}

void cAudioManagerHack::ProcessLoopingScriptObjectHack(unsigned char id)
{
	float maxDistance, distance;
	unsigned char unk1;

	switch (id)
	{
	case 47:
		this->m_SampleID = 483;
		break;
	case 48:
		this->m_SampleID = 484;
		break;
	case 49:
		this->m_SampleID = 485;
		break;
	case 50:
		this->m_SampleID = 486;
		break;
	case 51:
		this->m_SampleID = 487;
		break;
	default:
		this->ProcessLoopingScriptObject(id);
		return;
	}

	this->m_Unk0 = 0;
	maxDistance = 36.0f;
	this->m_Unk5 = 80.0f;
	unk1 = 127;
	this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
	this->m_Unk2 = 3;
	this->m_Unk6 = 15;
	this->m_Unk4 = 4.0f;
	this->m_Unk1 = 0;

	distance = this->GetDistanceSquared(this->m_Position);

	if (distance < maxDistance)
	{
		this->m_Unk3 = (distance > 0 ? sqrt(distance) : 0.0f);
		this->m_Volume = this->ComputeVolume(unk1, this->m_Unk5, this->m_Unk3);
		if (this->m_Volume > 0)
		{
			this->m_Unk7 = 0;
			this->m_Unk8 = 0;
			this->m_Unk9 = 0;
			this->m_Unk10 = 1;
			this->m_Unk11 = unk1;
			this->m_LoopStartOff = VCGlobals::SampleManager.GetSampleLoopStartOffset(this->m_SampleID);
			this->m_LoopEndOff = VCGlobals::SampleManager.GetSampleLoopEndOffset(this->m_SampleID);
			this->m_Unk12 = 0;
			this->AddSampleToRequestedQueue();
		}
	}
}
