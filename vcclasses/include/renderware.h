#ifndef __RENDERWARE_H__
#define __RENDERWARE_H__

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifdef TRUE
#undef TRUE
#endif
#define TRUE !FALSE

#ifdef NULL
#undef NULL
#endif
#define NULL 0

#ifndef MACRO_START
#define MACRO_START do
#endif /* MACRO_START */

#ifndef MACRO_STOP
#define MACRO_STOP while(0)
#endif /* MACRO_STOP */

typedef long RwFixed;
typedef int  RwInt32;
typedef unsigned int RwUInt32;
typedef short RwInt16;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef signed char RwInt8;

typedef char RwChar;
typedef float RwReal;
typedef RwInt32 RwBool;

#define RWALIGN(type, x)   type
#define rwMATRIXALIGNMENT sizeof(RwUInt32)
#define rwFRAMEALIGNMENT sizeof(RwUInt32)
#define rwV4DALIGNMENT sizeof(RwUInt32)

typedef enum RwCorePluginID RwCorePluginID;

enum RwCorePluginID
{
	rwID_NAOBJECT = 0x00,
	rwID_STRUCT = 0x01,
	rwID_STRING = 0x02,
	rwID_EXTENSION = 0x03,
	rwID_CAMERA = 0x05,
	rwID_TEXTURE = 0x06,
	rwID_MATERIAL = 0x07,
	rwID_MATLIST = 0x08,
	rwID_ATOMICSECT = 0x09,
	rwID_PLANESECT = 0x0A,
	rwID_WORLD = 0x0B,
	rwID_SPLINE = 0x0C,
	rwID_MATRIX = 0x0D,
	rwID_FRAMELIST = 0x0E,
	rwID_GEOMETRY = 0x0F,
	rwID_CLUMP = 0x10,
	rwID_LIGHT = 0x12,
	rwID_UNICODESTRING = 0x13,
	rwID_ATOMIC = 0x14,
	rwID_TEXTURENATIVE = 0x15,
	rwID_TEXDICTIONARY = 0x16,
	rwID_ANIMDATABASE = 0x17,
	rwID_IMAGE = 0x18,
	rwID_SKINANIMATION = 0x19,
	rwID_GEOMETRYLIST = 0x1A,
	rwID_HANIMANIMATION = 0x1B,
	rwID_TEAM = 0x1C,
	rwID_CROWD = 0x1D,
	rwID_DMORPHANIMATION = 0x1E,
	rwID_RIGHTTORENDER = 0x1f,
	rwID_MTEFFECTNATIVE = 0x20,
	rwID_MTEFFECTDICT = 0x21,
	rwID_TEAMDICTIONARY = 0x22,
	rwID_PITEXDICTIONARY = 0x23,
	rwID_TOC = 0x24,
	rwID_PRTSTDGLOBALDATA = 0x25,
	rwID_ALTPIPE = 0x26,
	rwID_PIPEDS = 0x27,
	rwID_COREPLUGINIDMAX = 0x28,
	rwCOREPLUGINIDFORCEENUMSIZEINT = 0x7FFFFFFF,
};

typedef struct RwObject RwObject;
struct RwObject
{
	RwUInt8 type;
	RwUInt8 subType;
	RwUInt8 flags;
	RwUInt8 privateFlags;
	void   *parent;
};

typedef struct RwV3d RwV3d;

struct RwV3d
{
	RwReal x, y, z;
};

typedef struct RwV2d RwV2d;
struct RwV2d
{
	RwReal x, y;
};

typedef struct RwRGBA RwRGBA;
struct RwRGBA
{
	RwUInt8 r, g, b, a;
};

typedef struct RwRect RwRect;
struct RwRect
{
	RwInt32 x;
	RwInt32 y;
	RwInt32 w;
	RwInt32 h;
};

typedef struct RwSphere RwSphere;
struct RwSphere
{
	RwV3d center;
	RwReal radius;
};

typedef struct RwLine RwLine;
struct RwLine
{
	RwV3d start;
	RwV3d end;
};

#define rwMAXTEXTURECOORDS 8

enum RwTextureCoordinateIndex
{
	rwNARWTEXTURECOORDINATEINDEX = 0,
	rwTEXTURECOORDINATEINDEX0,
	rwTEXTURECOORDINATEINDEX1,
	rwTEXTURECOORDINATEINDEX2,
	rwTEXTURECOORDINATEINDEX3,
	rwTEXTURECOORDINATEINDEX4,
	rwTEXTURECOORDINATEINDEX5,
	rwTEXTURECOORDINATEINDEX6,
	rwTEXTURECOORDINATEINDEX7,
	rwTEXTURECOORDINATEINDEXFORCEENUMSIZEINT = 0x7FFFFFFF,
};
typedef enum RwTextureCoordinateIndex RwTextureCoordinateIndex;

typedef struct RwTexCoords RwTexCoords;

struct RwTexCoords
{
	RwReal u;
	RwReal v;
};

typedef struct RwTexture RwTexture;

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

enum RwRenderState
{
	rwRENDERSTATENARENDERSTATE = 0,
	rwRENDERSTATETEXTURERASTER,
	rwRENDERSTATETEXTUREADDRESS,
	rwRENDERSTATETEXTUREADDRESSU,
	rwRENDERSTATETEXTUREADDRESSV,
	rwRENDERSTATETEXTUREPERSPECTIVE,
	rwRENDERSTATEZTESTENABLE,
	rwRENDERSTATESHADEMODE,
	rwRENDERSTATEZWRITEENABLE,
	rwRENDERSTATETEXTUREFILTER,
	rwRENDERSTATESRCBLEND,
	rwRENDERSTATEDESTBLEND,
	rwRENDERSTATEVERTEXALPHAENABLE,
	rwRENDERSTATEBORDERCOLOR,
	rwRENDERSTATEFOGENABLE,
	rwRENDERSTATEFOGCOLOR,
	rwRENDERSTATEFOGTYPE,
	rwRENDERSTATEFOGDENSITY,
	rwRENDERSTATECULLMODE = 20,
	rwRENDERSTATESTENCILENABLE,
	rwRENDERSTATESTENCILFAIL,
	rwRENDERSTATESTENCILZFAIL,
	rwRENDERSTATESTENCILPASS,
	rwRENDERSTATESTENCILFUNCTION,
	rwRENDERSTATESTENCILFUNCTIONREF,
	rwRENDERSTATESTENCILFUNCTIONMASK,
	rwRENDERSTATESTENCILFUNCTIONWRITEMASK,
	rwRENDERSTATEFORCEENUMSIZEINT = 0x7FFFFFFF,
};
typedef enum RwRenderState RwRenderState;

enum RwShadeMode
{
	rwSHADEMODENASHADEMODE = 0,
	rwSHADEMODEFLAT,
	rwSHADEMODEGOURAUD,
	rwSHADEMODEFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwShadeMode RwShadeMode;


enum RwTextureFilterMode
{
	rwFILTERNAFILTERMODE = 0,
	rwFILTERNEAREST,
	rwFILTERLINEAR,
	rwFILTERMIPNEAREST,
	rwFILTERMIPLINEAR,
	rwFILTERLINEARMIPNEAREST,
	rwFILTERLINEARMIPLINEAR,
	rwTEXTUREFILTERMODEFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwTextureFilterMode RwTextureFilterMode;


enum RwFogType
{
	rwFOGTYPENAFOGTYPE = 0,
	rwFOGTYPELINEAR,
	rwFOGTYPEEXPONENTIAL,
	rwFOGTYPEEXPONENTIAL2,
	rwFOGTYPEFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwFogType RwFogType;


enum RwBlendFunction
{
	rwBLENDNABLEND = 0,
	rwBLENDZERO,
	rwBLENDONE,
	rwBLENDSRCCOLOR,
	rwBLENDINVSRCCOLOR,
	rwBLENDSRCALPHA,
	rwBLENDINVSRCALPHA,
	rwBLENDDESTALPHA,
	rwBLENDINVDESTALPHA,
	rwBLENDDESTCOLOR,
	rwBLENDINVDESTCOLOR,
	rwBLENDSRCALPHASAT,
	rwBLENDFUNCTIONFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwBlendFunction RwBlendFunction;


enum RwTextureAddressMode
{
	rwTEXTUREADDRESSNATEXTUREADDRESS = 0,
	rwTEXTUREADDRESSWRAP,
	rwTEXTUREADDRESSMIRROR,
	rwTEXTUREADDRESSCLAMP,
	rwTEXTUREADDRESSBORDER,
	rwTEXTUREADDRESSMODEFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwTextureAddressMode RwTextureAddressMode;


enum RwStencilOperation
{
	rwSTENCILOPERATIONNASTENCILOPERATION = 0,
	rwSTENCILOPERATIONKEEP,
	rwSTENCILOPERATIONZERO,
	rwSTENCILOPERATIONREPLACE,
	rwSTENCILOPERATIONINCRSAT,
	rwSTENCILOPERATIONDECRSAT,
	rwSTENCILOPERATIONINVERT,
	rwSTENCILOPERATIONINCR,
	rwSTENCILOPERATIONDECR,
	rwSTENCILOPERATIONFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwStencilOperation RwStencilOperation;


enum RwStencilFunction
{
	rwSTENCILFUNCTIONNASTENCILFUNCTION = 0,
	rwSTENCILFUNCTIONNEVER,
	rwSTENCILFUNCTIONLESS,
	rwSTENCILFUNCTIONEQUAL,
	rwSTENCILFUNCTIONLESSEQUAL,
	rwSTENCILFUNCTIONGREATER,
	rwSTENCILFUNCTIONNOTEQUAL,
	rwSTENCILFUNCTIONGREATEREQUAL,
	rwSTENCILFUNCTIONALWAYS,
	rwSTENCILFUNCTIONFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwStencilFunction RwStencilFunction;

enum RwCullMode
{
	rwCULLMODENACULLMODE = 0,
	rwCULLMODECULLNONE,
	rwCULLMODECULLBACK,
	rwCULLMODECULLFRONT,
	rwCULLMODEFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwCullMode RwCullMode;

enum RwPrimitiveType
{
	rwPRIMTYPENAPRIMTYPE = 0,
	rwPRIMTYPELINELIST = 1,
	rwPRIMTYPEPOLYLINE = 2,
	rwPRIMTYPETRILIST = 3,
	rwPRIMTYPETRISTRIP = 4,
	rwPRIMTYPETRIFAN = 5,
	rwPRIMTYPEPOINTLIST = 6,
	rwPRIMITIVETYPEFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwPrimitiveType RwPrimitiveType;

enum RwOpCombineType
{
	rwCOMBINEREPLACE = 0,
	rwCOMBINEPRECONCAT,
	rwCOMBINEPOSTCONCAT,
	rwOPCOMBINETYPEFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RwOpCombineType RwOpCombineType;

typedef struct RwMatrix RwMatrix;

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

typedef RwMatrix RwMatrixTag;

typedef enum RwStreamType RwStreamType;

enum RwStreamType
{
	rwNASTREAM = 0,
	rwSTREAMFILE,
	rwSTREAMFILENAME,
	rwSTREAMMEMORY,
	rwSTREAMCUSTOM,
	rwSTREAMTYPEFORCEENUMSIZEINT = 0x7FFFFFFF
};

typedef enum RwStreamAccessType RwStreamAccessType;

enum RwStreamAccessType
{
	rwNASTREAMACCESS = 0,
	rwSTREAMREAD,
	rwSTREAMWRITE,
	rwSTREAMAPPEND,
	rwSTREAMACCESSTYPEFORCEENUMSIZEINT = 0x7FFFFFFF
};

typedef struct RxObjSpace3DVertex RxObjSpace3DVertex;

struct RxObjSpace3DVertex
{
	RwV3d        objVertex;
	RwV3d        objNormal;
	unsigned int color;
	float        u;
	float        v;
};

typedef struct RwLLLink  RwLLLink;
struct RwLLLink
{
	RwLLLink *next;
	RwLLLink *prev;
};

typedef struct RwLinkList RwLinkList;
struct RwLinkList
{
	RwLLLink link;
};

struct RwFrame
{
	RwObject            object;
	RwLLLink            inDirtyListLink;
	RwMatrix            modelling;
	RwMatrix            ltm;
	RwLinkList          objectList;
	struct RwFrame      *child;
	struct RwFrame      *next;
	struct RwFrame      *root;
};
typedef struct RwFrame RWALIGN(RwFrame, rwFRAMEALIGNMENT);

typedef struct RwObjectHasFrame RwObjectHasFrame;
typedef RwObjectHasFrame * (*RwObjectHasFrameSyncFunction)(RwObjectHasFrame *object);

struct RwObjectHasFrame
{
	RwObject                     object;
	RwLLLink                     lFrame;
	RwObjectHasFrameSyncFunction sync;
};

typedef struct RwSurfaceProperties RwSurfaceProperties;
struct RwSurfaceProperties
{
	RwReal ambient;
	RwReal specular;
	RwReal diffuse;
};

typedef struct RwResEntry RwResEntry;
typedef void(*RwResEntryDestroyNotify) (RwResEntry * resEntry);

struct RwResEntry
{
	RwLLLink            link;
	RwInt32             size;
	void               *owner;
	RwResEntry        **ownerRef;
	RwResEntryDestroyNotify destroyNotify;
};

typedef struct RpClump RpClump;
typedef RpClump    *(*RpClumpCallBack) (RpClump * clump, void *data);
struct RpClump
{
	RwObject            object;

	RwLinkList          atomicList;

	RwLinkList          lightList;
	RwLinkList          cameraList;

	RwLLLink            inWorldLink;

	RpClumpCallBack     callback;

	RwUInt16            renderFrame;
	RwUInt16            pad;
};

typedef struct RpMaterial RpMaterial;
struct RpMaterial
{
	RwTexture           *texture;
	RwRGBA              color;
	void          *pipeline;
	RwSurfaceProperties surfaceProps;
	RwInt16             refCount;
	RwInt16             pad;
};

typedef struct RpMaterialList RpMaterialList;
struct RpMaterialList
{
	RpMaterial     **materials;
	RwInt32        numMaterials;
	RwInt32        space;
};

typedef struct RpGeometry RpGeometry;

typedef struct RpMorphTarget RpMorphTarget;
struct RpMorphTarget
{
	RpGeometry *parentGeom;
	RwSphere   boundingSphere;
	RwV3d      *verts;
	RwV3d      *normals;
};

typedef struct RpTriangle RpTriangle;
struct RpTriangle
{
	RwUInt16            vertIndex[3];
	RwInt16             matIndex;
};

typedef struct RpInterpolator RpInterpolator;
struct RpInterpolator
{
	RwInt32             flags;
	RwInt16             startMorphTarget;
	RwInt16             endMorphTarget;
	RwReal              time;
	RwReal              recipTime;
	RwReal              position;
};

struct RpGeometry
{
	RwObject            object;
	RwUInt32            flags;
	RwUInt16            lockedSinceLastInst;
	RwInt16             refCount;
	RwInt32             numTriangles;
	RwInt32             numVertices;
	RwInt32             numMorphTargets;
	RwInt32             numTexCoordSets;
	RpMaterialList      matList;
	RpTriangle         *triangles;
	RwRGBA             *preLitLum;
	RwTexCoords        *texCoords[rwMAXTEXTURECOORDS];
	void       *mesh;
	RwResEntry         *repEntry;
	RpMorphTarget      *morphTarget;
};

typedef struct RpAtomic RpAtomic;
typedef RpAtomic   *(*RpAtomicCallBackRender) (RpAtomic * atomic);
struct RpAtomic
{
	RwObjectHasFrame    object;
	RwResEntry         *repEntry;
	RpGeometry         *geometry;
	RwSphere            boundingSphere;
	RwSphere            worldBoundingSphere;
	RpClump            *clump;
	RwLLLink            inClumpLink;
	RpAtomicCallBackRender renderCallBack;
	RpInterpolator      interpolator;
	RwUInt16            renderFrame;
	RwUInt16            pad;
	RwLinkList          llWorldSectorsInAtomic;
	void         *pipeline;
};

typedef RpAtomic   *(*RpAtomicCallBack) (RpAtomic * atomic, void *data);
typedef RpAtomic   *(*RpAtomicCallBackRender) (RpAtomic * atomic);

#define RpHANIMSTREAMCURRENTVERSION 0x100

typedef struct RpHAnimAnimation RpHAnimAnimation;

typedef void(*RpHAnimKeyFrameApplyCallBack) (void *result, void *voidIFrame);
typedef void(*RpHAnimKeyFrameBlendCallBack) (void *voidOut, void *voidIn1, void *voidIn2, float alpha);
typedef void(*RpHAnimKeyFrameInterpolateCallBack) (void *voidOut, void *voidIn1, void *voidIn2, float time);
typedef void(*RpHAnimKeyFrameAddCallBack) (void *voidOut, void *voidIn1, void *voidIn2);
typedef void(*RpHAnimKeyFrameMulRecipCallBack)(void *voidFrame, void *voidStart);
typedef RpHAnimAnimation * (*RpHAnimKeyFrameStreamReadCallBack)(void *stream, RpHAnimAnimation *animation);
typedef int(*RpHAnimKeyFrameStreamWriteCallBack)(const RpHAnimAnimation *animation, void *stream);
typedef int(*RpHAnimKeyFrameStreamGetSizeCallBack)(const RpHAnimAnimation *animation);

typedef struct RpHAnimInterpolatorInfo RpHAnimInterpolatorInfo;

struct RpHAnimInterpolatorInfo
{
	int										typeID;
	int										interpKeyFrameSize;
	RpHAnimKeyFrameApplyCallBack			keyFrameApplyCB;
	RpHAnimKeyFrameBlendCallBack			keyFrameBlendCB;
	RpHAnimKeyFrameInterpolateCallBack	keyFrameInterpolateCB;
	RpHAnimKeyFrameAddCallBack			keyFrameAddCB;
	RpHAnimKeyFrameMulRecipCallBack		keyFrameMulRecipCB;
	RpHAnimKeyFrameStreamReadCallBack		keyFrameStreamReadCB;
	RpHAnimKeyFrameStreamWriteCallBack	keyFrameStreamWriteCB;
	RpHAnimKeyFrameStreamGetSizeCallBack	keyFrameStreamGetSizeCB;
	int										customDataSize;
};

typedef struct RpHAnimAnimation RpHAnimAnimation;

struct RpHAnimAnimation
{
	RpHAnimInterpolatorInfo	*interpInfo;
	int							numFrames;
	int							flags;
	float						duration;
	void						*pFrames;
	void						*customData;
};

typedef struct RpHAnimKeyFrameHeader RpHAnimKeyFrameHeader;

struct RpHAnimKeyFrameHeader
{
	void	*prevFrame;
	float	time;
};

typedef struct RpHAnimInterpFrameHeader RpHAnimInterpFrameHeader;

struct RpHAnimInterpFrameHeader
{
	RpHAnimKeyFrameHeader	*keyFrame1;
	RpHAnimKeyFrameHeader	*keyFrame2;
};

typedef struct RpHAnimInterpolator RpHAnimInterpolator;

typedef RpHAnimInterpolator *(*RpHAnimCallBack)(RpHAnimInterpolator *animInstance, void *data);

struct RpHAnimInterpolator
{
	RpHAnimAnimation		*pCurrentAnim;
	float					currentTime;
	void					*pNextFrame;
	RpHAnimCallBack		pAnimCallBack;
	void					*pAnimCallBackData;
	float					animCallBackTime;
	RpHAnimCallBack		pAnimLoopCallBack;
	void					*pAnimLoopCallBackData;
	int						maxKeyFrameSize;
	int						currentKeyFrameSize;
	int						numNodes;
	int						isSubInterpolator;
	int						offsetInParent;
	RpHAnimInterpolator	*parentAnimation;

	RpHAnimKeyFrameApplyCallBack			keyFrameApplyCB;
	RpHAnimKeyFrameBlendCallBack			keyFrameBlendCB;
	RpHAnimKeyFrameInterpolateCallBack	keyFrameInterpolateCB;
	RpHAnimKeyFrameAddCallBack			keyFrameAddCB;
};

typedef struct RpHAnimNodeInfo RpHAnimNodeInfo;

struct RpHAnimNodeInfo
{
	int	nodeID;     /**< User defined ID for this node  */
	int	nodeIndex;  /**< Array index of node  */
	int	flags;      /**< Matrix push/pop flags  */
	void *pFrame;     /**< Pointer to an attached RwFrame (see \ref RpHAnimHierarchyAttach) */
};

typedef struct RpHAnimHierarchy RpHAnimHierarchy;
typedef struct RtAnimInterpolator RtAnimInterpolator;

struct RpHAnimHierarchy
{
	int				flags;
	int				numNodes;

	void			*pMatrixArray;
	void				*pMatrixArrayUnaligned;
	RpHAnimNodeInfo	*pNodeInfo;
	void				*parentFrame;
	RpHAnimHierarchy	*parentHierarchy;
	int				rootParentOffset;

	RtAnimInterpolator	*currentAnim;
};

#ifdef rtANIMGETINTERPFRAME
#undef rtANIMGETINTERPFRAME
#endif

#define rtANIMGETINTERPFRAME( anim, nodeIndex )                              \
	((void *)(((unsigned char *)&(anim[1]) + \
	((nodeIndex)*                                           \
	anim->currentKeyFrameSize))))

#define RpClumpGetFrame(clump) (RwFrame *)((void **)clump)[1]
#define RwMatrixCopy(dst, src) (*(dst) = *(src))

#ifdef __cplusplus
extern "C"
{
#endif
	unsigned long RpAnimBlendClumpGetFirstAssociation(unsigned long);
	void RsMouseSetPos(RwV2d *);

	RpClump *RpClumpForAllAtomics(RpClump * clump, RpAtomicCallBack callback, void *pData);
	int RwMatrixDestroy(RwMatrix *);
	RwBool RwRenderStateSet(RwRenderState state, void *value);
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
	unsigned int RwStreamRead(void *stream, void *buffer, unsigned int length);
	RwFrame *RwFrameForAllChildren(RwFrame *frame, void *callBack, void *data);
	RwMatrix *RwFrameGetLTM(RwFrame *frame);
	void *RwStreamOpen(RwStreamType type, RwStreamAccessType accessType, const void *pData);
	void *RwStreamSkip(void *stream, unsigned int offset);
	int RwStreamFindChunk(void *stream, unsigned int type, unsigned int *lengthOut, unsigned int *versionOut);
	int RwStreamClose(void *stream, void *pData);

	RwMatrix *RwMatrixCreate(void);
	RwMatrix *RwMatrixScale(RwMatrix * matrix, const RwV3d * scale, int combineOp);

	RpHAnimAnimation *RpHAnimAnimationCreate(int typeID, int numFrames, int flags, float duration);
	int RpHAnimInterpolatorSetCurrentAnim(RpHAnimInterpolator *, RpHAnimAnimation *);
	int RpHAnimIDGetIndex(RpHAnimHierarchy *hierarchy, int ID);
	RwMatrix *RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy *hierarchy);
	RpHAnimHierarchy *RpSkinAtomicGetHAnimHierarchy(const void *atomic);
	int RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy *hierarchy);

	// Below 2 functions don't exist in VC, these are in RpHAnim.cpp
	int RpHAnimInterpolatorAddAnimTime(RpHAnimInterpolator *anim, float time);
	RpHAnimAnimation *RpHAnimAnimationStreamRead(void *stream);
#ifdef __cplusplus
}
#endif

#endif
