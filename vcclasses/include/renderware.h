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
	unsigned long raster;           // 0x00
	unsigned long dict;             // 0x04
	unsigned long next;             // 0x08
	unsigned long prev;             // 0x0C
	char          name[32];         // 0x10
	char          mask[32];         // 0x30
	unsigned int  filterAddressing; // 0x50
	int           refCount;         // 0x54
	unsigned char maxAnisotropy;    // 0x58
	char          pad[3];           // 0x59
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

unsigned long RpAnimBlendClumpGetFirstAssociation(unsigned long);
void RsMouseSetPos(RwV2d *);
unsigned long RpClumpForAllAtomics(unsigned long, unsigned long(*)(unsigned long, void *), void *);
bool RwMatrixDestroy(RwMatrix *);
int RwRenderStateSet(int, int);
unsigned long RpGeometryForAllMaterials(unsigned long, unsigned long(*)(unsigned long, void *), void *);
RwTexture *RwTextureRead(const char *, const char *);
unsigned long RpMaterialSetTexture(unsigned long, RwTexture *);
unsigned long RpMatFXAtomicEnableEffects(unsigned long);
unsigned long RpMatFXMaterialSetEffects(unsigned long, unsigned long);
unsigned long RpMatFXMaterialSetupEnvMap(unsigned long, RwTexture *, unsigned long, int, float);
unsigned long RpMatFXMaterialGetEffects(unsigned long);
RxObjSpace3DVertex *RwIm3DTransform(RxObjSpace3DVertex *, unsigned int, void *, unsigned int);
int RwIm3DEnd(void);
int RwIm3DRenderIndexedPrimitive(int, unsigned short *, int);
int RwIm3DRenderLine(int, int);

#endif