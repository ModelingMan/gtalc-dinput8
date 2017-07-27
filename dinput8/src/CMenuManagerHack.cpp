#include "CMenuManagerHack.h"
#include "SilentCall.h"

struct MenuPage
{
	char          pageText[8];
	unsigned char parentMenu;
	unsigned char unk;
	struct MenuItem
	{
		unsigned short action;
		char           itemText[8];
		unsigned char  saveSlot;
		unsigned char  targetMenu;
		unsigned short posX;
		unsigned short posY;
		unsigned short align;
	} menuItem[12];
};

static_assert(sizeof(MenuPage) == 0xE2, "Size of MenuPage is not 0xE2 bytes.");

static const MenuPage displayPage =
{
	"FEH_DIS", 27, 2, // DISPLAY
	{
		{ 12, "FED_BRI", 0,  4,  40,  78, 1 }, // Brightness
		{ 51, "FEM_LOD", 0,  4,  40, 103, 1 }, // DRAW DISTANCE
		{  8, "FEM_FRM", 0,  4,  40, 128, 1 }, // FRAME LIMITER
		{  9, "FED_TRA", 0,  4,  40, 153, 1 }, // Trails
		{ 10, "FED_SUB", 0,  4,  40, 178, 1 }, // Subtitles
		{ 11, "FED_WIS", 0,  4,  40, 202, 1 }, // Wide Screen
		{ 31, "MAP_LEG", 0,  4,  40, 228, 1 }, // Map Legend
		{ 32, "FED_RDR", 0,  4,  40, 253, 1 }, // RADAR MODE
		{ 33, "FED_HUD", 0,  4,  40, 278, 1 }, // HUD MODE
		{ 43, "FED_RES", 0,  4,  40, 303, 1 }, // SCREEN RESOLUTION
		{ 47, "FET_DEF", 0,  4, 320, 328, 3 }, // Restore Defaults
		{ 34, "FEDS_TB", 0, 33, 320, 353, 3 }  // Back
	}
};

bool CMenuManagerHack::initialise()
{
	// add trails option to menu
	Patch<MenuPage>(0x006D8B70 + sizeof(MenuPage) * 4, displayPage);

	// trails in settings
	Patch<void *>(0x004902D2, &CMBlur::BlurOn);
	Patch<void *>(0x0048FF97, &CMBlur::BlurOn);

	return true;
}
