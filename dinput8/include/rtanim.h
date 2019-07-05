#ifndef __RTANIM_H__
#define __RTANIM_H__

#define rtANIMSTREAMCURRENTVERSION 0x100

typedef struct RtAnimAnimation RtAnimAnimation;

typedef void(*RtAnimKeyFrameApplyCallBack)(void *result, void *voidIFrame);
typedef void(*RtAnimKeyFrameBlendCallBack)(void *voidOut, void *voidIn1, void *voidIn2, float alpha);
typedef void(*RtAnimKeyFrameInterpolateCallBack)(void *voidOut, void *voidIn1,	void *voidIn2, float time);
typedef void(*RtAnimKeyFrameAddCallBack)(void *voidOut, void *voidIn1, void *voidIn2);
typedef void(*RtAnimKeyFrameMulRecipCallBack)(void *voidFrame, void *voidStart);
typedef RtAnimAnimation * (*RtAnimKeyFrameStreamReadCallBack)(void *stream, RtAnimAnimation *animation);
typedef int(*RtAnimKeyFrameStreamWriteCallBack)(RtAnimAnimation *animation, void *stream);
typedef int(*RtAnimKeyFrameStreamGetSizeCallBack)(RtAnimAnimation *animation);

typedef struct RtAnimInterpolatorInfo RtAnimInterpolatorInfo;

struct RtAnimInterpolatorInfo
{
	int                             typeID;
	int                             keyFrameSize;
	RtAnimKeyFrameApplyCallBack         keyFrameApplyCB;
	RtAnimKeyFrameBlendCallBack         keyFrameBlendCB;
	RtAnimKeyFrameInterpolateCallBack   keyFrameInterpolateCB;
	RtAnimKeyFrameAddCallBack           keyFrameAddCB;
	RtAnimKeyFrameMulRecipCallBack      keyFrameMulRecipCB;
	RtAnimKeyFrameStreamReadCallBack    keyFrameStreamReadCB;
	RtAnimKeyFrameStreamWriteCallBack   keyFrameStreamWriteCB;
	RtAnimKeyFrameStreamGetSizeCallBack keyFrameStreamGetSizeCB;
};

struct RtAnimAnimation
{
	RtAnimInterpolatorInfo              *interpInfo;
	int                             numFrames;
	int                             flags;
	float                              duration;
	void                                *pFrames;
};

typedef struct RtAnimKeyFrameHeader RtAnimKeyFrameHeader;

struct RtAnimKeyFrameHeader
{
	void                                *prevFrame;
	float                              time;
};

typedef struct RtAnimInterpFrameHeader RtAnimInterpFrameHeader;

struct RtAnimInterpFrameHeader
{
	RtAnimKeyFrameHeader    *keyFrame1;
	RtAnimKeyFrameHeader    *keyFrame2;
};

typedef struct RtAnimInterpolator RtAnimInterpolator;

typedef RtAnimInterpolator *(*RtAnimCallBack)(RtAnimInterpolator *animInstance, void *data);

struct RtAnimInterpolator
{
	RtAnimAnimation                   *pCurrentAnim;
	float                              currentTime;
	void                                *pNextFrame;
	RtAnimCallBack                    pAnimCallBack;
	void                                *pAnimCallBackData;
	float                              animCallBackTime;
	RtAnimCallBack                    pAnimLoopCallBack;
	void                                *pAnimLoopCallBackData;
	int                             maxKeyFrameSize;
	int                             currentKeyFrameSize;
	int                             numNodes;
	int                              isSubInterpolator;
	int                             offsetInParent;
	RtAnimInterpolator           *parentAnimation;

	RtAnimKeyFrameApplyCallBack       keyFrameApplyCB;
	RtAnimKeyFrameBlendCallBack       keyFrameBlendCB;
	RtAnimKeyFrameInterpolateCallBack keyFrameInterpolateCB;
	RtAnimKeyFrameAddCallBack         keyFrameAddCB;
};

#ifdef    __cplusplus
extern              "C"
{
#endif

	extern void RtAnimAnimationFreeListCreateParams(int blockSize, int numBlocksToPrealloc);
	extern int RtAnimInitialize(void);
	extern int RtAnimRegisterInterpolationScheme(RtAnimInterpolatorInfo *interpolatorInfo);
	extern RtAnimInterpolatorInfo *RtAnimGetInterpolatorInfo(int typeID);

	extern RtAnimAnimation *RtAnimAnimationCreate(int typeID, int numFrames, int flags, float duration);
	extern RtAnimAnimation *RtAnimAnimationDestroy(RtAnimAnimation *animation);
	extern RtAnimAnimation *RtAnimAnimationRead(const char *filename);
	extern int RtAnimAnimationWrite(RtAnimAnimation *animation, const char *filename);
	extern RtAnimAnimation *RtAnimAnimationStreamRead(void *stream);
	extern int RtAnimAnimationStreamWrite(RtAnimAnimation *animation, void *stream);
	extern int RtAnimAnimationStreamGetSize(RtAnimAnimation *animation);
	extern int RtAnimAnimationGetNumNodes(RtAnimAnimation *animation);

#ifdef RWDEBUG

	extern int RtAnimAnimationGetTypeID(RtAnimAnimation *animation);

#else

#define RtAnimAnimationGetTypeID(animation) (animation->interpInfo->typeID)

#endif

	extern RtAnimInterpolator *RtAnimInterpolatorCreate(int numNodes, int maxKeyFrameSize);
	extern void RtAnimInterpolatorDestroy(RtAnimInterpolator *anim);
	extern int RtAnimInterpolatorSetCurrentAnim(RtAnimInterpolator *animI, RtAnimAnimation *anim);

#ifdef RWDEBUG

	extern RtAnimAnimation *RtAnimInterpolatorGetCurrentAnim(RtAnimInterpolator *animI);

#else

#define RtAnimInterpolatorGetCurrentAnim(animI)  (animI->pCurrentAnim)

#endif

	extern int RtAnimInterpolatorSetKeyFrameCallBacks(RtAnimInterpolator *anim, int keyFrameTypeID);
	extern void RtAnimInterpolatorSetAnimLoopCallBack(RtAnimInterpolator *anim, RtAnimCallBack callBack, void *data);
	extern void RtAnimInterpolatorSetAnimCallBack(RtAnimInterpolator *anim, RtAnimCallBack callBack, float time, void *data);
	extern int RtAnimInterpolatorCopy(RtAnimInterpolator *outAnim, RtAnimInterpolator *inAnim);
	extern int RtAnimInterpolatorSubAnimTime(RtAnimInterpolator *anim, float time);
	extern int RtAnimInterpolatorAddAnimTime(RtAnimInterpolator *anim, float time);
	extern int RtAnimInterpolatorSetCurrentTime(RtAnimInterpolator *anim, float time);
	extern int RtAnimAnimationMakeDelta(RtAnimAnimation *animation, int numNodes, float time);
	extern int RtAnimInterpolatorBlend(RtAnimInterpolator *outAnim, RtAnimInterpolator *inAnim1, RtAnimInterpolator *inAnim2, float alpha);
	extern int RtAnimInterpolatorAddTogether(RtAnimInterpolator *outAnim, RtAnimInterpolator *inAnim1, RtAnimInterpolator *inAnim2);

#define RtAnimKeyFrameApplyMacro(animation, out, in)                         \
	MACRO_START                                                                    \
	{                                                                              \
	(anim)->keyFrameApplyCB((out), (in1), (in2), (time));                      \
	}                                                                              \
	MACRO_STOP


#define RtAnimKeyFrameInterpolateMacro(anim, out, in1, in2, time)            \
	MACRO_START                                                                    \
	{                                                                              \
	(anim)->keyFrameInterpolateCB((out), (in1), (in2), (time));                \
	}                                                                              \
	MACRO_STOP

#define RtAnimKeyFrameBlendMacro(anim, out, in1, in2, fAlpha)                \
	MACRO_START                                                                    \
	{                                                                              \
	(anim)->keyFrameBlendCB((out), (in1), (in2), (fAlpha));                    \
	}                                                                              \
	MACRO_STOP

#define RtAnimKeyFrameAddTogetherMacro(anim, out, in1, in2)                  \
	MACRO_START                                                                    \
	{                                                                              \
	(anim)->keyFrameAddCB((out), (in1), (in2));                                \
	}                                                                              \
	MACRO_STOP

#ifdef RWDEBUG
	extern void RtAnimKeyFrameApply(RtAnimInterpolator *animation, void *result, void *iFrame);
	extern void RtAnimKeyFrameInterpolate(RtAnimInterpolator *animation, void *out, void *in1, void *in2, float time);
	extern void RtAnimKeyFrameBlend(RtAnimInterpolator *animation, void *out, void *in1, void *in2, float alpha);
	extern void RtAnimKeyFrameAddTogether(RtAnimInterpolator *animation, void *out, void *in1, void *in2);
#else
#define RtAnimKeyFrameApply(animation, out, in) RtAnimKeyFrameApplyMacro(animation, out, in)
#define RtAnimKeyFrameInterpolate(animation, out, in1, in2, time) RtAnimKeyFrameInterpolateMacro(animation, out, in1, in2, time)
#define RtAnimKeyFrameBlend(animation, out, in1, in2, alpha) RtAnimKeyFrameBlendMacro(animation, out, in1, in2, alpha)
#define RtAnimKeyFrameAddTogether(animation, out, in1, in2) RtAnimKeyFrameAddTogetherMacro(animation, out, in1, in2)
#endif

	extern RtAnimInterpolator *RtAnimInterpolatorCreateSubInterpolator(RtAnimInterpolator *parentAnim, int startNode, int numNodes, int maxKeyFrameSize);
	extern int RtAnimInterpolatorBlendSubInterpolator(RtAnimInterpolator *outAnim, RtAnimInterpolator *inAnim1, RtAnimInterpolator *inAnim2, float alpha);
	extern int RtAnimInterpolatorAddSubInterpolator(RtAnimInterpolator *outAnim, RtAnimInterpolator *mainAnim, RtAnimInterpolator *subAnim);
#ifdef    __cplusplus
}
#endif

#endif