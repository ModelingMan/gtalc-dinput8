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

extern void RsMouseSetPos(RwV2d *);
extern int RwRenderStateSet(int, int);

#endif