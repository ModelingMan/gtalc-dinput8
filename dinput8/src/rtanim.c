#include "renderware.h"
#include "rtanim.h"

RtAnimAnimation *RtAnimAnimationStreamRead(void *stream)
{
	RtAnimAnimation *pAnimation = NULL;
	RwInt32 version;
	RwInt32 typeID, numFrames, flags;
	RwReal duration;

	if (RwStreamRead(stream, &version, sizeof(version)) == 0)
		return NULL;

	if (version != rtANIMSTREAMCURRENTVERSION)
		return NULL;

	if (RwStreamRead(stream, &typeID, sizeof(typeID)) == 0)
		return NULL;

	if (RwStreamRead(stream, &numFrames, sizeof(numFrames)) == 0)
		return NULL;

	if (RwStreamRead(stream, &flags, sizeof(flags)) == 0)
		return NULL;

	if (RwStreamRead(stream, &duration, sizeof(duration)) == 0)
		return NULL;

	pAnimation = RtAnimAnimationCreate(typeID, numFrames, flags, duration);

	pAnimation->interpInfo->keyFrameStreamReadCB(stream, pAnimation);

	return pAnimation;
}

RwBool RtAnimInterpolatorAddAnimTime(RtAnimInterpolator *anim, RwReal time)
{
	RtAnimInterpolator *interp = anim;

	if (time > 0.0f)
	{
		RwBool callLoopCB = FALSE;
		RwBool callAnimCB = FALSE;
		RwReal currentTime = interp->currentTime + time;
		RwReal duration = interp->pCurrentAnim->duration;
		RwReal animCallBackTime = interp->animCallBackTime;
		RtAnimAnimation *pCurrentAnim = interp->pCurrentAnim;
		void *pEndofFrames;

		if (interp->currentTime < animCallBackTime && currentTime >= animCallBackTime)
			callAnimCB = TRUE;

		interp->currentTime = currentTime;

		if (currentTime > duration)
		{
			while (currentTime > duration)
			{
				currentTime -= duration;
				callAnimCB |= (currentTime >= animCallBackTime);
			}

			callLoopCB = TRUE;
			RtAnimInterpolatorSetCurrentAnim(anim, interp->pCurrentAnim);
			interp->currentTime = currentTime;
		}
		else
		{
			callLoopCB = FALSE;
		}

		if (!interp->pNextFrame)
		{
			RwReal saveTime = interp->currentTime;
			RtAnimInterpolatorSetCurrentAnim(interp, interp->pCurrentAnim);
			interp->currentTime = saveTime;
		}

		pEndofFrames = (RwUInt8 *)pCurrentAnim->pFrames + pCurrentAnim->numFrames * pCurrentAnim->interpInfo->keyFrameSize;

		if (interp->pNextFrame < pEndofFrames)
		{
			do
			{
				RwInt32 frameCounter = 0;
				RtAnimInterpFrameHeader *prevFrame = (RtAnimInterpFrameHeader *)interp->pNextFrame;
				RtAnimInterpFrameHeader *nextFrame = NULL;

				if (!(prevFrame->keyFrame1->time <= currentTime))
					break;

				do
				{
					nextFrame = (RtAnimInterpFrameHeader *)rtANIMGETINTERPFRAME(interp, frameCounter++);
					if (frameCounter >= interp->numNodes)
						frameCounter = 0;
				} while (nextFrame->keyFrame2 != prevFrame->keyFrame1);

				nextFrame->keyFrame1 = nextFrame->keyFrame2;
				nextFrame->keyFrame2 = interp->pNextFrame;
				interp->pNextFrame = (RwUInt8 *)interp->pNextFrame + interp->currentKeyFrameSize;
			} while (interp->pNextFrame < pEndofFrames);
		}

		if (interp->numNodes > 0)
		{
			RwInt32 nodeCounter = 0;
			do
			{
				RtAnimInterpFrameHeader *frame = (RtAnimInterpFrameHeader *)rtANIMGETINTERPFRAME(interp, nodeCounter++);
				RtAnimKeyFrameInterpolate(interp, frame, frame->keyFrame1, frame->keyFrame2, interp->currentTime);
			} while (nodeCounter < interp->numNodes);
		}

		if (callAnimCB
			&& interp->pAnimCallBack
			&& !interp->pAnimCallBack(interp, interp->pAnimCallBackData))
			interp->pAnimCallBack = NULL;

		if (callLoopCB
			&& interp->pAnimLoopCallBack
			&& !interp->pAnimLoopCallBack(interp, interp->pAnimLoopCallBackData))
			interp->pAnimLoopCallBack = NULL;
	}

	return TRUE;
}