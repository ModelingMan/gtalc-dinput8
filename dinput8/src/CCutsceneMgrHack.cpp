#include "CCutsceneMgrHack.h"
#include "Globals.h"
#include "CCutsceneHeadHack.h"

CCutsceneHeadHack *CCutsceneMgrHack::AddCutsceneHead(CObject * body, int index)
{
	CCutsceneHeadHack *head = new CCutsceneHeadHack(body);
	head->SetModelIndex(index);

	CWorld::Add(head);

	CCutsceneMgr::ms_pCutsceneObjects[CCutsceneMgr::ms_numCutsceneObjs++] = head;

	return head;
}

void CCutsceneMgrHack::SetHeadAnim(const char *headAnimName, CCutsceneHeadHack *head)
{
	char animName[21];
	VCGlobals::sprintf(animName, "%s_%s", CCutsceneMgr::ms_cutsceneName, headAnimName);

	head->PlayAnimation(animName);
}
