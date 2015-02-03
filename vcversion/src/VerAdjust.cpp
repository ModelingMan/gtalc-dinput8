/*******************************************************************************
	vcversion - 

	Ported from Delphi source code courtesy of Artem Khassanov (Hammer83)
	Original file: uVerAdjust.pas
	http://www.artemkh.com/gtalc.php
*******************************************************************************/

unsigned long AdjustOffsetUS11(unsigned long Offset)
{
	if (Offset < 0x00489D0C)
		return Offset;
	else if (Offset < 0x00489D10)
		return Offset + 0x04;
	else if (Offset < 0x00489D82)
		return Offset + 0x0D;
	else if (Offset < 0x00489E0D)
		return Offset + 0x0E;
	else if (Offset < 0x00498FF3)
		return Offset + 0x10;
	else if (Offset < 0x004A4353)
		return Offset + 0x21;
	else if (Offset < 0x00600FB0)
		return Offset + 0x20;
	else if (Offset < 0x00601FF9)
	{
		if (Offset < 0x00601E83)
			return Offset + 0x30;
		else if (Offset < 0x00601EAB)
			return Offset + 0x2E;
		else if (Offset < 0x00601EAD)
			return Offset + 0x2C;
		else if (Offset < 0x00601EDC)
			return Offset + 0x30;
		else if (Offset < 0x00601EDE)
			return Offset + 0x2E;
		else if (Offset < 0x00601F0E)
			return Offset + 0x30;
		else if (Offset < 0x00601F10)
			return Offset + 0x2E;
		else if (Offset < 0x00601F48)
			return Offset + 0x30;
		else if (Offset < 0x00601F50)
			return Offset + 0x2E;
		else if (Offset < 0x00601F5F)
			return Offset + 0x28;
		else if (Offset < 0x00601F8C)
			return Offset + 0x26;
		else
			return Offset + 0x24;
	}
	else if (Offset < 0x00626F79)
		return Offset - 0x20;
	else if (Offset < 0x0062758D)
	{
		if (Offset < 0x00626F7F)
			return Offset - 0x1B;
		else if (Offset < 0x006271C9)
			return Offset - 0x20;
		else if (Offset < 0x006271D8)
			return Offset - 0x19;
		else if (Offset < 0x006271ED)
			return Offset - 0x20;
		else if (Offset < 0x006271F7)
			return Offset - 0x14;
		else if (Offset < 0x00627203)
			return Offset - 0x02;
		else if (Offset < 0x0062720A)
			return Offset + 0x20;
		else if (Offset < 0x00627214)
			return Offset - 0x01;
		else if (Offset < 0x0062721B)
			return Offset + 0x08;
		else if (Offset < 0x006272DB)
			return Offset + 0x0F;
		else if (Offset < 0x006273D1)
			return Offset + 0x10;
		else if (Offset < 0x00627448)
			return Offset + 0x23;
		else if (Offset < 0x00627470)
			return Offset + 0x28;
		else if (Offset < 0x006274B6)
			return Offset + 0x26;
		else if (Offset < 0x006274CC)
			return Offset + 0x2A;
		else if (Offset < 0x00627570)
			return Offset + 0x20;
		else
			return Offset + 0x46;
	}
	else if (Offset < 0x0067E000)
		return Offset + 0x50;
	else if (Offset < 0x006D6688)
		return Offset;
	else if (Offset < 0x006D6B28)
		return Offset - 0x2C;
	else if (Offset == 0x006DB8E8)
		return 0x00786D44;
	else if (Offset < 0x006DB8F0)
		return Offset - 0x28;
	else if (Offset < 0x006DB924)
		return Offset - 0x30;
	else if (Offset < 0x006E0000)
		return Offset - 0x10;
	else if (Offset < 0x00786BA8)
		return Offset;
	else if (Offset < 0x00786D40)
		return Offset + 0x04;
	else if (Offset < 0x00A10B56)
		return Offset + 0x08;
	else if (Offset < 0x00A12000)
		return Offset + 0x09;
	else
		return Offset;
}

unsigned long AdjustOffsetAUS10(unsigned long Offset)
{
	if (Offset < 0x00600B8A)
		return AdjustOffsetUS11(Offset);
	else if (Offset < 0x00600FB0)
	{
		if (Offset < 0x00600B91)
			return Offset + 0x25;
		else if (Offset < 0x00600B96)
			return Offset + 0x19;
		else if (Offset < 0x00600BFD)
			return Offset + 0x20;
		else if (Offset < 0x00600C40)
			return Offset - 0x36;
		else if (Offset < 0x00600C4A)
			return Offset - 0x73;
		else if (Offset < 0x00600C4F)
			return Offset - 0x88;
		else if (Offset < 0x00600C6E)
			return Offset - 0x78;
		else
			return Offset - 0x80;
	}
	else if (Offset < 0x0067E000)
		return AdjustOffsetUS11(Offset) - 0xA0;
	else if (Offset < 0x0068DD6C)
		return Offset;
	else if (Offset < 0x0068E008)
		return Offset + 0x04;
	else if (Offset < 0x006D6688)
		return Offset + 0x08;
	else if (Offset < 0x006D6934)
		return Offset - 0x24;
	else if (Offset < 0x006D6B28)
		return Offset - 0x4C;
	else if (Offset == 0x006DB8E8)
		return 0x00786D44;
	else if (Offset < 0x006DB8F0)
		return Offset - 0x48;
	else if (Offset < 0x006DB924)
		return Offset - 0x50;
	else if (Offset < 0x006E0000)
		return Offset - 0x30;
	else if (Offset < 0x00786BA8)
		return Offset;
	else if (Offset < 0x00786D40)
		return Offset + 0x04;
	else if (Offset < 0x00A10B56)
		return Offset + 0x08;
	else if (Offset < 0x00A10B9C)
		return Offset + 0x09;
	else if (Offset < 0x00A12000)
		return Offset + 0x08;
	else
		return Offset;
}

unsigned long AdjustOffsetGER10(unsigned long Offset)
{
	if (Offset < 0x004A3941)
		return AdjustOffsetUS11(Offset);
	else if (Offset < 0x004A3948)
	return Offset + 0x0E;
	else if (Offset < 0x004A4357)
		return Offset + 0x15;
	else if (Offset < 0x005367AE)
		return Offset + 0x10;
	else if (Offset < 0x00536E5B)
	{
		if (Offset < 0x005367B7)
			return Offset + 0x1D;
		else if (Offset < 0x005367C4)
			return Offset + 0x19;
		else if (Offset < 0x005367D8)
			return Offset - 0x04;
		else if (Offset < 0x005367E3)
			return Offset - 0x08;
		else if (Offset < 0x00536855)
			return Offset - 0x0C;
		else if (Offset < 0x005368E0)
			return Offset - 0x05;
		else if (Offset < 0x00536966)
			return Offset - 0x0C;
		else if (Offset < 0x00536A20)
			return Offset - 0x06;
		else if (Offset < 0x00536AA0)
			return Offset - 0x04;
		else if (Offset < 0x00536D37)
			return Offset - 0x0D;
		else if (Offset < 0x00536D90)
			return Offset - 0x07;
		else if (Offset < 0x00536DC7)
			return Offset - 0x0C;
		else if (Offset < 0x00536E32)
			return Offset - 0x07;
		else
			return Offset - 0x02;
	}
	else
		return Offset;
}

unsigned long AdjustOffsetGER11(unsigned long Offset)
{
	if (Offset < 0x00600FB0)
		return AdjustOffsetGER10(Offset);
	else if (Offset < 0x0067E000)
		return AdjustOffsetUS11(Offset) - 0x10;
	else
		return AdjustOffsetUS11(Offset);
}
