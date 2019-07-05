#pragma once

#include "vcclasses.h"

class CCutsceneObjectHack : public CCutsceneObject
{
public:
	static bool initialise();

	void RenderHijack();
};
