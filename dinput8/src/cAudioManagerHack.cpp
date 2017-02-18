#include "cAudioManagerHack.h"
#include "CBridgeHack.h"
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "ModelIndices.h"
#include <Windows.h>
#include <math.h>

#define REPORT_AMBULANCE     234
#define REPORT_VAN           235
#define REPORT_TRUCK         236
#define REPORT_ECONOMY       237
#define REPORT_SPORTSCAR     238
#define REPORT_BUGGY         239
#define REPORT_TAXI          240
#define REPORT_CRUISER       241
#define REPORT_BUS           242
#define REPORT_COUPE         243
#define REPORT_FIRETRUCK     244
#define REPORT_BOAT          245
#define REPORT_PICKUP        246
#define REPORT_ICECREAMTRUCK 247
#define REPORT_LIMO          248
#define REPORT_POLICECAR     249
#define REPORT_CONVERTIBLE   250
#define REPORT_SUBWAYCAR     251
#define REPORT_TANK          252
#define REPORT_NONE          0

#define REPORT_LIBERTYCITY     210
#define REPORT_PORTLAND        211
#define REPORT_STAUNTONISLAND  212
#define REPORT_SHORESIDEVALE   213
#define REPORT_ROCKFORD        214
#define REPORT_FORTSTAUNTON    215
#define REPORT_ASPATRIA        216
#define REPORT_TORRINGTON      217
#define REPORT_BEDFORDPOINT    218
#define REPORT_NEWPORT         219
#define REPORT_BELLEVILLE      220
#define REPORT_LIBERTYCAMPUS   221
#define REPORT_COCHRANE        222
#define REPORT_PIKECREEK       223
#define REPORT_CEDARGROVE      253
#define REPORT_WICHITAGARDENS  254
#define REPORT_FRANCISINTL     255
#define REPORT_CALLAHANPOINT   256
#define REPORT_ATLANTICQUAYS   257
#define REPORT_PORTLANDHARBOR  258
#define REPORT_TRENTON         259
#define REPORT_CHINATOWN       260
#define REPORT_REDLIGHT        261
#define REPORT_HEPBURNHEIGHTS  262
#define REPORT_SAINTMARKS      263
#define REPORT_HARWOOD         264
#define REPORT_PORTLANDBEACH   265
#define REPORT_PORTLANDVIEW    489

#define TOTAL_AUDIO_ZONES 36

#define FRONT_END_96              465
#define LOOPING_SCRIPT_OBJECT_A   466
#define LOOPING_SCRIPT_OBJECT_B   467
static unsigned int scriptObjectCinemaTime;
#define LOOPING_SCRIPT_OBJECT_62  468
#define LOOPING_SCRIPT_OBJECT_64  469
#define LOOPING_SCRIPT_OBJECT_66  471
#define LOOPING_SCRIPT_OBJECT_30  472
#define LOOPING_SCRIPT_OBJECT_32  473
#define LOOPING_SCRIPT_OBJECT_5   474
#define LOOPING_SCRIPT_OBJECT_41A 475
#define LOOPING_SCRIPT_OBJECT_41B 476
#define LOOPING_SCRIPT_OBJECT_42  477
#define LOOPING_SCRIPT_OBJECT_44  478
#define LOOPING_SCRIPT_OBJECT_7   479
#define LOOPING_SCRIPT_OBJECT_60  480
#define LOOPING_SCRIPT_OBJECT_71  481
#define LOOPING_SCRIPT_OBJECT_73  482
#define LOOPING_SCRIPT_OBJECT_37A 483
#define LOOPING_SCRIPT_OBJECT_37B 484
static unsigned int scriptObjectSawmillTime;
#define LOOPING_SCRIPT_OBJECT_51A 485
#define LOOPING_SCRIPT_OBJECT_51B 486
#define LOOPING_SCRIPT_OBJECT_51C 487
#define LOOPING_SCRIPT_OBJECT_51D 488
static unsigned int scriptObjectAirportTime;
static unsigned char scriptObjectAirportCounter;
#define LOOPING_SCRIPT_OBJECT_59A 490
#define LOOPING_SCRIPT_OBJECT_59B 491
#define LOOPING_SCRIPT_OBJECT_59C 492
#define LOOPING_SCRIPT_OBJECT_59D 493
#define LOOPING_SCRIPT_OBJECT_59E 494
static unsigned int scriptObjectHomeTime;
static unsigned char scriptObjectHomeCounter;
#define LOOPING_SCRIPT_OBJECT_77A 165
#define LOOPING_SCRIPT_OBJECT_77B 167
static unsigned int scriptObjectCellBeatingTime;
static unsigned char scriptObjectCellBeatingCounter;
#define LOOPING_SCRIPT_OBJECT_102 153

#define BRIDGE_WARNING 495
#define BRIDGE_ONE_SHOT 132
#define BRIDGE_MOTOR 319

struct PoliceRadioZone
{
	char zone[8];
	int sfx;
	int padding;
} policeRadioZones[TOTAL_AUDIO_ZONES] =
{
	{ "HOSPI_2", REPORT_ROCKFORD,       0 },
	{ "CONSTRU", REPORT_FORTSTAUNTON,   0 },
	{ "STADIUM", REPORT_ASPATRIA,       0 },
	{ "YAKUSA",  REPORT_TORRINGTON,     0 },
	{ "SHOPING", REPORT_BEDFORDPOINT,   0 },
	{ "COM_EAS", REPORT_NEWPORT,        0 },
	{ "PARK",    REPORT_BELLEVILLE,     0 },
	{ "UNIVERS", REPORT_LIBERTYCAMPUS,  0 },
	{ "BIG_DAM", REPORT_COCHRANE,       0 },
	{ "SUB_IND", REPORT_PIKECREEK,      0 },
	{ "SWANKS",  REPORT_CEDARGROVE,     0 },
	{ "PROJECT", REPORT_WICHITAGARDENS, 0 },
	{ "AIRPORT", REPORT_FRANCISINTL,    0 },
	{ "PORT_W",  REPORT_CALLAHANPOINT,  0 },
	{ "PORT_S",  REPORT_ATLANTICQUAYS,  0 },
	{ "PORT_E",  REPORT_PORTLANDHARBOR, 0 },
	{ "PORT_I",  REPORT_TRENTON,        0 },
	{ "CHINA",   REPORT_CHINATOWN,      0 },
	{ "REDLIGH", REPORT_REDLIGHT,       0 },
	{ "TOWERS",  REPORT_HEPBURNHEIGHTS, 0 },
	{ "LITTLEI", REPORT_SAINTMARKS,     0 },
	{ "HARWOOD", REPORT_HARWOOD,        0 },
	{ "EASTBAY", REPORT_PORTLANDBEACH,  0 },
	{ "S_VIEW",  REPORT_PORTLANDVIEW,   0 },
	{ "CITYZON", REPORT_LIBERTYCITY,    0 },
	{ "IND_ZON", REPORT_PORTLAND,       0 },
	{ "COM_ZON", REPORT_STAUNTONISLAND, 0 },
	{ "SUB_ZON", REPORT_SHORESIDEVALE,  0 },
	{ "SUB_ZO2", REPORT_SHORESIDEVALE,  0 },
	{ "SUB_ZO3", REPORT_SHORESIDEVALE,  0 },
	{ "A",       REPORT_ROCKFORD,       0 },
	{ "A",       REPORT_ROCKFORD,       0 },
	{ "A",       REPORT_ROCKFORD,       0 },
	{ "A",       REPORT_ROCKFORD,       0 },
	{ "A",       REPORT_ROCKFORD,       0 },
	{ 0,         0,                     0 }
};

struct VehicleSfx
{
	int npcEngine;
	int playerEngine;
	int horn;
	int hornPitch;
	int siren;
	int sirenPitch;
	int door;
} presetVehicleSfx[107] =
{
	{ 277, 13, 0, 26513, 52,  9935, 1 }, // landstal
	{ 278, 14, 4, 11487, 52,  9935, 0 }, // idaho
	{ 274, 10, 6, 10400, 52, 10123, 1 }, // banshee
	{ 272,  8, 7, 29711, 52,  9935, 2 }, // linerun
	{ 278, 14, 4, 12893, 52,  8941, 0 }, // peren
	{ 271,  7, 1, 10706, 52, 11922, 1 }, // sentinel
	{ 268,  0, 7, 29711, 52,  9700, 1 }, // rio
	{ 272,  8, 7, 29711, 27, 11556, 2 }, // firetruk
	{ 272,  8, 7, 31478, 52,  8941, 2 }, // trash
	{ 278, 14, 1,  9538, 52, 12220, 1 }, // stretch
	{ 278, 14, 4, 10842, 52,  9935, 0 }, // manana
	{ 269,  5, 1, 12017, 52,  9935, 1 }, // infernus
	{ 277, 13, 0, 22293, 52,  9935, 1 }, // yardie
	{ 270,  6, 3, 18000, 52, 13400, 1 }, // pony
	{ 270,  6, 2, 18286, 52,  9935, 2 }, // mule
	{ 274, 10, 6, 10000, 52,  9500, 0 }, // hotring
	{ 270,  6, 0, 22295, 29,  8795, 2 }, // ambulan
	{ 268,  4, 3, 17900, 27, 10511, 2 }, // fbiranch
	{ 278, 14, 4, 12170, 52,  8000, 1 }, // moonbeam
	{ 278, 14, 3, 12345, 52,  9935, 0 }, // esperant
	{ 277, 13, 1, 10796, 52,  8543, 1 }, // taxi
	{ 271,  7, 1,  9003, 52,  9935, 1 }, // mafia
	{ 277, 13, 5, 10924, 52,  9935, 1 }, // bobcat
	{ 278, 14, 5, 11025, 31, 11025, 0 }, // mrwhoop
	{ 273,  9, 0, 26513, 52,  9935, 1 }, // bfinject
	{ 453, 30, 0, 26513, 52,  9200, 1 }, // hunter
	{ 271,  7, 1, 10706, 27, 13596, 1 }, // police
	{ 270,  6, 2, 17260, 27, 13000, 2 }, // enforcer
	{ 270,  6, 5,  8670, 52,  9935, 0 }, // securica
	{ 271,  7, 1, 10500, 52,  9100, 1 }, // washing
	{ 268,  0, 0, 26513, 27, 13596, 1 }, // predator
	{ 272,  8, 3, 11652, 52, 10554, 3 }, // bus
	{ 272,  8, 7, 29711, 52,  8000, 2 }, // rhino
	{ 272,  8, 7, 28043, 52,  9935, 2 }, // barracks
	{ 273,  9, 0, 25400, 52,  9800, 0 }, // cuban
	{ 268,  0, 0, 26513, 52,  9935, 1 }, // chopper
	{ 284, 20, 0, 26313, 52, 10000, 1 }, // angel
	{ 272,  8, 2, 16291, 52,  7500, 3 }, // coach
	{ 278, 14, 4, 10842, 52,  9935, 0 }, // cabbie
	{ 278, 14, 4, 10233, 52,  8935, 0 }, // stallion
	{ 270,  6, 5,  8670, 52,  8935, 0 }, // rumpo
	{ 423, 17, 5, 20000, 52, 17000, 1 }, // rcbandit
	{ 278, 14, 0, 26513, 52, 10000, 0 }, // corpse
	{ 272,  8, 7, 29000, 52,  9400, 2 }, // packer
	{ 270,  6, 0, 21043, 52,  9000, 0 }, // panlant
	{ 271,  7, 6,  9271, 52,  9935, 1 }, // kuruma
	{ 268,  0, 3, 15554, 52,  9100, 1 }, // squalo
	{ 268,  0, 3, 13857, 52,  9000, 2 }, // seaspar
	{ 285, 21, 0, 30000, 52,  9100, 1 }, // pizzaboy
	{ 270,  6, 0, 21043, 52,  9935, 2 }, // hoods
	{ 268,  0, 0, 21043, 52,  9935, 1 }, // airtrain
	{ 268,  0, 0, 21043, 52,  9935, 1 }, // deaddodo
	{ 268,  0, 0, 21043, 52,  9935, 1 }, // speeder
	{ 268,  0, 0, 21043, 52,  9935, 1 }, // reefer
	{ 268,  0, 0, 21043, 52,  9700, 1 }, // tropic
	{ 272,  8, 7, 28043, 52,  9935, 2 }, // flatbed
	{ 270,  6, 2, 18286, 52,  9935, 2 }, // yankee
	{ 279, 15, 0, 28500, 52,  9800, 1 }, // caddy
	{ 278, 14, 4, 10842, 52,  9935, 0 }, // borgnine
	{ 270,  6, 3, 18000, 52, 13400, 1 }, // toyz
	{ 461, 35, 0, 26513, 52,  9700, 1 }, // skimmer
	{ 287, 23, 0, 27000, 52,  9600, 1 }, // pcj600
	{ 285, 21, 0, 31000, 52,  9500, 1 }, // faggio
	{ 284, 20, 5, 11000, 52,  9400, 1 }, // freeway
	{ 423, 17, 0, 30000, 52,  9935, 0 }, // dodo
	{ 425, 18, 0, 30000, 52, 15000, 1 }, // rcraider
	{ 276, 12, 4, 10300, 52,  9100, 0 }, // glendale
	{ 276, 12, 4, 10500, 52,  9000, 0 }, // blistac
	{ 286, 22, 0, 30000, 52,  9000, 1 }, // sanchez
	{ 268,  0, 0, 26513, 52,  9100, 2 }, // delofly
	{ 270,  6, 7, 29711, 52,  7948, 2 }, // patriot
	{ 274, 10, 5, 11200, 52,  9300, 1 }, // lovefist
	{ 268,  0, 0, 26513, 52,  9935, 1 }, // ghost
	{ 268,  0, 0, 26513, 52,  9500, 1 }, // dinghy
	{ 276, 12, 4, 10700, 52,  9600, 0 }, // comet
	{ 273,  9, 1,  9200, 52,  9700, 0 }, // sabretur
	{ 273,  9, 3, 13857, 52,  9935, 0 }, // diablos
	{ 274, 10, 0, 26513, 52,  9900, 1 }, // phoenix
	{ 278, 14, 4, 10540, 52,  9935, 2 }, // walton
	{ 275, 11, 5, 11000, 52,  9700, 1 }, // regina
	{ 274, 10, 6, 11025, 52, 10928, 1 }, // stinger
	{ 274, 10, 1,  9700, 52,  9700, 1 }, // delodrv
	{ 275, 11, 3, 18000, 52,  9600, 0 }, // burrito
	{ 273,  9, 6, 10500, 52,  9500, 0 }, // sandking
	{ 268,  0, 0, 26513, 52,  9400, 1 }, // marquis
	{ 275, 11, 0, 27513, 52,  9300, 1 }, // baggage
	{ 268,  4, 4, 10842, 52,  9200, 0 }, // zebra
	{ 268,  0, 0, 26513, 52,  9100, 2 }, // maverick
	{ 268,  0, 0, 26513, 52,  9000, 2 }, // vcnmav
	{ 277, 13, 3, 18000, 52,  9100, 2 }, // rancher
	{ 271,  7, 6,  9271, 27, 16168, 1 }, // fbicar
	{ 271,  7, 0, 26513, 52,  9200, 1 }, // virgo
	{ 275, 11, 1,  9600, 52,  9300, 1 }, // greenwoo
	{ 271,  0, 0, 26513, 52,  9400, 1 }, // jetmax
	{ 269,  5, 6, 11025, 52, 13600, 1 }, // cheetah
	{ 273,  9, 5, 10924, 52,  9935, 0 }, // columb
	{ 277, 13, 0, 22295, 52, 12200, 1 }, // blista
	{ 268,  0, 0, 26513, 52,  9800, 1 }, // polmav
	{ 270,  6, 0, 21043, 52,  9935, 0 }, // bellyup
	{ 270,  6, 0, 21043, 52,  9935, 0 }, // mrwongs
	{ 268,  4, 0, 26513, 52,  9700, 1 }, // mesa
	{ 425, 18, 0, 26513, 52,  9600, 1 }, // rcgoblin
	{ 273, 9, 79, 26513, 52,  9700, 1 }, // genlee
	{ 274, 10, 3, 15554, 52,  9935, 1 }, // yakuza
	{ 268,  4, 0, 26513, 52,  9500, 1 }, // bloodra
	{ 271,  7, 6, 12375, 52,  9400, 1 }, // admiral
	{ 269,  5, 6, 11025, 52, 13600, 1 } // vicechee
};

struct PedSfxDelay
{
	int fixedDelay;
	int randomDelay;
	int reuseDelay;
	int reuseRandomDelay;
} presetPedSfxDelay[56] =
{
	{  500,  800,  500,    2 },
	{  500,  800,  500,    2 },
	{  500,  800,  500,    2 },
	{  500,  800,  500,    2 },
	{  100,    2,  100,    2 },
	{  700,  500, 1000,  500 },
	{ 2000,   50, 2050, 1000 },
	{ 5000, 2000, 15000, 3000 },
	{ 5000, 2000, 7000, 3000 },
	{ 6000, 6000, 6000, 6000 },
	{ 3000, 1000, 4000, 1000 },
	{ 6000, 6000, 6000, 6000 },
	{ 4000, 1000, 5000, 1000 },
	{ 3000, 1000, 4000, 1000 },
	{ 1000, 1000, 2000, 2000 },
	{ 1000, 1000, 2000, 2000 },
	{ 1000,  500, 2000, 1500 },
	{ 1000,  500, 2000, 1500 },
	{  800,  200, 1000,  500 },
	{  800,  200, 1000,  500 },
	{  800,  400, 2000, 1000 },
	{  800,  400, 2000, 1000 },
	{ 2000, 2000, 4000, 1000 },
	{ 4000, 1000, 5000, 1000 },
	{  800,  400, 1200,  500 },
	{ 5000, 1000, 6000, 2000 },
	{ 5000, 1000, 6000, 2000 },
	{ 5000, 1000, 6000, 2000 },
	{ 5000, 1000, 6000, 2000 },
	{ 5000, 1000, 6000, 2000 },
	{ 5000, 1000, 6000, 2000 },
	{ 5000, 1000, 6000, 2000 },
	{ 4000, 2000, 7000, 2000 },
	{ 1000,  300, 2000, 1000 },
	{  400,  300, 2000, 1000 },
	{ 2000, 1000, 2500, 1500 },
	{  200,  200,  200,  200 },
	{  400,  300, 4000, 1000 },
	{  400,  300, 4000, 1000 },
	{ 1000,  500, 3000, 1000 },
	{ 1000,  500, 1000, 1000 },
	{ 3000, 2000, 3000, 2000 },
	{ 3000, 2000, 3000, 2000 },
	{ 3000, 2000, 3000, 2000 },
	{ 2500, 1000, 5000, 5000 },
	{ 1000,  500, 3000, 6000 },
	{ 4000, 1000, 5000, 1000 },
	{ 1000,  500, 2000, 4000 },
	{ 1000,  500, 2000, 4000 },
	{ 1000,  500, 2000, 5000 },
	{ 1000,  500, 3000, 2000 },
	{ 1000,  500, 3000, 2000 },
	{ 1600, 1000, 2000, 2000 },
	{ 3000, 2000, 5000, 3000 },
	{ 3000, 2000, 5000, 3000 },
	{ 0, 0, 0, 0 }
};

short audioZones[TOTAL_AUDIO_ZONES] = {};
bool isPlayerSfxTommy;

// ProcessFrontEndHackProxy
unsigned long JumpTableForFrontEnd = vcversion::AdjustOffset(0x006B28B8);
unsigned long OffsetIfWeHackedFrontEnd = vcversion::AdjustOffset(0x005DBE5E);
// SetupSuspectLastSeenReportHackProxy
unsigned long setupSuspectLastSeenReportMatch = vcversion::AdjustOffset(0x005FD6B8);
unsigned long setupSuspectLastSeenReportNoMatch = vcversion::AdjustOffset(0x005FD6B0);
// ProcessVehicleSirenOrAlarmHack
unsigned long fbiNoMatchEndJump = vcversion::AdjustOffset(0x005F03F0);
unsigned long fbiMatchEndJump = vcversion::AdjustOffset(0x005F03FF);

bool cAudioManagerHack::initialise()
{
	unsigned long ProcessFrontEndHackAddr = vcversion::AdjustOffset(0x005DBCA7);

	//Memory is protected from write (write protection of .text section removed at startup)
	*reinterpret_cast<unsigned char *>(ProcessFrontEndHackAddr) = 0xB9;						// mov ecx,
	*reinterpret_cast<void (**)()>(ProcessFrontEndHackAddr + 1) = ProcessFrontEndHackProxy; //          ProcessFrontEndHackProxy
	*reinterpret_cast<unsigned short *>(ProcessFrontEndHackAddr + 5) = 0xE1FF;				// jmp ecx

	// car alarms
	if (!GetPrivateProfileInt("Misc", "UseVCCarAlarm", 0, "./gta-lc.ini")) {
		Patch<unsigned int>(0x005F02F9, 0);
		Patch<unsigned long>(0x005F0457, vcversion::AdjustOffset(0x006AD1B0));
		Patch<unsigned long>(0x005F046D, vcversion::AdjustOffset(0x006AD1B4));
	}

	// suspect last seen report, requires modification of sfx
	InjectHook(0x005FD58C, &cAudioManagerHack::SetupSuspectLastSeenReportHackProxy, PATCH_JUMP);

	// set up crime report
	Patch<unsigned char>(0x005FDBFF, TOTAL_AUDIO_ZONES);
	Patch<unsigned char>(0x005FDC4A, TOTAL_AUDIO_ZONES);
	Patch<unsigned char>(0x005FDC4F, TOTAL_AUDIO_ZONES);
	Patch<unsigned long>(0x005FDC27, (unsigned long)&policeRadioZones + 4);
	Patch<unsigned long>(0x005FDC2F, (unsigned long)&policeRadioZones);
	Patch<unsigned long>(0x005FDC3D, (unsigned long)&policeRadioZones + 8);

	// play suspect last seen
	Patch<unsigned char>(0x005FCF39, TOTAL_AUDIO_ZONES);
	Patch<unsigned char>(0x005FCF87, TOTAL_AUDIO_ZONES);
	Patch<unsigned char>(0x005FCF8C, TOTAL_AUDIO_ZONES);
	Patch<unsigned long>(0x005FCF5F, (unsigned long)&policeRadioZones + 4);
	Patch<unsigned long>(0x005FCF67, (unsigned long)&policeRadioZones);
	Patch<unsigned long>(0x005FCF75, (unsigned long)&policeRadioZones + 8);

	// do not use game's audio zone array
	InjectHook(0x004DDAEB, &cAudioManagerHack::InitialiseAudioZoneArrayHack);
	
	// crane audio
	auto function = &cAudioManagerHack::ProcessCraneAndBridge;
	InjectHook(0x005F596C, (unsigned long &)function);
	Patch<unsigned char>(0x005F5E6C, 5);

	// looping script objects
	auto function2 = &cAudioManagerHack::ProcessLoopingScriptObjectHack;
	InjectHook(0x005F58F3, (unsigned long &)function2);
	scriptObjectCinemaTime = scriptObjectSawmillTime = scriptObjectAirportTime = scriptObjectHomeTime = scriptObjectCellBeatingTime = CTimer::m_snTimeInMilliseconds;
	scriptObjectAirportCounter = scriptObjectHomeCounter = scriptObjectCellBeatingCounter = 0;

	// RC Baron process engine - temporary workaround affects RC helicopters
	Patch<unsigned int>(0x005F3925, 342);
	Patch<unsigned int>(0x005F392C, 342);
	Patch<unsigned int>(0x005F395B, 342);
	Patch<unsigned char>(0x005F394C, 80);
	Patch<float>(0x005F3973, 90.0);
	Patch<unsigned char>(0x005F55CA, 0x2B);

	// crime report fix (SilentPatch)
	Patch<unsigned int>(0x005FDDDB, 0xC5);

	// radio station text shadow fix (SilentPatch)
	InjectHook(0x005FA1FD, &cAudioManagerHack::DisplayRadioStationNameHack);

	// vehicle sfx
	InjectHook(0x005F8A30, &cAudioManagerHack::InitialiseHack, PATCH_JUMP);

	// do not change vice cheetah siren pitch
	InjectHook(0x005F0417, vcversion::AdjustOffset(0x005F03F0), PATCH_JUMP);

	// fbi alt siren
	InjectHook(0x005F03DD, &cAudioManagerHack::ProcessVehicleSirenOrAlarmHack, PATCH_JUMP);

	// chopper dialogue
	Patch<unsigned int>(0x005EB3EC, 0x236);
	Patch<unsigned int>(0x005EB3FA, 0x8D3DCB09);
	Patch<unsigned char>(0x005EB427, 0x1D);
	Patch<unsigned int>(0x005EB42B, 0x236);

	// major changes to ped talk sfx
	auto function3 = &cAudioManagerHack::GetPedCommentSfxHack;
	InjectHook(0x005EB2D5, (unsigned long &)function3);

	// player talk sfx
	isPlayerSfxTommy = !!GetPrivateProfileInt("Misc", "UseTommySfx", 0, "./gta-lc.ini");

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
	case 96: //Pager sound
		this->m_SampleID = FRONT_END_96;
		break;
	default:
		return false;
	}

	return true;
}

void cAudioManagerHack::ProcessLoopingScriptObjectHack(unsigned char id)
{
	float maxDistance = 0.0, distance;
	unsigned char maxVolume = 0;

	switch (id) {
	case 5:
		maxDistance = 6400.0;
		this->m_MaxRange = 80.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_5;
		this->m_Unk0 = 0;
		maxVolume = 127;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 3;
		this->m_Unk6 = 3;
		this->m_Unk4 = 2.0;
		break;
	case 7:
		maxDistance = 6400.0;
		this->m_MaxRange = 80.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_7;
		this->m_Unk0 = 0;
		maxVolume = 127;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 3;
		this->m_Unk6 = 3;
		this->m_Unk4 = 2.0;
		break;
	case 30:
		maxDistance = 900.0;
		this->m_MaxRange = 30.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_30;
		this->m_Unk0 = 0;
		maxVolume = 127;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 3;
		this->m_Unk6 = 3;
		this->m_Unk4 = 2.0;
		break;
	case 32:
		maxDistance = 900.0;
		this->m_MaxRange = 30.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_32;
		this->m_Unk0 = 0;
		maxVolume = 127;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 3;
		this->m_Unk6 = 3;
		this->m_Unk4 = 2.0;
		break;
	case 37:
		this->ProcessSawMillScriptObject(id);
		break;
	case 41:
		this->ProcessLaunderetteScriptObject(id);
		break;
	case 42:
		maxDistance = 900.0;
		this->m_MaxRange = 30.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_42;
		this->m_Unk0 = 0;
		maxVolume = 110;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 3;
		this->m_Unk6 = 3;
		this->m_Unk4 = 2.0;
		break;
	case 44:
		maxDistance = 900.0;
		this->m_MaxRange = 30.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_44;
		this->m_Unk0 = 0;
		maxVolume = 110;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 3;
		this->m_Unk6 = 3;
		this->m_Unk4 = 2.0;
		break;
	case 51:
		this->ProcessAirportScriptObject(id);
		break;
	case 59:
		this->ProcessHomeScriptObject(id);
		break;
	case 60:
		maxDistance = 900.0;
		this->m_MaxRange = 30.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_60;
		this->m_Unk0 = 0;
		maxVolume = 127;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 3;
		this->m_Unk6 = 3;
		this->m_Unk4 = 2.0;
		break;
	case 62:
	case 64:
	case 66:
	case 91:
		this->ProcessCinemaScriptObject(id);
		break;
	case 71:
		maxDistance = 6400.0;
		this->m_MaxRange = 80.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_71;
		this->m_Unk0 = 0;
		maxVolume = 127;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 2;
		this->m_Unk6 = 3;
		this->m_Unk4 = 2.0;
		break;
	case 73:
		maxDistance = 6400.0;
		this->m_MaxRange = 80.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_73;
		this->m_Unk0 = 0;
		maxVolume = 127;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 3;
		this->m_Unk6 = 3;
		this->m_Unk4 = 2.0;
		break;
	case 77:
		this->ProcessPoliceCellBeatingScriptObject(id);
		break;
	case 102:
		maxDistance = 2500.0;
		this->m_MaxRange = 50.0;
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_102;
		this->m_Unk0 = 0;
		maxVolume = 80;
		this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
		this->m_Unk2 = 8;
		this->m_Unk6 = 10;
		this->m_Unk4 = 2.0;
		break;
	default:
		this->ProcessLoopingScriptObject(id);
		return;
	}
	distance = this->GetDistanceSquared(this->m_Position);
	if (distance < maxDistance) {
		this->m_DistanceToCamera = (distance > 0 ? sqrt(distance) : 0.0f);
		this->m_Volume = this->ComputeVolume(maxVolume, this->m_MaxRange, this->m_DistanceToCamera);
		if (this->m_Volume) {
			this->m_Unk7 = 0;
			this->m_Unk1 = 0;
			this->m_Unk8 = 0;
			this->m_Unk9 = 0;
			this->m_Unk10 = 1;
			this->m_MaxVolume = maxVolume;
			this->m_LoopStartOff = VCGlobals::SampleManager.GetSampleLoopStartOffset(this->m_SampleID);
			this->m_LoopEndOff = VCGlobals::SampleManager.GetSampleLoopEndOffset(this->m_SampleID);
			this->m_Unk12 = 0;
			this->AddSampleToRequestedQueue();
		}
	}
}

void cAudioManagerHack::InitialiseAudioZoneArrayHack()
{
	*reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x004DC392)) = (unsigned long)&audioZones; // CTheZones::FindAudioZone
	*reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x005FCF49)) = (unsigned long)&audioZones; // cAudioManager::PlaySuspectLastSeen
	*reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x005FDC0F)) = (unsigned long)&audioZones; // cAudioManager::SetupCrimeReport

	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004DC475)) = TOTAL_AUDIO_ZONES;
	*reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x004DC48A)) = (unsigned long)&audioZones;
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004DC4C4)) = TOTAL_AUDIO_ZONES;
	*reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x004DC4D9)) = (unsigned long)&audioZones;
	CTheZones::InitialiseAudioZoneArray();
}

void __declspec(naked) cAudioManagerHack::SetupSuspectLastSeenReportHackProxy()
{
	__asm
	{
		push eax
		call cAudioManagerHack::SetupSuspectLastSeenReportHack
		add esp, 4
		mov esi, eax  // get report sfx
		test eax, eax // compare sfx with 0
		jz noMatch
		jmp setupSuspectLastSeenReportMatch
	noMatch:
		jmp setupSuspectLastSeenReportNoMatch
	}
}

int cAudioManagerHack::SetupSuspectLastSeenReportHack(int model)
{
	switch (model) {
	case CAR_AMBULAN:
		return REPORT_AMBULANCE;
	case BOAT_DINGHY:
	case BOAT_GHOST:
	case BOAT_JETMAX:
	case BOAT_MARQUIS:
	case BOAT_PREDATOR:
	case BOAT_REEFER:
	case BOAT_RIO:
	case BOAT_SPEEDER:
	case BOAT_SQUALO:
	case BOAT_TROPIC:
		return REPORT_BOAT;
	case CAR_BFINJECT:
		return REPORT_BUGGY;
	case CAR_BUS:
	case CAR_COACH:
		return REPORT_BUS;
	case CAR_COMET:
	case CAR_IDAHO:
	case CAR_STALLION:
		return REPORT_CONVERTIBLE;
	case CAR_CORPSE:
	case CAR_ESPERANT:
	case CAR_MANANA:
		return REPORT_COUPE;
	case CAR_BLISTA:
	case CAR_LANDSTAL:
		return REPORT_CRUISER;
	case CAR_FBICAR:
	case CAR_KURUMA:
	case CAR_PEREN:
	case CAR_REGINA:
	case CAR_SENTINEL:
	case CAR_WASHING:
		return REPORT_ECONOMY;
	case CAR_FIRETRUK:
		return REPORT_FIRETRUCK;
	case CAR_MRWHOOP:
		return REPORT_ICECREAMTRUCK;
	case CAR_LOVEFIST:
	case CAR_STRETCH:
		return REPORT_LIMO;
	case CAR_BOBCAT:
	case CAR_PATRIOT:
		return REPORT_PICKUP;
	case CAR_POLICE:
		return REPORT_POLICECAR;
	case CAR_BANSHEE:
	case CAR_CHEETAH:
	case CAR_HOTRING:
	case CAR_INFERNUS:
	case CAR_PHOENIX:
	case CAR_STINGER:
		return REPORT_SPORTSCAR;
	case CAR_RHINO:
		return REPORT_TANK;
	case CAR_BORGNINE:
	case CAR_CABBIE:
	case CAR_TAXI:
	case CAR_ZEBRA:
		return REPORT_TAXI;
	case CAR_BARRACKS:
	case CAR_FLATBED:
	case CAR_PACKER:
	case CAR_TRASH:
		return REPORT_TRUCK;
	case CAR_ENFORCER:
	case CAR_MOONBEAM:
	case CAR_MRWONGS:
	case CAR_MULE:
	case CAR_PANLANT:
	case CAR_PONY:
	case CAR_RUMPO:
	case CAR_SECURICA:
	case CAR_TOYZ:
	case CAR_YANKEE:
		return REPORT_VAN;
	}
	return REPORT_NONE;
}

void cAudioManagerHack::ProcessCraneAndBridge()
{
	// process crane
	float distance;
	CCrane *crane = (CCrane *)*(unsigned long *)((unsigned long)&VCGlobals::AudioManager + this->m_AudioEntity * 0x28 + 0x1F14);
	if (crane && crane->activity == 1 && crane->status) {
		this->m_Position = crane->object->GetPos();
		distance = this->GetDistanceSquared(this->m_Position);
		if (distance < 6400.0) {
			this->m_DistanceToCamera = distance > 0.0 ? sqrt(distance) : 0.0f;
			this->m_Volume = this->ComputeVolume(100, 80.0, this->m_DistanceToCamera);
			if (this->m_Volume) {
				this->m_Unk7 = 0;
				this->m_SampleID = 340;
				this->m_Unk0 = 0;
				this->m_Unk1 = 0;
				this->m_Unk2 = 2;
				this->m_Frequency = 6000;
				this->m_Unk8 = 0;
				this->m_MaxVolume = 100;
				this->m_LoopStartOff = VCGlobals::SampleManager.GetSampleLoopStartOffset(this->m_SampleID);
				this->m_LoopEndOff = VCGlobals::SampleManager.GetSampleLoopEndOffset(this->m_SampleID);
				this->m_Unk4 = 4.0;
				this->m_MaxRange = 80.0;
				this->m_Unk9 = 0;
				this->m_Unk6 = 3;
				this->m_Unk10 = 1;
				this->m_Unk12 = 0;
				this->AddSampleToRequestedQueue();
			}
			if (*(unsigned char *)((unsigned long)&VCGlobals::AudioManager + this->m_AudioEntity * 0x28 + 0x1F34)) {
				this->m_Unk7 = 1;
				this->m_SampleID = 139;
				this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
				this->m_Unk8 = 1;
				this->m_Unk9 = 1;
				this->m_Unk10 = 1;
				this->m_Unk12 = 1;
				this->AddSampleToRequestedQueue();
			}
		}
	}

	// process bridge
	if (CBridgeHack::pLiftPart && CStats::CommercialPassed) {
		this->m_Position = CBridgeHack::pLiftPart->GetPos();
		distance = this->GetDistanceSquared(this->m_Position);
		if (distance < 202500.0) {
			this->m_DistanceToCamera = distance > 0.0 ? sqrt(distance) : 0.0f;
			switch (CBridgeHack::State) {
			case 2: // moving down
			case 5: // moving up
				this->ProcessBridgeMotor();
			case 0: // inactive
			case 1: // fully opened
			case 4: // ready to move up
				this->ProcessBridgeWarning();
				break;
			default:
				this->ProcessBridgeOneShots();
			}
		}
	}
}

void cAudioManagerHack::ProcessBridgeWarning()
{
	if (this->m_DistanceToCamera < 450.0) {
		this->m_Volume = this->ComputeVolume(100, 450.0, this->m_DistanceToCamera);
		if (this->m_Volume) {
			this->m_Unk7 = 0;
			this->m_SampleID = BRIDGE_WARNING;
			this->m_Unk0 = 0;
			this->m_Unk1 = 0;
			this->m_Unk2 = 1;
			this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
			this->m_Unk8 = 0;
			this->m_MaxVolume = 100;
			this->m_LoopStartOff = VCGlobals::SampleManager.GetSampleLoopStartOffset(this->m_SampleID);
			this->m_LoopEndOff = VCGlobals::SampleManager.GetSampleLoopEndOffset(this->m_SampleID);
			this->m_Unk4 = 2.0;
			this->m_MaxRange = 450.0;
			this->m_Unk9 = 0;
			this->m_Unk6 = 8;
			this->m_Unk10 = 0;
			this->m_Unk12 = 0;
			this->AddSampleToRequestedQueue();
		}
	}
}

void cAudioManagerHack::ProcessBridgeMotor()
{
	if (this->m_DistanceToCamera < 400.0) {
		this->m_Volume = this->ComputeVolume(127, 400.0, this->m_DistanceToCamera);
		if (this->m_Volume) {
			this->m_Unk7 = 1;
			this->m_SampleID = BRIDGE_MOTOR;
			this->m_Unk0 = 0;
			this->m_Unk1 = 0;
			this->m_Unk2 = 1;
			this->m_Frequency = 5500;
			this->m_Unk8 = 0;
			this->m_MaxVolume = 127;
			this->m_LoopStartOff = VCGlobals::SampleManager.GetSampleLoopStartOffset(this->m_SampleID);
			this->m_LoopEndOff = VCGlobals::SampleManager.GetSampleLoopEndOffset(this->m_SampleID);
			this->m_Unk4 = 2.0;
			this->m_MaxRange = 400.0;
			this->m_Unk9 = 0;
			this->m_Unk6 = 3;
			this->m_Unk10 = 0;
			this->AddSampleToRequestedQueue();
		}
	}
}

void cAudioManagerHack::ProcessBridgeOneShots()
{
	if ((CBridgeHack::State == 1 && CBridgeHack::OldState == 5) ||
		(CBridgeHack::State == 3 && CBridgeHack::OldState == 2) ||
		(CBridgeHack::State == 5 && CBridgeHack::OldState == 4) ||
		(CBridgeHack::State == 2 && CBridgeHack::OldState == 1)) {
		if (this->m_DistanceToCamera < 400.0) {
			this->m_Volume = this->ComputeVolume(127, 400.0, this->m_DistanceToCamera);
			if (this->m_Volume) {
				this->m_Unk7 = 2;
				this->m_SampleID = BRIDGE_ONE_SHOT;
				this->m_Unk0 = 0;
				this->m_Unk1 = 0;
				this->m_Unk2 = 1;
				this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
				this->m_Unk8 = 1;
				this->m_MaxVolume = 127;
				this->m_LoopStartOff = 0;
				this->m_LoopEndOff = -1;
				this->m_Unk4 = 2.0;
				this->m_MaxRange = 400.0;
				this->m_Unk9 = 1;
				this->m_Unk10 = 0;
				this->m_Unk12 = 0;
				this->AddSampleToRequestedQueue();
			}
		}
	}
}

void cAudioManagerHack::ProcessCinemaScriptObject(unsigned int id)
{
	float maxDistance = 0.0, distance;
	switch (id) {
	case 62:
	case 91:
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_62;
		this->m_Unk0 = 0;
		maxDistance = 400.0;
		this->m_MaxRange = 20.0;
		break;
	case 64:
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_64;
		this->m_Unk0 = 0;
		maxDistance = 400.0;
		this->m_MaxRange = 20.0;
		break;
	case 66:
		this->m_SampleID = LOOPING_SCRIPT_OBJECT_66;
		this->m_Unk0 = 0;
		maxDistance = 400.0;
		this->m_MaxRange = 20.0;
		break;
	}
	distance = this->GetDistanceSquared(this->m_Position);
	if (distance < maxDistance) {
		this->m_DistanceToCamera = (distance > 0 ? sqrt(distance) : 0.0f);
		if (id != 90 && id != 91) {
			this->m_Volume = this->ComputeVolume(127, this->m_MaxRange, this->m_DistanceToCamera);
			if (this->m_Volume) {
				this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
				this->m_Unk7 = 0;
				this->m_Unk1 = 0;
				this->m_Unk8 = 0;
				this->m_Unk9 = 0;
				this->m_Unk2 = 3;
				this->m_Unk4 = 2.0;
				this->m_MaxVolume = 127;
				this->m_LoopStartOff = VCGlobals::SampleManager.GetSampleLoopStartOffset(this->m_SampleID);
				this->m_LoopEndOff = VCGlobals::SampleManager.GetSampleLoopEndOffset(this->m_SampleID);
				this->m_Unk10 = 1;
				this->m_Unk12 = 0;
				this->AddSampleToRequestedQueue();
			}
		}
		if (CTimer::m_snTimeInMilliseconds > scriptObjectCinemaTime) {
			this->m_Volume = this->ComputeVolume(90, this->m_MaxRange, this->m_DistanceToCamera);
			if (this->m_Volume) {
				int rand = *(unsigned int *)((unsigned long)this + 0x5540);
				rand &= 1;
				this->m_SampleID = rand + LOOPING_SCRIPT_OBJECT_A;
				this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
				this->m_Frequency += this->RandomDisplacement(this->m_Frequency >> 4);
				this->m_Unk7 = rand + 1;
				this->m_Unk1 = 0;
				this->m_Unk8 = 1;
				this->m_Unk9 = 1;
				this->m_Unk2 = 6;
				this->m_Unk4 = 0;
				this->m_LoopStartOff = 0;
				this->m_LoopEndOff = -1;
				this->m_Unk10 = 1;
				this->m_Unk12 = 0;
				this->AddSampleToRequestedQueue();
				scriptObjectCinemaTime = CTimer::m_snTimeInMilliseconds + 2000 + *(unsigned int *)((unsigned long)this + 0x5548) % 6000;
			}
		}
	}
}

void cAudioManagerHack::ProcessLaunderetteScriptObject(unsigned int)
{
	float maxDistance, distance;
	maxDistance = 900.0;
	this->m_MaxRange = 30.0;
	distance = this->GetDistanceSquared(this->m_Position);
	if (distance < maxDistance) {
		this->m_DistanceToCamera = (distance > 0 ? sqrt(distance) : 0.0f);
		this->m_Volume = this->ComputeVolume(45, this->m_MaxRange, this->m_DistanceToCamera);
		if (this->m_Volume) {
			this->m_SampleID = LOOPING_SCRIPT_OBJECT_41A;
			this->m_Unk0 = 0;
			this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
			this->m_Unk7 = 0;
			this->m_Unk1 = 0;
			this->m_Unk8 = 0;
			this->m_Unk9 = 0;
			this->m_Unk2 = 5;
			this->m_Unk4 = 2.0;
			this->m_MaxVolume = 45;
			this->m_LoopStartOff = VCGlobals::SampleManager.GetSampleLoopStartOffset(this->m_SampleID);
			this->m_LoopEndOff = VCGlobals::SampleManager.GetSampleLoopEndOffset(this->m_SampleID);
			this->m_Unk10 = 1;
			this->m_Unk12 = 0;
			this->AddSampleToRequestedQueue();
		}
		this->m_Volume = this->ComputeVolume(110, this->m_MaxRange, this->m_DistanceToCamera);
		if (this->m_Volume) {
			this->m_SampleID = LOOPING_SCRIPT_OBJECT_41B;
			this->m_Unk0 = 0;
			this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
			this->m_Unk7 = 1;
			this->m_Unk1 = 0;
			this->m_Unk8 = 0;
			this->m_Unk9 = 0;
			this->m_Unk2 = 3;
			this->m_Unk4 = 2.0;
			this->m_MaxVolume = 110;
			this->m_LoopStartOff = VCGlobals::SampleManager.GetSampleLoopStartOffset(this->m_SampleID);
			this->m_LoopEndOff = VCGlobals::SampleManager.GetSampleLoopEndOffset(this->m_SampleID);
			this->m_Unk10 = 1;
			this->m_Unk12 = 0;
			this->AddSampleToRequestedQueue();
		}
	}
}

void cAudioManagerHack::ProcessSawMillScriptObject(unsigned int)
{
	float maxDistance, distance;
	maxDistance = 900.0;
	this->m_MaxRange = 30.0;
	distance = this->GetDistanceSquared(this->m_Position);
	if (distance < maxDistance) {
		this->m_DistanceToCamera = (distance > 0 ? sqrt(distance) : 0.0f);
		this->m_Volume = this->ComputeVolume(30, this->m_MaxRange, this->m_DistanceToCamera);
		if (this->m_Volume) {
			this->m_SampleID = LOOPING_SCRIPT_OBJECT_37A;
			this->m_Unk0 = 0;
			this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
			this->m_Unk7 = 0;
			this->m_Unk1 = 0;
			this->m_Unk8 = 0;
			this->m_Unk9 = 0;
			this->m_Unk2 = 5;
			this->m_Unk4 = 2.0;
			this->m_MaxVolume = 30;
			this->m_LoopStartOff = VCGlobals::SampleManager.GetSampleLoopStartOffset(this->m_SampleID);
			this->m_LoopEndOff = VCGlobals::SampleManager.GetSampleLoopEndOffset(this->m_SampleID);
			this->m_Unk10 = 1;
			this->m_Unk12 = 0;
			this->AddSampleToRequestedQueue();
		}
		if (CTimer::m_snTimeInMilliseconds > scriptObjectSawmillTime) {
			this->m_Volume = this->ComputeVolume(70, this->m_MaxRange, this->m_DistanceToCamera);
			if (this->m_Volume) {
				this->m_SampleID = LOOPING_SCRIPT_OBJECT_37B;
				this->m_Unk0 = 0;
				this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
				this->m_Unk7 = 1;
				this->m_Unk1 = 0;
				this->m_Unk8 = 1;
				this->m_Unk9 = 1;
				this->m_Unk2 = 3;
				this->m_Unk4 = 2.0;
				this->m_LoopStartOff = 0;
				this->m_LoopEndOff = -1;
				this->m_Unk10 = 1;
				this->m_Unk12 = 0;
				this->AddSampleToRequestedQueue();
				scriptObjectSawmillTime = CTimer::m_snTimeInMilliseconds + 2000 + *(unsigned int *)((unsigned long)this + 0x5548) % 4000;
			}
		}
	}
}

void cAudioManagerHack::ProcessAirportScriptObject(unsigned int)
{
	if (CTimer::m_snTimeInMilliseconds > scriptObjectAirportTime) {
		float maxDistance, distance;
		maxDistance = 6400.0;
		this->m_MaxRange = 80.0;
		distance = this->GetDistanceSquared(this->m_Position);
		if (distance < maxDistance) {
			this->m_DistanceToCamera = (distance > 0 ? sqrt(distance) : 0.0f);
			this->m_Volume = this->ComputeVolume(110, this->m_MaxRange, this->m_DistanceToCamera);
			if (this->m_Volume) {
				int rand = *(unsigned int *)((unsigned long)this + 0x5540);
				rand &= 3;
				this->m_SampleID = rand + LOOPING_SCRIPT_OBJECT_51A;
				this->m_Unk0 = 0;
				this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
				this->m_Unk7 = scriptObjectAirportCounter++;
				this->m_Unk1 = 0;
				this->m_Unk8 = 1;
				this->m_Unk9 = 1;
				this->m_Unk2 = 3;
				this->m_Unk4 = 2.0;
				this->m_MaxVolume = 110;
				this->m_LoopStartOff = 0;
				this->m_LoopEndOff = -1;
				this->m_Unk10 = 1;
				this->m_Unk12 = 0;
				this->AddSampleToRequestedQueue();
				scriptObjectAirportTime = CTimer::m_snTimeInMilliseconds + 10000 + *(unsigned int *)((unsigned long)this + 0x5548) % 20000;
			}
		}
	}
}

void cAudioManagerHack::ProcessHomeScriptObject(unsigned int)
{
	if (CTimer::m_snTimeInMilliseconds > scriptObjectHomeTime) {
		float maxDistance, distance;
		maxDistance = 6400.0;
		this->m_MaxRange = 80.0;
		distance = this->GetDistanceSquared(this->m_Position);
		if (distance < maxDistance) {
			unsigned char randomVolume = 40 + *(unsigned int *)((unsigned long)this + 0x553C) % 30;
			this->m_DistanceToCamera = (distance > 0 ? sqrt(distance) : 0.0f);
			this->m_Volume = this->ComputeVolume(randomVolume, this->m_MaxRange, this->m_DistanceToCamera);
			if (this->m_Volume) {
				this->m_SampleID = LOOPING_SCRIPT_OBJECT_59A + *(unsigned int *)((unsigned long)this + 0x553C) % 5;
				this->m_Unk0 = 0;
				this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
				this->m_Unk7 = scriptObjectHomeCounter++;
				this->m_Unk1 = 0;
				this->m_Unk8 = 1;
				this->m_Unk9 = 1;
				this->m_Unk2 = 3;
				this->m_Unk4 = 0;
				this->m_MaxVolume = randomVolume;
				this->m_LoopStartOff = 0;
				this->m_LoopEndOff = -1;
				this->m_Unk10 = 1;
				this->m_Unk12 = 1;
				this->AddSampleToRequestedQueue();
				scriptObjectHomeTime = CTimer::m_snTimeInMilliseconds + 1000 + *(unsigned int *)((unsigned long)this + 0x5548) % 4000;
			}
		}
	}
}

void cAudioManagerHack::ProcessPoliceCellBeatingScriptObject(unsigned int)
{
	if (CTimer::m_snTimeInMilliseconds > scriptObjectCellBeatingTime) {
		float maxDistance, distance;
		maxDistance = 6400.0;
		this->m_MaxRange = 80.0;
		distance = this->GetDistanceSquared(this->m_Position);
		if (distance < maxDistance) {
			unsigned char randomVolume = 55 + *(unsigned int *)((unsigned long)this + 0x553C) % 50;
			this->m_DistanceToCamera = (distance > 0 ? sqrt(distance) : 0.0f);
			this->m_Volume = this->ComputeVolume(randomVolume, this->m_MaxRange, this->m_DistanceToCamera);
			if (this->m_Volume) {
				if (*(unsigned int *)((unsigned long)this + 0x5554) & 1) {
					this->m_SampleID = LOOPING_SCRIPT_OBJECT_77A + (*(unsigned int *)((unsigned long)this + 0x5548) & 1);
				} else {
					this->m_SampleID = LOOPING_SCRIPT_OBJECT_77B + (*(unsigned int *)((unsigned long)this + 0x5540) & 3);
				}
				this->m_Unk0 = 0;
				this->m_Frequency = VCGlobals::SampleManager.GetSampleBaseFrequency(this->m_SampleID);
				this->m_Frequency += this->RandomDisplacement(this->m_Frequency >> 4);
				this->m_Unk7 = scriptObjectCellBeatingCounter++;
				this->m_Unk1 = 0;
				this->m_Unk8 = 1;
				this->m_Unk9 = 1;
				this->m_Unk2 = 3;
				this->m_Unk4 = 0;
				this->m_MaxVolume = randomVolume;
				this->m_LoopStartOff = 0;
				this->m_LoopEndOff = -1;
				this->m_Unk10 = 1;
				this->m_Unk12 = 0;
				this->AddSampleToRequestedQueue();
				cPedParams parameters = { 1, {}, distance, 0 };
				this->SetupPedComments(parameters, 0xC8);
				scriptObjectCellBeatingTime = CTimer::m_snTimeInMilliseconds + 500 + *(unsigned int *)((unsigned long)this + 0x5548) % 1500;
			}
		}
	}
}

void cAudioManagerHack::DisplayRadioStationNameHack(float fX, float fY, wchar_t *pText)
{
	CFont::PrintString(fX - 2.0f + (2.0f * VCGlobals::RsGlobal.currentWidth / 640.0f),
		fY - 2.0f + (2.0f * VCGlobals::RsGlobal.currentHeight / 448.0f), pText);
}

void cAudioManagerHack::InitialiseHack(void)
{
	VehicleSfx *vehicleSfx = reinterpret_cast<VehicleSfx *>(vcversion::AdjustOffset(0x006AD1A0));
	int filename = CFileMgr::OpenFile("vehicleSfx.dat", "r");
	if (filename) {
		char buffer[200];
		for (int i = 0; CFileMgr::ReadLine(filename, buffer, 200) && i < 107; i++) {
			VCGlobals::sscanf(buffer, "%d %d %d %d %d %d %d",
				&vehicleSfx[i].npcEngine, &vehicleSfx[i].playerEngine, &vehicleSfx[i].horn, &vehicleSfx[i].hornPitch, &vehicleSfx[i].siren, &vehicleSfx[i].sirenPitch, &vehicleSfx[i].door);
		}
		CFileMgr::CloseFile(filename);
	} else {
		for (int i = 0; i < 107; i++) {
			vehicleSfx[i] = presetVehicleSfx[i];
		}
	}
	PedSfxDelay *pedSfxDelay = reinterpret_cast<PedSfxDelay *>(vcversion::AdjustOffset(0x00693800));
	for (int i = 0; i < 56; i++) {
		pedSfxDelay[i] = presetPedSfxDelay[i];
	}
}

void __declspec(naked) cAudioManagerHack::ProcessVehicleSirenOrAlarmHack()
{
	__asm
	{
		cmp eax, 5Ah                   // test for fbicar
		jnz fbiranchtest
		mov dword ptr [esi+28h], 3EF1h // set fbicar alt siren pitch
		jmp fbiMatchEndJump
	fbiranchTest:
		cmp eax, 11h                   // test for fbiranch
		jnz noMatch
		mov dword ptr [esi+28h], 317Ch // set fbiranch alt siren pitch
		jmp fbiMatchEndJump
	noMatch:
		jmp fbiNoMatchEndJump
	}
}

unsigned int __thiscall cAudioManagerHack::GetPedCommentSfxHack(CPed *ped, unsigned short type)
{
	switch (type) {
	case 0xA0:
		return 3029;
	case 0xA1:
		return 3030;
	case 0xA2:
		return 3031;
	}
	switch (ped->modelIndex) {
	case 0:   // 0
		if (isPlayerSfxTommy) {
			return cAudioManager::GetPlayerTalkSfx(ped, type);
		} else {
			return this->GetPlayerTalkSfx(ped, type);
		}
	case 5:   // 5
		return this->GetMedicTalkSfx(ped, type);
	case 6:   // 6
		return this->GetFiremanTalkSfx(ped, type);
	case 7:   // 7
		return this->GetNormalMaleTalkSfx(ped, type);
	case 28:  // 8
		return this->GetAsianTaxiDriverTalkSfx(ped, type);
	case 73:  // 9
		return this->GetPimpTalkSfx(ped, type);
	case 83:  // 10
	case 84:  // 11
		return this->GetMafiaTalkSfx(ped, type);
	case 85:  // 12
	case 86:  // 13
		return this->GetTriadTalkSfx(ped, type);
	case 87:  // 14
	case 88:  // 15
		return this->GetDiabloTalkSfx(ped, type);
	case 89:  // 16
	case 90:  // 17
		return this->GetYakuzaTalkSfx(ped, type);
	case 91:  // 18
	case 92:  // 19
		return this->GetYardieTalkSfx(ped, type);
	case 93:  // 20
	case 94:  // 21
		return this->GetColombianTalkSfx(ped, type);
	case 95:  // 22
	case 96:  // 23
		return this->GetHoodTalkSfx(ped, type);
	case 30:  // 24
		return this->GetBlackCriminalTalkSfx(ped, type);
	case 48:  // 25
		return this->GetWhiteCriminalTalkSfx(ped, type);
	case 109: // 26
	case 110: // 27
	case 111: // 28
	case 112: // 29
		return this->GetSpecialCharacterTalkSfx(ped, type);
	case 97:  // 97
	case 98:  // 98
	case 99:  // 99
	case 100: // 100
	case 101: // 101
	case 103: // 103
	case 104: // 104
		return this->GetViceWhiteTalkSfx(ped, type);
	case 102: // 102
		return this->GetViceBlackTalkSfx(ped, type);
	}
	return 9942;
}

unsigned int cAudioManagerHack::GetPlayerTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x68:
		this->GetPhrase(store, ped->phrase, 663, 11);
		break;
	case 0x69:
		this->GetPhrase(store, ped->phrase, 653, 10);
		break;
	case 0x6A:
		this->GetPhrase(store, ped->phrase, 674, 6);
		break;
	default:
		return 9942;
	}
	return store;
}

unsigned int cAudioManagerHack::GetMedicTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x77:
		this->GetPhrase(store, ped->phrase, 920, 5);
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 925, 5);
		break;
	case 0x8C:
		this->GetPhrase(store, ped->phrase, 945, 12);
		break;
	case 0x8D:
		this->GetPhrase(store, ped->phrase, 936, 9);
		break;
	case 0x8F:
		this->GetPhrase(store, ped->phrase, 930, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store + 0x25 * (this->m_AudioEntity & 1);
}

unsigned int cAudioManagerHack::GetFiremanTalkSfx(CPed *ped, unsigned short type)
{
	return GetGenericMaleTalkSfx(ped, type);
}

unsigned int cAudioManagerHack::GetNormalMaleTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x77:
		this->GetPhrase(store, ped->phrase, 832, 7);
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 839, 7);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 815, 9);
		break;
	case 0x8F:
		this->GetPhrase(store, ped->phrase, 846, 5);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 778, 12);
		break;
	case 0x9A:
		this->GetPhrase(store, ped->phrase, 824, 8);
		break;
	case 0x9B:
		this->GetPhrase(store, ped->phrase, 851, 10);
		break;
	case 0x9C:
	case 0x9D:
		this->GetPhrase(store, ped->phrase, 790, 25);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetAsianTaxiDriverTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 2648, 7);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 2642, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetPimpTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 765, 7);
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 772, 4);
		break;
	case 0x8B:
		this->GetPhrase(store, ped->phrase, 756, 9);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 750, 6);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 728, 5);
		break;
	case 0x9B:
		this->GetPhrase(store, ped->phrase, 776, 2);
		break;
	case 0x9C:
	case 0x9D:
		this->GetPhrase(store, ped->phrase, 733, 17);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetMafiaTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x79:
		this->GetPhrase(store, ped->phrase, 2504, 2);
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 2502, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 2497, 5);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 2489, 5);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 2476, 6);
		break;
	case 0x9A:
		this->GetPhrase(store, ped->phrase, 2494, 3);
		break;
	case 0x9C:
	case 0x9D:
		this->GetPhrase(store, ped->phrase, 2482, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store + 0x1E * (this->m_AudioEntity & 1);
}

unsigned int cAudioManagerHack::GetTriadTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 2469, 3);
		break;
	case 0x79:
		this->GetPhrase(store, ped->phrase, 2474, 2);
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 2472, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 2464, 5);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 2457, 4);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 2442, 7);
		break;
	case 0x9A:
		this->GetPhrase(store, ped->phrase, 2461, 3);
		break;
	case 0x9C:
	case 0x9D:
		this->GetPhrase(store, ped->phrase, 2449, 8);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetDiabloTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 2990, 4);
		break;
	case 0x79:
		this->GetPhrase(store, ped->phrase, 2980, 2);
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 2978, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 2982, 4);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 2974, 4);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 2994, 5);
		break;
	case 0x9A:
		this->GetPhrase(store, ped->phrase, 2986, 4);
		break;
	case 0x9C:
	case 0x9D:
		this->GetPhrase(store, ped->phrase, 2969, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store + 0x1E * (this->m_AudioEntity & 1);
}

unsigned int cAudioManagerHack::GetYakuzaTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x79:
		this->GetPhrase(store, ped->phrase, 2588, 2);
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 2586, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 2581, 5);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 2577, 4);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 2566, 6);
		break;
	case 0x9C:
	case 0x9D:
		this->GetPhrase(store, ped->phrase, 2572, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store + 0x18 * (this->m_AudioEntity & 1);
}

unsigned int cAudioManagerHack::GetYardieTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		store = 1707;
		break;
	case 0x79:
		this->GetPhrase(store, ped->phrase, 1709, 2);
		break;
	case 0x7B:
		store = 1708;
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 1701, 6);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 1694, 5);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 1680, 6);
		break;
	case 0x9A:
		this->GetPhrase(store, ped->phrase, 1699, 2);
		break;
	case 0x9C:
	case 0x9D:
		this->GetPhrase(store, ped->phrase, 1686, 8);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store + 0x1F * (this->m_AudioEntity & 1);
}

unsigned int cAudioManagerHack::GetColombianTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x79:
		this->GetPhrase(store, ped->phrase, 2192, 2);
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 2190, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 2185, 5);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 2178, 5);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 2167, 6);
		break;
	case 0x9A:
		this->GetPhrase(store, ped->phrase, 2183, 2);
		break;
	case 0x9C:
	case 0x9D:
		this->GetPhrase(store, ped->phrase, 2173, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store + 0x1B * (this->m_AudioEntity & 1);
}

unsigned int cAudioManagerHack::GetHoodTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 1636, 5);
		break;
	case 0x79:
		this->GetPhrase(store, ped->phrase, 1643, 2);
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 1641, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 1630, 6);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 1623, 5);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 1610, 7);
		break;
	case 0x9A:
		this->GetPhrase(store, ped->phrase, 1628, 2);
		break;
	case 0x9C:
	case 0x9D:
		this->GetPhrase(store, ped->phrase, 1617, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store + 0x23 * (this->m_AudioEntity & 1);
}

unsigned int cAudioManagerHack::GetBlackCriminalTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 2325, 4);
		break;
	case 0x79:
		store = 2329;
		break;
	case 0x7A:
		this->GetPhrase(store, ped->phrase, 2330, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 2320, 5);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 2314, 6);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 2309, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetWhiteCriminalTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 2345, 3);
		break;
	case 0x79:
		store = 2348;
		break;
	case 0x7A:
		this->GetPhrase(store, ped->phrase, 2349, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 2341, 4);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 2336, 5);
		break;
	case 0x90:
	case 0x91:
	case 0x92:
		this->GetPhrase(store, ped->phrase, 2332, 4);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetSpecialCharacterTalkSfx(CPed *ped, unsigned short type)
{
	char *modelName = reinterpret_cast<char *>(CModelInfo::ms_modelInfoPtrs[ped->modelIndex] + 0x4);
	if (VCGlobals::strcmp(modelName, "eight") == 0 || VCGlobals::strcmp(modelName, "eight2") == 0) {
		return this->GetEightBallTalkSfx(ped, type);
	}
	if (VCGlobals::strcmp(modelName, "frankie") == 0) {
		return this->GetSalvatoreTalkSfx(ped, type);
	}
	if (VCGlobals::strcmp(modelName, "misty") == 0) {
		return this->GetMistyTalkSfx(ped, type);
	}
	if (VCGlobals::strcmp(modelName, "ojg") == 0 || VCGlobals::strcmp(modelName, "ojg_p") == 0) {
		return GetGenericMaleTalkSfx(ped, type);
	}
	if (VCGlobals::strcmp(modelName, "cat") == 0) {
		return GetGenericFemaleTalkSfx(ped, type);
	}
	if (VCGlobals::strcmp(modelName, "bomber") == 0) {
		return this->GetBomberTalkSfx(ped, type);
	}
	if (VCGlobals::strcmp(modelName, "s_guard") == 0) {
		return this->GetSecurityGuardTalkSfx(ped, type);
	}
	if (VCGlobals::strcmp(modelName, "chunky") == 0) {
		return this->GetChunkyTalkSfx(ped, type);
	}
	if (VCGlobals::strcmp(modelName, "asuka") == 0) {
		return GetGenericFemaleTalkSfx(ped, type);
	}
	if (VCGlobals::strcmp(modelName, "maria") == 0) {
		return GetGenericFemaleTalkSfx(ped, type);
	}
	return 9942;
}

unsigned int cAudioManagerHack::GetEightBallTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 881, 2);
		break;
	case 0x7C:
		this->GetPhrase(store, ped->phrase, 883, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 875, 6);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 868, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetSalvatoreTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 894, 4);
		break;
	case 0x7C:
		this->GetPhrase(store, ped->phrase, 898, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 888, 6);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 885, 3);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetMistyTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 909, 5);
		break;
	case 0x7C:
		this->GetPhrase(store, ped->phrase, 918, 2);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 905, 4);
		break;
	case 0x8E:
		this->GetPhrase(store, ped->phrase, 900, 5);
		break;
	//case:
	//	this->GetPhrase(store, ped->phrase, 914, 4);
	//	break;
	default:
		return GetGenericFemaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetBomberTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x6C:
		this->GetPhrase(store, ped->phrase, 861, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetSecurityGuardTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x76:
		this->GetPhrase(store, ped->phrase, 2676, 2);
		break;
	case 0x77:
		store = 2678;
		break;
	case 0x7B:
		this->GetPhrase(store, ped->phrase, 2668, 6);
		break;
	case 0x8A:
		this->GetPhrase(store, ped->phrase, 2674, 2);
		break;
	case 0x8F:
		this->GetPhrase(store, ped->phrase, 2668, 12);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetChunkyTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x8F:
		this->GetPhrase(store, ped->phrase, 723, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store;
}

unsigned int cAudioManagerHack::GetViceWhiteTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x6E:
		this->GetPhrase(store, ped->phrase, 1874, 3);
		break;
	case 0x6F:
		store = 1877;
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store + 4 * (this->m_AudioEntity % 5) + 3000; // vc talk sfx moved by 3000
}

unsigned int cAudioManagerHack::GetViceBlackTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x6E:
		this->GetPhrase(store, ped->phrase, 1894, 3);
		break;
	case 0x6F:
		store = 1897;
		break;
	default:
		return GetGenericMaleTalkSfx(ped, type);
	}
	return store + 3000; // vc talk sfx moved by 3000
}

unsigned int cAudioManagerHack::GetGenericMaleTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x6B:
	case 0x8B:
		this->GetPhrase(store, ped->phrase, 2857, 15);
		break;
	case 0x67:
		this->GetPhrase(store, ped->phrase, 2841, 8);
		break;
	case 0x6C:
		this->GetPhrase(store, ped->phrase, 2849, 8);
		break;
	case 0x78:
		this->GetPhrase(store, ped->phrase, 2872, 6);
		break;
	default:
		return 9942;
	}
	return store;
}

unsigned int cAudioManagerHack::GetGenericFemaleTalkSfx(CPed *ped, unsigned short type)
{
	unsigned int store;
	switch (type) {
	case 0x6B:
	case 0x8B:
		this->GetPhrase(store, ped->phrase, 2290, 11);
		break;
	case 0x67:
		this->GetPhrase(store, ped->phrase, 2271, 10);
		break;
	case 0x6C:
		this->GetPhrase(store, ped->phrase, 2281, 9);
		break;
	case 0x78:
		this->GetPhrase(store, ped->phrase, 2301, 8);
		break;
	default:
		return 9942;
	}
	return store;
}
