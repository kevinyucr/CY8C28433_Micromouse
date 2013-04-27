#include "nav.h"

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

	if (adcButtonPressed)
	{
		
		Nav_BasicWander1();
	}

}

void Nav_CommandListFollower(char list[], char count)
{
	static char index = 0;
	if (Motion_Ready())
	{
		Motion_SetNextCommand(list[index]);
		++index;
		if (index == count) index = 0;
	}
}

void Nav_BasicWander1(void)
{
	// Go forward. Turn when blocked, prefering left.
	if (Motion_Done())
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
