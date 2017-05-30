#include "CFontHack.h"
#include <Windows.h>
#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"
#include "SilentCall.h"

using namespace VCGlobals;

static CSprite2d *PagerFont = reinterpret_cast<CSprite2d *>(vcversion::AdjustOffset(0x00A10748));

static unsigned long SubtitlesShadowFixEndJump = vcversion::AdjustOffset(0x00551701);

static void SubtitlesShadowFix();

bool CFontHack::initialise()
{
	// subtitles shadow fix (SilentPatch)
	InjectHook(0x005516FB, &SubtitlesShadowFix, PATCH_JUMP);
	Patch<unsigned char>(0x005517C4, 0xD9);
	Patch<unsigned char>(0x005517C7, 0x28 - 0x18);
	Patch<unsigned char>(0x005517DF, 0xD9);
	Patch<unsigned char>(0x005517E2, 0x34 - 0x14);
	Patch<unsigned char>(0x00551832, 0xD9);
	Patch<unsigned char>(0x00551835, 0x24 - 0x18);
	Patch<unsigned char>(0x00551848, 0xD9);
	Patch<unsigned char>(0x0055184B, 0x34 - 0x14);

	// font styles
	if (!GetPrivateProfileInt("Misc", "UseVCFontStyles", 0, "./gta-lc.ini")) {
		Patch<unsigned char>(0x0042F339, 0); // garage message
		Patch<unsigned char>(0x0055AE9A, 0); // message
		Patch<unsigned char>(0x0055B593, 0); // help message
		Patch<unsigned char>(0x005FA178, 2); // radio station name
	}

	// font colors
	if (!GetPrivateProfileInt("Misc", "UseVCFontColors", 0, "./gta-lc.ini")) {
		Patch<unsigned char>(0x0042A378, 0x96); // rampage timer
		Patch<unsigned char>(0x0042A373, 0x64);
		Patch<unsigned char>(0x0042A36E, 0xFF);
		Patch<unsigned char>(0x0042A47E, 0xFF); // rampage counter
		Patch<unsigned char>(0x0042A47C, 0x80);
		Patch<unsigned char>(0x0042A47A, 0x80);
		Patch<unsigned char>(0x0042F351, 0x59); // garage message
		Patch<unsigned char>(0x0042F34F, 0x73);
		Patch<unsigned char>(0x0042F34A, 0x96);
		Patch<unsigned char>(0x00550564, 0x71); // r
		Patch<unsigned char>(0x00550568, 0x2B);
		Patch<unsigned char>(0x0055056C, 0x49);
		Patch<unsigned char>(0x00550319, 0x71);
		Patch<unsigned char>(0x00550320, 0x2B);
		Patch<unsigned char>(0x00550327, 0x49);
		Patch<unsigned char>(0x00550574, 0x55); // g
		Patch<unsigned char>(0x00550578, 0xA0);
		Patch<unsigned char>(0x0055057C, 0x6A);
		Patch<unsigned char>(0x0055033A, 0x55);
		Patch<unsigned char>(0x00550341, 0xA0);
		Patch<unsigned char>(0x00550348, 0x6A);
		Patch<unsigned char>(0x00550584, 0x80); // b
		Patch<unsigned char>(0x00550588, 0xA7);
		Patch<unsigned char>(0x0055058C, 0xF3);
		Patch<unsigned char>(0x0055035B, 0x80);
		Patch<unsigned char>(0x00550362, 0xA7);
		Patch<unsigned char>(0x00550369, 0xF3);
		Patch<unsigned char>(0x005505B1, 0xD2); // y
		Patch<unsigned char>(0x005505B5, 0xC4);
		Patch<unsigned char>(0x005505B9, 0x6A);
		Patch<unsigned char>(0x005503BE, 0xD2);
		Patch<unsigned char>(0x005503C5, 0xC4);
		Patch<unsigned char>(0x005503CC, 0x6A);
		Patch<unsigned char>(0x0055A186, 0xBA); // timer number
		Patch<unsigned char>(0x0055A181, 0x65);
		Patch<unsigned char>(0x0055A17C, 0x32);
		Patch<unsigned char>(0x0055A248, 0xBA); // timer text
		Patch<unsigned char>(0x0055A243, 0x65);
		Patch<unsigned char>(0x0055A23E, 0x32);
		Patch<unsigned char>(0x0055A40E, 0);    // counter number
		Patch<unsigned char>(0x0055A409, 0x6A);
		Patch<unsigned char>(0x0055A404, 0xA4);
		Patch<unsigned char>(0x0055A4CD, 0);    // counter bar shadow
		Patch<unsigned char>(0x0055A5C1, 0);    // counter unfilled bar
		Patch<unsigned char>(0x0055A5BF, 0x6A);
		Patch<unsigned char>(0x0055A5BA, 0xA4);
		Patch<unsigned char>(0x0055A5B5, 0x50);
		Patch<unsigned char>(0x0055A663, 0);    // counter filled bar
		Patch<unsigned char>(0x0055A65E, 0x6A);
		Patch<unsigned char>(0x0055A659, 0xA4);
		Patch<unsigned char>(0x0055A7A3, 0);    // counter text
		Patch<unsigned char>(0x0055A79E, 0x6A);
		Patch<unsigned char>(0x0055A799, 0xA4);
	}

	return true;
}

void CFontHack::PrintPagerString(float posX, float posY, float scaleX, float scaleY, wchar_t *text)
{
	int len = wcslen(text);

	for (int i = 0; i < len; i++) {
		if (text[i] >= ' ' && text[i] <= 'z') {
			int row = (text[i] - 32) / 16;
			int col = (text[i] - 32) % 16;

			CRect drawRect;
			float cropX1 = col * 0.0625f;
			float cropY1 = row * 0.0625f;
			float cropX2 = cropX1 + 0.06f;
			float cropY2 = cropY1 + 0.0625f;

			if (static_cast<float>(RsGlobal.currentWidth) / static_cast<float>(RsGlobal.currentHeight) < 1.5f) {
				float charWidth = RsGlobal.currentWidth * (16.0f / 640.0f);
				float charHeight = RsGlobal.currentHeight * (16.0f / 448.0f);

				drawRect.left = posX + (charWidth * i);
				drawRect.right = drawRect.left + (charWidth * scaleX * 2);
				drawRect.top = posY;
				drawRect.bottom = drawRect.top + (charHeight * scaleY);
			} else {
				float charWidth = RsGlobal.currentWidth * (32.0f / 1920.0f);
				float charHeight = RsGlobal.currentHeight * (32.0f / 1080.0f);

				drawRect.left = posX + (charWidth * i);
				drawRect.right = drawRect.left + charWidth;
				drawRect.top = posY;
				drawRect.bottom = drawRect.top + charHeight;

				cropX2 = cropX1 + 0.04f;
			}

			PagerFont->Draw(drawRect, CRGBA(0, 0, 0, 255), cropX1, cropY1, cropX2, cropY1, cropX1, cropY2, cropX2, cropY2);
		}
	}
}

// subtitles shadow fix (SilentPatch)
void __stdcall Recalculate(float &fX, float &fY, int nShadow)
{
	fX = nShadow * RsGlobal.currentWidth / 640.0f;
	fY = nShadow * RsGlobal.currentHeight / 448.0f;
}

void __declspec(naked) SubtitlesShadowFix()
{
	__asm
	{
		mov [esp], eax
		fild word ptr [esp]
		push eax
		lea eax, [esp+8]
		push eax
		lea eax, [esp+10h]
		push eax
		call Recalculate
		jmp SubtitlesShadowFixEndJump
	}
}
