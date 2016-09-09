#pragma once

#include "vcclasses.h"

class CScrollBarHack : public CScrollBar
{
public:
	void Update();

	static char *BridgesMsgDynamic();
	static char *LibertyTunnelMsgDynamic();
	static char *TimeMsgDynamic();
};
