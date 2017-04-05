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
	RwV3d        right;
	unsigned int flags;
	RwV3d        up;
	unsigned int pad1;
	RwV3d        at;
	unsigned int pad2;
	RwV3d        pos;
	unsigned int pad3;
};

struct RxObjSpace3DVertex
{
	RwV3d        objVertex;
	RwV3d        objNormal;
	unsigned int color;
	float        u;
	float        v;
};

void RsMouseSetPos(RwV2d *);
bool RwMatrixDestroy(RwMatrix *);
int RwRenderStateSet(int, int);
unsigned long RwTextureRead(const char *, const char *);
RxObjSpace3DVertex *RwIm3DTransform(RxObjSpace3DVertex *, unsigned int, void *, unsigned int);
int RwIm3DEnd(void);
int RwIm3DRenderIndexedPrimitive(int, unsigned short *, int);
int RwIm3DRenderLine(int, int);

#endif