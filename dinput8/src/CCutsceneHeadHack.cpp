#include "CCutsceneHeadHack.h"
#include "vcclasses.h"
#include "renderware.h"
#include "RtAnim.h"
#include "Globals.h"

struct FindFrameFromNameData
{
	const char *name;
	void *out;
};

//*****************************************************************************

RwFrame *FindFrameFromNameCB(RwFrame *frame, void *data)
{
	FindFrameFromNameData *findData = (FindFrameFromNameData *)data;
	const char *frameName = VCGlobals::GetFrameNodeName(frame);
	if (VCGlobals::strcmp(frameName, findData->name) == 0)
	{
		findData->out = frame;
		return 0;
	}

	return RwFrameForAllChildren(frame, FindFrameFromNameCB, data);
}

//*****************************************************************************

CCutsceneHeadHack::CCutsceneHeadHack(CObject *body)
: CCutsceneObject()
{
	FindFrameFromNameData data;
	data.name = "Head";
	data.out = 0;
	RwFrameForAllChildren(
		RpClumpGetFrame(body->clump), FindFrameFromNameCB, &data);

	CutsceneHeadHackLink::Add(
		this, body, reinterpret_cast<RwFrame *>(data.out));
}

//*****************************************************************************

CCutsceneHeadHack::~CCutsceneHeadHack()
{
	CutsceneHeadHackLink::Remove(this);
}

//*****************************************************************************

void CCutsceneHeadHack::CreateRwObject()
{
	CEntity::CreateRwObject();

	RpHAnimHierarchy *hierarchy = VCGlobals::GetFrameHierarchy(clump);
	RpClumpForAllAtomics(clump, VCGlobals::SetAtomicHierarchyCB, hierarchy);
}

//*****************************************************************************

void CCutsceneHeadHack::DeleteRwObject()
{
	CEntity::DeleteRwObject();
}

//*****************************************************************************

void CCutsceneHeadHack::ProcessControl()
{
	CutsceneHeadHackLink *headHack = CutsceneHeadHackLink::Get(this);

	CEntity::UpdateRpHAnim();
	CEntity::UpdateRwFrame();

	RpHAnimHierarchy *hier = 
		VCGlobals::GetAnimHierarchyFromSkinClump(headHack->body->clump);
	int index = RpHAnimIDGetIndex(hier, VCGlobals::ConvertPedNode2BoneTag(2));
	RwMatrix *matrices = RpHAnimHierarchyGetMatrixArray(hier);

	placeable.matrix.SetRotateY(1.5707964f); // M_PI/2
	placeable.matrix = &matrices[index] * placeable.matrix;

	RwV3d scale = { 0 };
	RwMatrixScale(&matrices[index], &scale, rwCOMBINEPRECONCAT);

	hier = RpSkinAtomicGetHAnimHierarchy(VCGlobals::GetFirstAtomic(clump));
	RtAnimInterpolatorAddAnimTimeASM(
		hier->currentAnim, CTimer::ms_fTimeStepNonClipped / 50);

	CPhysical::ProcessControl();
}

//*****************************************************************************

void CCutsceneHeadHack::Render()
{
	CutsceneHeadHackLink *headHack = CutsceneHeadHackLink::Get(this);

	RpHAnimHierarchy *hier = 
		VCGlobals::GetAnimHierarchyFromSkinClump(headHack->body->clump);
	int index = RpHAnimIDGetIndex(hier, VCGlobals::ConvertPedNode2BoneTag(2));
	RwMatrix *matrices = RpHAnimHierarchyGetMatrixArray(hier);

	placeable.matrix.SetRotateY(1.5707964f); // M_PI/2
	placeable.matrix = &matrices[index] * placeable.matrix;

	RwV3d scale = { 0 };
	RwMatrixScale(&matrices[index], &scale, rwCOMBINEPRECONCAT);

	CEntity::UpdateRwFrame();
	CEntity::UpdateRpHAnim();

	CObject::Render();
}

//*****************************************************************************

void CCutsceneHeadHack::PlayAnimation(const char *name)
{
	char animFilename[13];
	VCGlobals::strcpy(animFilename, name);
	VCGlobals::strcat(animFilename, ".anm");

	unsigned int offset, size;
	if (!CCutsceneMgr::ms_pCutsceneDir->FindItem(animFilename, offset, size))
		return;

	void *stream = 
		RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, "ANIM\\CUTS.IMG");

	CStreaming::MakeSpaceFor(size << 11);

	RwStreamSkip(stream, offset << 11);

	if (RwStreamFindChunk(stream, rwID_HANIMANIMATION, 0, 0))
	{
		RtAnimAnimation *anim = RtAnimAnimationStreamRead(stream);
		if (anim)
		{
			RpHAnimHierarchy *frameHier = VCGlobals::GetFrameHierarchy(clump);
			RpClumpForAllAtomics(
				clump, VCGlobals::SetAtomicHierarchyCB, frameHier);
			RtAnimInterpolatorSetCurrentAnim(frameHier->currentAnim, anim);
		}
	}

	RwStreamClose(stream, 0);
}

CutsceneHeadHackLink *CutsceneHeadHackLink::ms_LinkList = nullptr;

//*****************************************************************************

CutsceneHeadHackLink::CutsceneHeadHackLink()
: 
m_head(nullptr),
m_next(nullptr), 
m_prev(nullptr), 
body(nullptr), 
headFrame(nullptr)
{

}

//*****************************************************************************

CutsceneHeadHackLink::~CutsceneHeadHackLink()
{
}

//*****************************************************************************

CutsceneHeadHackLink *CutsceneHeadHackLink::Add(
	CCutsceneHeadHack *t_head, CObject *t_body, RwFrame *t_headFrame)
{
	if (ms_LinkList == nullptr)
		ms_LinkList = new CutsceneHeadHackLink();

	CutsceneHeadHackLink *newLink = ms_LinkList;

	if (newLink->m_head == nullptr) {
		newLink->m_head = t_head;
		newLink->body = t_body;
		newLink->headFrame = t_headFrame;
	}
	else {
		CutsceneHeadHackLink *lastLink = newLink;

		while (lastLink->m_next)
			lastLink = lastLink->m_next;

		newLink = new CutsceneHeadHackLink();
		newLink->m_head = t_head;
		newLink->body = t_body;
		newLink->headFrame = t_headFrame;
		newLink->m_prev = lastLink;

		lastLink->m_next = newLink;
	}

	return newLink;
}

//*****************************************************************************

void CutsceneHeadHackLink::Remove(CutsceneHeadHackLink *link)
{
	// If link being removed is the first link then make first link the 
	// next link (nullptr if no more links)
	if (link == ms_LinkList)
		ms_LinkList = link->m_next;

	// If there is a previous link then make it's next link equal to this
	// link's next (can be nullptr)
	if (link->m_prev != nullptr)
		link->m_prev->m_next = link->m_next;

	// If there is a next link then make it's previous link equal to this
	// link's previous (can be nullptr)
	if (link->m_next != nullptr)
		link->m_next->m_prev = link->m_prev;

	link->m_next = nullptr;
	link->m_prev = nullptr;

	// This will delete the ms_LinkList pointer when it is the only
	// remaining link. ms_LinkList will be nullptr after the first 
	// condition above executes true and link->m_next == nullptr
	delete link;
}

//*****************************************************************************

void CutsceneHeadHackLink::Remove(CCutsceneHeadHack *head)
{
	CutsceneHeadHackLink *link = Get(head);
	if (link != nullptr)
		Remove(link);
}

//*****************************************************************************

CutsceneHeadHackLink *CutsceneHeadHackLink::Get(CCutsceneHeadHack *head)
{
	CutsceneHeadHackLink *link = ms_LinkList;

	while (link && link->m_head != head)
		link = link->m_next;

	return link;
}
