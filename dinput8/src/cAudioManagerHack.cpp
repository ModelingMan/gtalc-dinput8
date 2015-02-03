#include "cAudioManagerHack.h"
#include "Globals.h"
#include "vcversion.h"
#include <math.h>

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
	case 59:
		this->m_SampleID = 488;
		break;
	case 60:
		this->m_SampleID = 489;
		break;
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
