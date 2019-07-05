#pragma once

#include "vcclasses.h"

class CCutsceneHeadHack : public CCutsceneObject
{
public:
	CCutsceneHeadHack(CObject *body);
	virtual ~CCutsceneHeadHack();

	virtual void CreateRwObject();
	virtual void DeleteRwObject();

	virtual void ProcessControl();

	virtual void Render();

	void PlayAnimation(const char *name);
};

class CutsceneHeadHackLink
{
private:
	CCutsceneHeadHack *m_head;

	static CutsceneHeadHackLink *ms_LinkList;
	CutsceneHeadHackLink *m_next;
	CutsceneHeadHackLink *m_prev;

public:
	CObject *body;
	RwFrame *headFrame;

	CutsceneHeadHackLink();
	~CutsceneHeadHackLink();

	static CutsceneHeadHackLink *Add(CCutsceneHeadHack *t_head, CObject *t_body, RwFrame *t_headFrame);
	static void Remove(CutsceneHeadHackLink *link);
	static void Remove(CCutsceneHeadHack *head);
	static CutsceneHeadHackLink *Get(CCutsceneHeadHack *head);
};