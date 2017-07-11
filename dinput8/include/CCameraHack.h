#pragma once

#include "vcclasses.h"

class CCameraHack : public CCamera
{
public:
	static bool initialise();

	static void CamControlHack();
	static void ProcessObbeCinemaCameraCarHack();
};
