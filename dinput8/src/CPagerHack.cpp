#include "CPagerHack.h"
#include <wchar.h>
#include "CFontHack.h"
#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"
#include "SilentCall.h"

using namespace VCGlobals;

CSprite2d *PagerSprite = reinterpret_cast<CSprite2d *>(0x00A1074C);

wchar_t PagerMessage[8];
float PagerScrollLeft = 0.0f;
int	PagerDrawState = 0;
int	PagerSoundState = 0;

bool CPagerHack::initialise()
{
	InjectHook(0x004A6501, &Draw, PATCH_JUMP);
	InjectHook(0x00584C26, &SetMessage);

	return true;
}

void CPagerHack::AddMessage(wchar_t *text, unsigned short delay, unsigned short unk1, unsigned short unk2)
{
	bool bDone = false;
	unsigned short iTextLength = static_cast<unsigned short>(wcslen(text));

	for (int iPagerIndex = 0; !bDone && iPagerIndex < 8; iPagerIndex++) {
		if (Pagers[iPagerIndex].Text == 0) {
			Pagers[iPagerIndex].Text = text;
			Pagers[iPagerIndex].Delay = delay;
			Pagers[iPagerIndex].Unk1 = unk1;
			Pagers[iPagerIndex].Unk3 = unk2;
			Pagers[iPagerIndex].Scroll = -((unsigned short)MaxLength + 10);
			Pagers[iPagerIndex].Unk2 = delay + CTimer::m_snTimeInMilliseconds;
			Pagers[iPagerIndex].TextLength = iTextLength;
			Pagers[iPagerIndex].Unk5 = 0x0FFFFFFFF;
			Pagers[iPagerIndex].Unk6 = 0x0FFFFFFFF;
			Pagers[iPagerIndex].Unk7 = 0x0FFFFFFFF;
			Pagers[iPagerIndex].Unk8 = 0x0FFFFFFFF;
			Pagers[iPagerIndex].Unk9 = 0x0FFFFFFFF;
			Pagers[iPagerIndex].Unk10 = 0x0FFFFFFFF;
			bDone = true;
		} else {
			if (Pagers[iPagerIndex].Delay < delay) {
				if (iPagerIndex < 7) {
					for (int i = 7; i > iPagerIndex; i--) {
						Pagers[i].Text = Pagers[i - 1].Text;
						Pagers[i].Delay = Pagers[i - 1].Delay;
						Pagers[i].Scroll = Pagers[i - 1].Scroll;
						Pagers[i].TextLength = Pagers[i - 1].TextLength;
						Pagers[i].Unk1 = Pagers[i - 1].Unk1;
						Pagers[i].Unk2 = Pagers[i - 1].Unk2;
						Pagers[i].Unk3 = Pagers[i - 1].Unk3;
						Pagers[i].Unk5 = Pagers[i - 1].Unk5;
						Pagers[i].Unk6 = Pagers[i - 1].Unk6;
						Pagers[i].Unk7 = Pagers[i - 1].Unk7;
						Pagers[i].Unk8 = Pagers[i - 1].Unk8;
						Pagers[i].Unk9 = Pagers[i - 1].Unk9;
						Pagers[i].Unk10 = Pagers[i - 1].Unk10;
					}
				} else {
					Pagers[iPagerIndex].Text = text;
					Pagers[iPagerIndex].Delay = delay;
					Pagers[iPagerIndex].Unk1 = unk1;
					Pagers[iPagerIndex].Unk3 = unk2;
					Pagers[iPagerIndex].Scroll = -((unsigned short)MaxLength + 10);
					Pagers[iPagerIndex].Unk2 = delay + CTimer::m_snTimeInMilliseconds;
					Pagers[iPagerIndex].TextLength = iTextLength;
					Pagers[iPagerIndex].Unk5 = 0xFFFFFFFF;
					Pagers[iPagerIndex].Unk6 = 0xFFFFFFFF;
					Pagers[iPagerIndex].Unk7 = 0xFFFFFFFF;
					Pagers[iPagerIndex].Unk8 = 0xFFFFFFFF;
					Pagers[iPagerIndex].Unk9 = 0xFFFFFFFF;
					Pagers[iPagerIndex].Unk10 = 0xFFFFFFFF;
					bDone = true;
				}
			}

			if (bDone && iPagerIndex == 0) {
				CMessages::AddToPreviousBriefArray(Pagers[iPagerIndex].Text,
					Pagers[iPagerIndex].Unk5,
					Pagers[iPagerIndex].Unk6,
					Pagers[iPagerIndex].Unk7,
					Pagers[iPagerIndex].Unk8,
					Pagers[iPagerIndex].Unk9,
					Pagers[iPagerIndex].Unk10, NULL);
			}
		}
	}
}

void CPagerHack::Draw()
{
	if (PagerMessage[0] == 0 && PagerDrawState == 1) {
		PagerSoundState = 0;
		PagerDrawState = 2;
	}

	if (PagerMessage[0] != 0 || PagerDrawState == 2) {
		switch (PagerDrawState) {
		case 0:
			PagerDrawState = 1;
			PagerScrollLeft = 150.0f;
			break;

		case 1:
			if (PagerScrollLeft > 0.0f)
				PagerScrollLeft -= (PagerScrollLeft * 0.1f == 10.0f ? 10.0f : PagerScrollLeft * 0.1f);

			if (PagerSoundState == 0) {
				DMAudio.PlayFrontEndSound(96, 0);
				PagerSoundState = 1;
			}
			break;

		case 2:
			if (PagerScrollLeft * 0.1f < 2.0f)
				PagerScrollLeft += 2.0f;

			if (PagerScrollLeft < 150.0f)
				PagerScrollLeft += PagerScrollLeft * 0.1f;
			else
				PagerDrawState = 0;
			break;
		}

		const float width = static_cast<float>(RsGlobal.currentWidth);
		const float height = static_cast<float>(RsGlobal.currentHeight);

		if (width / height < 1.5f ) {
			PagerSprite->Draw(
				CRect(width * (26.0f / 640.0f) - PagerScrollLeft,
				height * (107.0f / 448.0f),
				width * (186.0f / 640.0f) - PagerScrollLeft,
				height * (27.0f / 448.0f)),
				CRGBA(255, 255, 255, 255), 0.015f, 0.0f, 1.0f, 0.0f, 0.015f, 0.995f, 1.0f, 0.995f);

			CFontHack::PrintPagerString(width * (52.0f / 640.0f) - PagerScrollLeft, height * (54.0f / 448.0f), 0.84f, 1.0f, PagerMessage);
		} else {
			CRect rect;
			rect.left = width * (26.0f / 1920.0f) - PagerScrollLeft;
			rect.right = width * (346.0f / 1920.0f) - PagerScrollLeft;
			rect.top = height * (26.0f / 1080.0f);
			rect.bottom = rect.top + ((rect.right - rect.left) / 2.0f);

			PagerSprite->Draw(rect, CRGBA(255, 255, 255, 255));
			CFontHack::PrintPagerString(width * (78.0f / 1920.0f) - PagerScrollLeft, height * (80.0f / 1080.0f), 0.84f, 1.0f, PagerMessage);
		}
	}
}

void CPagerHack::SetMessage(wchar_t *text)
{
	if (text == NULL)
		return;

	int i;
	for (i = 0; i < 7 && text[i] != 0; i++)
		PagerMessage[i] = text[i];

	PagerMessage[i] = 0;
}
