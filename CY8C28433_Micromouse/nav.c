#include "nav.h"

      char _navCommandIndex = 0;
//const char _navCommandListSize = 8;
//const char _navCommandList[] = {MOTION_COMMAND_FWDWAIT,
//                                MOTION_COMMAND_FWDWAIT,
//							    MOTION_COMMAND_LEFT90,
//								MOTION_COMMAND_LEFT90,
//								MOTION_COMMAND_FWDWAIT,
//								MOTION_COMMAND_FWDWAIT,
//								MOTION_COMMAND_RIGHT90,
//								MOTION_COMMAND_RIGHT90};

//const char _navCommandListSize = 4;
//const char _navCommandList[] = {MOTION_COMMAND_LEFT90,
//								MOTION_COMMAND_LEFT90,
//                                MOTION_COMMAND_RIGHT90,
//							    MOTION_COMMAND_RIGHT90};

const char _navCommandListSize = 1;
const char _navCommandList[] = {MOTION_COMMAND_FWDFOLLOW};
							  
void Nav_Init(void)
{
}

void Nav_Update(void)
{
//  // Follow command list
//	if (Motion_Ready())
//	{
//		Motion_SetNextCommand(_navCommandList[_navCommandIndex]);
//		_navCommandIndex++;
//		if (_navCommandIndex == _navCommandListSize) _navCommandIndex = 0;
//	}

//	// Left wall follower
//	if (Motion_Done() && adcGood)
//	{
//		if (!ADC_LeftWallExists)
//		{
//			Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
//			Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
//		}
//		else if (!ADC_FrontWallExists)
//		{
//			Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
//		}
//		else
//		{
//			Motion_SetNextCommand(MOTION_COMMAND_RIGHT90);
//		}
//			
//	}

	// Go forwarder until blocked
	if (Motion_Done() && adcButtonPressed)
	{
		if (!ADC_FrontWallExists)
		{
			Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
		}
		else if (!ADC_LeftWallExists)
		{
			Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
		}
		else if (!ADC_RightWallExists)
		{
			Motion_SetNextCommand(MOTION_COMMAND_RIGHT90);
		}
		else
		{
			Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
		}
	}
}
