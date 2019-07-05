#pragma once

#include "vcclasses.h"

class CCutsceneHeadHack;

class CCutsceneMgrHack
{
public:
	static CCutsceneHeadHack *AddCutsceneHead(CObject *body, int index);
	static void SetHeadAnim(const char *headAnimName, CCutsceneHeadHack *head);
};
