#ifndef __CSCROLLBARHACK_H__
#define __CSCROLLBARHACK_H__

#include "vcclasses.h"

class CScrollBarHack : public CScrollBar
{
public:
	static bool ms_PortlandComplete, ms_StauntonComplete, ms_ShoresideComplete;

	void Update();

	static char *BridgesMsgDynamic();
	static char *LibertyTunnelMsgDynamic();
	static char *TimeMsgDynamic();
};

#endif
