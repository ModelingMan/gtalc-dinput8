#include "CRunningScriptHack.h"
#include "CPagerHack.h"
#include "CScrollBarHack.h"
#include "CCranesHack.h"
#include "CExplosionHack.h"
#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"
#include "SilentCall.h"

#include <string.h>
#include <Windows.h>

using namespace VCGlobals;

unsigned long *ProcessOneCommandHackAddr = reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x0044FDB6));

// GetRandomCarOfTypeInAreaNoSave
static void GetRandomCarOfTypeInAreaNoSave();
unsigned long getRandomCarProceedJump = vcversion::AdjustOffset(0x0062F23D);
unsigned long getRandomCarEndJump = vcversion::AdjustOffset(0x0062F269);

// GangsInitialise
static void GangsInitialise();
unsigned long gangInitialiseEndJump = vcversion::AdjustOffset(0x004EEEDF);

// ProjectileInfoUpdate
static void ProjectileInfoUpdate();
unsigned long projectileInfoUpdateProceedJump = vcversion::AdjustOffset(0x005C6ECC);
unsigned long projectileInfoUpdateEndJump = vcversion::AdjustOffset(0x005C6F45);

// CamControl
static void CamControl();
unsigned long camControlOther = vcversion::AdjustOffset(0x00472BF9);
unsigned long camControlCar = vcversion::AdjustOffset(0x00472C02);

int CRunningScriptHack::debugMode;

bool CRunningScriptHack::initialise()
{
	//Memory is protected from write (write protection of .text section removed at startup)
	union { bool (CRunningScriptHack::*func)(); unsigned long offset; } nasty = { &ProcessOneCommandHack };
	*ProcessOneCommandHackAddr = nasty.offset - reinterpret_cast<unsigned long>(ProcessOneCommandHackAddr + 1);

	// detonator weapon switch
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x005D49C7)) = 0xD;
	memset(reinterpret_cast<void *>(vcversion::AdjustOffset(0x005345ED)), 0x90, 9);

	// second helicopter
	*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x004D1E0F)) = 2;

	// 0410 (Purple Nines) fix
	call(0x004EEED1, &GangsInitialise, PATCH_JUMP);

	// 053E accept mission vehicles - workaround for crusher
	call(0x0062F234, &GetRandomCarOfTypeInAreaNoSave, PATCH_JUMP);

	// ProjectileInfo null thrower fix
	call(0x005C6EC6, &ProjectileInfoUpdate, PATCH_JUMP);

	// RC Baron camera controls
	*reinterpret_cast<float *>(vcversion::AdjustOffset(0x0068ABF4)) = 0.0;
	*reinterpret_cast<float *>(vcversion::AdjustOffset(0x0068ABEC)) = 0.0;
	call(0x00483F6A, 0x00483F7D, PATCH_JUMP);
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00597CBE)) = 3;
	call(0x00472BE8, &CamControl, PATCH_JUMP);

	// RC Baron process engine - temporary workaround affects RC helicopters
	*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x005F3925)) = 342;
	*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x005F392C)) = 342;
	*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x005F395B)) = 342;
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x005F394C)) = 80;
	*reinterpret_cast<float *>(vcversion::AdjustOffset(0x005F3973)) = 90.0;
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x005F55CA)) = 0x2B;

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

	case 0x01EE:
		return this->_01EE_activate_crane();
		break;

	case 0x01EF:
		return this->_01EF_deactivate_crane();
		break;

	case 0x024C:
		return this->_024C_set_phone_message();
		break;

	case 0x02BD:
		return this->_02BD_is_debug_mode();
		break;

	case 0x02FB:
		return this->_02FB_activate_crusher_crane();
		break;

	case 0x034A:	// set_portland_complete
		CScrollBarHack::ms_PortlandComplete = true;
		break;

	case 0x034B:	// set_staunton_complete
		CScrollBarHack::ms_StauntonComplete = true;
		break;

	case 0x034C:	// set_shoreside_complete
		CScrollBarHack::ms_ShoresideComplete = true;
		break;

	case 0x0351:
		return this->_0351_is_nasty_game();
		break;

	case 0x0356:
		return this->_0356_is_explosion_in_area();
		break;

	case 0x0368:
		return this->_0368_activate_military_crane();
		break;

	case 0x03A0:
		return this->_03A0_is_crane_lifting_car();
		break;

	case 0x03C2:
		return this->_03C2_is_phone_displaying_message();
		break;

	case 0x03EC:
		return this->_03EC_has_military_crane_collected_all_cars();
		break;

	case 0x0410:
		return this->_0410_set_gang_ped_model_preference();
		break;

	case 0x0421:
		return this->_0421_force_rain();
		break;

	case 0x0422:
		return this->_0422_does_garage_contain_car();
		break;

	case 0x042A:
		return this->_042A_is_threat_for_ped_type();
		break;

	case 0x0444:
		return this->_0444_set_script_fire_audio();
		break;

	case 0x0447:
		return this->_0447_is_player_lifting_a_phone();
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

bool CRunningScriptHack::_01EE_activate_crane()
{
	this->CollectParameters(&this->m_dwScriptIP, 10);
	float temp;
	if (ScriptParams[2].float32 > ScriptParams[4].float32) {
		temp = ScriptParams[4].float32;
		ScriptParams[4].float32 = ScriptParams[2].float32;
		ScriptParams[2].float32 = temp;
	}
	if (ScriptParams[3].float32 > ScriptParams[5].float32) {
		temp = ScriptParams[5].float32;
		ScriptParams[5].float32 = ScriptParams[3].float32;
		ScriptParams[3].float32 = temp;
	}
	ScriptParams[9].float32 = ScriptParams[9].float32 * 3.1415927f * 5.5555557e-3f;
	CCranesHack::ActivateCrane(ScriptParams[2].float32, ScriptParams[4].float32, ScriptParams[3].float32, ScriptParams[5].float32, ScriptParams[6].float32, ScriptParams[7].float32, ScriptParams[8].float32, ScriptParams[9].float32, false, false, ScriptParams[0].float32, ScriptParams[1].float32);
	return 0;
}

bool CRunningScriptHack::_01EF_deactivate_crane()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CCranesHack::DeActivateCrane(ScriptParams[0].float32, ScriptParams[1].float32);
	return 0;
}

bool CRunningScriptHack::_024C_set_phone_message()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	char text[8];
	strcpy_s(text, reinterpret_cast<char *>(&CTheScripts::ScriptSpace[this->m_dwScriptIP]));
	this->m_dwScriptIP += 8;
	wchar_t *string = TheText.Get(text);
	auto SetPhoneMessage_JustOnce = (void(__thiscall *)(uintptr_t, DWORD, wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *))vcversion::AdjustOffset(0x43C430);
	SetPhoneMessage_JustOnce(vcversion::AdjustOffset(0x817CF0), ScriptParams[0].int32, string, NULL, NULL, NULL, NULL, NULL);
	return 0;
}

bool CRunningScriptHack::_02BD_is_debug_mode()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag(!!(debugMode & ScriptParams[0].int32));
	return 0;
}

bool CRunningScriptHack::_02FB_activate_crusher_crane()
{
	this->CollectParameters(&this->m_dwScriptIP, 10);
	float temp;
	if (ScriptParams[2].float32 > ScriptParams[4].float32) {
		temp = ScriptParams[4].float32;
		ScriptParams[4].float32 = ScriptParams[2].float32;
		ScriptParams[2].float32 = temp;
	}
	if (ScriptParams[3].float32 > ScriptParams[5].float32) {
		temp = ScriptParams[5].float32;
		ScriptParams[5].float32 = ScriptParams[3].float32;
		ScriptParams[3].float32 = temp;
	}
	ScriptParams[9].float32 = ScriptParams[9].float32 * 3.1415927f * 5.5555557e-3f;
	CCranesHack::ActivateCrane(ScriptParams[2].float32, ScriptParams[4].float32, ScriptParams[3].float32, ScriptParams[5].float32, ScriptParams[6].float32, ScriptParams[7].float32, ScriptParams[8].float32, ScriptParams[9].float32, true, false, ScriptParams[0].float32, ScriptParams[1].float32);
	return 0;
}

bool CRunningScriptHack::_0351_is_nasty_game()
{
	this->UpdateCompareFlag(*(bool *)vcversion::AdjustOffset(0x68DD68));
	return 0;
}

bool CRunningScriptHack::_0356_is_explosion_in_area()
{
	this->CollectParameters(&this->m_dwScriptIP, 7);
	this->UpdateCompareFlag(CExplosionHack::TestForExplosionInArea(ScriptParams[0].int32, ScriptParams[1].float32, ScriptParams[4].float32, ScriptParams[2].float32, ScriptParams[5].float32, ScriptParams[3].float32, ScriptParams[6].float32));
	return 0;
}

bool CRunningScriptHack::_0368_activate_military_crane()
{
	this->CollectParameters(&this->m_dwScriptIP, 10);
	float temp;
	if (ScriptParams[2].float32 > ScriptParams[4].float32) {
		temp = ScriptParams[4].float32;
		ScriptParams[4].float32 = ScriptParams[2].float32;
		ScriptParams[2].float32 = temp;
	}
	if (ScriptParams[3].float32 > ScriptParams[5].float32) {
		temp = ScriptParams[5].float32;
		ScriptParams[5].float32 = ScriptParams[3].float32;
		ScriptParams[3].float32 = temp;
	}
	ScriptParams[9].float32 = ScriptParams[9].float32 * 3.1415927f * 5.5555557e-3f;
	CCranesHack::ActivateCrane(ScriptParams[2].float32, ScriptParams[4].float32, ScriptParams[3].float32, ScriptParams[5].float32, ScriptParams[6].float32, ScriptParams[7].float32, ScriptParams[8].float32, ScriptParams[9].float32, false, true, ScriptParams[0].float32, ScriptParams[1].float32);
	return 0;
}

bool CRunningScriptHack::_03A0_is_crane_lifting_car()
{
	this->CollectParameters(&this->m_dwScriptIP, 3);
	auto VehiclePoolGetStruct = (uintptr_t(__thiscall *)(void *, int))vcversion::AdjustOffset(0x451C70);
	void **carPool = (void **)vcversion::AdjustOffset(0xA0FDE4);
	this->UpdateCompareFlag(CCranesHack::IsThisCarPickedUp(ScriptParams[0].float32, ScriptParams[1].float32, VehiclePoolGetStruct(*carPool, ScriptParams[2].int32)));
	return 0;
}

bool CRunningScriptHack::_03C2_is_phone_displaying_message()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag((ScriptParams[0].int32 * 0x34 + vcversion::AdjustOffset(0x817CF0) + 8) == *(DWORD *)vcversion::AdjustOffset(0x7030E8));
	return 0;
}

bool CRunningScriptHack::_03EC_has_military_crane_collected_all_cars()
{
	this->UpdateCompareFlag(CCranes::carsCollectedMilitaryCrane == MILITARYCRANETOTAL);
	return 0;
}

bool CRunningScriptHack::_0410_set_gang_ped_model_preference()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	*(BYTE *)(ScriptParams[0].int32 * 0x18 + vcversion::AdjustOffset(0x7D925C)) = (BYTE)ScriptParams[1].int32;
	return 0;
}

bool CRunningScriptHack::_0421_force_rain()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	*(BYTE *)vcversion::AdjustOffset(0xA10B38) = (BYTE)(ScriptParams[0].int32 ? 1 : 0);
	return 0;
}

bool CRunningScriptHack::_0422_does_garage_contain_car()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	auto VehiclePoolGetStruct = (CVehicle *(__thiscall *)(void *, int))vcversion::AdjustOffset(0x451C70);
	void **carPool = (void **)vcversion::AdjustOffset(0xA0FDE4);
	this->UpdateCompareFlag(CGarages::garages[ScriptParams[0].int32].IsEntityEntirelyInside3D(VehiclePoolGetStruct(*carPool, ScriptParams[1].int32), 0.0));
	return 0;
}

bool CRunningScriptHack::_042A_is_threat_for_ped_type()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	this->UpdateCompareFlag(ScriptParams[1].int32 == (*(DWORD *)(*(DWORD *)(vcversion::AdjustOffset(0xA0DA64) + ScriptParams[0].int32 * 4) + 0x18) & ScriptParams[1].int32));
	return 0;
}

bool CRunningScriptHack::_0444_set_script_fire_audio()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CFireManager::fires[ScriptParams[0].int32].sfx = (char)(ScriptParams[1].int32 ? 1 : 0);
	return 0;
}

bool CRunningScriptHack::_0447_is_player_lifting_a_phone()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag(*(DWORD *)(*(DWORD *)(CWorld::Players + 0x170 * ScriptParams[0].int32) + 0x244) == 0x13);
	return 0;
}

void __declspec(naked) GetRandomCarOfTypeInAreaNoSave()
{
	__asm
	{
		cmp byte ptr [ebx+1F8h], 1 // is traffic vehicle
		jz proceed
		cmp byte ptr [ebx+1F8h], 2 // is mission vehicle
		jz proceed
		jmp getRandomCarEndJump
	proceed:
		jmp getRandomCarProceedJump
	}
}

void GangsInitialise()
{
	for (int i = 0; i < 8 * 0x18; i += 0x18) {
		*(BYTE *)(i + vcversion::AdjustOffset(0x7D925C)) = 255;
	}
}

void __declspec(naked) ProjectileInfoUpdate()
{
	__asm
	{
		mov eax, [ebp+4] // get pointer of projectile thrower
		test eax, eax    // compare pointer with 0
		jz end
		mov eax, [ebp+0]
		cmp eax, 0Ch
		jmp projectileInfoUpdateProceedJump
	end:
		jmp projectileInfoUpdateEndJump

	}
}

void __declspec(naked) CamControl()
{
	__asm
	{
		mov eax, dword ptr [ebp+80Ch]
		mov edi, dword ptr [eax+29Ch]
		cmp edi, 1
		jz other
		movzx edi, word ptr [eax+5Ch] // get model index of vehicle
		cmp edi, 194                  // compare with model index of RC Baron
		jnz car
	other:
		jmp camControlOther
	car:
		jmp camControlCar
	}
}
