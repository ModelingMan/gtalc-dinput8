#include "CFontHack.h"
#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"
#include "SilentCall.h"

#include <wchar.h>

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
	_asm
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
