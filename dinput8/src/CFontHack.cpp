#include "CFontHack.h"
#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"

#include <wchar.h>

using namespace VCGlobals;

CSprite2d *PagerFont = reinterpret_cast<CSprite2d *>(0x00A10748);

bool CFontHack::initialise()
{
	return true;
}

void CFontHack::PrintPagerString(float posX, float posY, float scaleX, float scaleY, wchar_t *text)
{
	int len = wcslen(text);

	for (int i = 0; i < len; i++)
	{
		if (text[i] >= ' ' && text[i] <= 'z')
		{
			int row = (text[i] - 32) / 16;
			int col = (text[i] - 32) % 16;

			CRect drawRect;
			float cropX1 = col * 0.0625f;
			float cropY1 = row * 0.0625f;
			float cropX2 = cropX1 + 0.06f;
			float cropY2 = cropY1 + 0.0625f;

			if ((float)Globals.currentWidth / (float)Globals.currentHeight < 1.5f)
			{
				float charWidth = Globals.currentWidth * (16.0f / 640.0f);
				float charHeight = Globals.currentHeight * (16.0f / 448.0f);

				drawRect.left = posX + (charWidth * i);
				drawRect.right = drawRect.left + (charWidth * scaleX * 2);
				drawRect.top = posY;
				drawRect.bottom = drawRect.top + (charHeight * scaleY);
			}
			else
			{
				float charWidth = Globals.currentWidth * (32.0f / 1920.0f);
				float charHeight = Globals.currentHeight * (32.0f / 1080.0f);

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
