#include "CRunningScriptHack.h"
#include "CPagerHack.h"
#include "CScrollBarHack.h"
#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"

#include <string.h>
#include <Windows.h>

using namespace VCGlobals;

unsigned long *ProcessOneCommandHackAddr = reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x0044FDB6));

bool CRunningScriptHack::initialise()
{
	//Memory is protected from write (write protection of .text section removed at startup)
	union { bool (CRunningScriptHack::*func)(); unsigned long offset; } nasty = { &ProcessOneCommandHack };
	*ProcessOneCommandHackAddr = nasty.offset - reinterpret_cast<unsigned long>(ProcessOneCommandHackAddr + 1);
	return true;
}

bool CRunningScriptHack::ProcessOneCommandHack()
{
	CTheScripts::CommandsExecuted++;
	short opCode = MAKEWORD(CTheScripts::ScriptSpace[this->m_dwScriptIP], CTheScripts::ScriptSpace[this->m_dwScriptIP + 1]);
	m_dwScriptIP += 2;
	this->m_bNotFlag = opCode < 0;
	short opCodeNum = opCode & 0x7FFF;

	switch (opCodeNum)
	{
	case 0x014D:
		return this->_014D_text_pager();

	case 0x034A:	// set_portland_complete
		CScrollBarHack::ms_PortlandComplete = true;
		break;

	case 0x034B:	// set_staunton_complete
		CScrollBarHack::ms_StauntonComplete = true;
		break;

	case 0x034C:	// set_shoreside_complete
		CScrollBarHack::ms_ShoresideComplete = true;
		break;
	}

	CTheScripts::CommandsExecuted--;
	m_dwScriptIP -= 2;
	// Call VC's CRunningScript::ProcessOneCommand
	return ProcessOneCommand();
}

bool CRunningScriptHack::_014D_text_pager()
{
	char pagerText[8];
	
	strcpy_s(pagerText, reinterpret_cast<char *>(&CTheScripts::ScriptSpace[this->m_dwScriptIP]));
	this->m_dwScriptIP += 8;
	
	this->CollectParameters(&this->m_dwScriptIP, 3);

	wchar_t *scmPagerText = TheText.Get(pagerText);

	CPagerHack *pager = reinterpret_cast<CPagerHack *>(&CUserDisplay::Pager); //YUCKY YUCKY!!! but it'll do the job
	pager->AddMessage(scmPagerText, ScriptParams[0].uint16, ScriptParams[1].uint16, ScriptParams[2].uint16);
	
	return 0;
}
