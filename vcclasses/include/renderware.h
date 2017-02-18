#ifndef __RENDERWARE_H__
#define __RENDERWARE_H__

struct RwV3d
{
	float x, y, z;
};

struct RwV2d
{
	float x, y;
};

struct RwRGBA
{
	unsigned char r, g, b, a;
};

struct RwTexture
{
	unsigned char space[0x5C];
};

struct RwMatrix
{
	unsigned char space[0x40];
};

void RsMouseSetPos(RwV2d *);
bool RwMatrixDestroy(RwMatrix *);
int RwRenderStateSet(int, int);
unsigned long RwTextureRead(const char *, const char *);

#endif