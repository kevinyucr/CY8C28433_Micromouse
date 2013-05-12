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
		
		//Nav_RandomWander2();
		//Nav_FloodFill2();
		Nav_RightWall();
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

void Nav_RandomWander1(void)
{
	// Go forward. Turn when blocked, picking a random direction
	if (Motion_Done())
	{
		if (!ADC_FrontWallExists)
		{
			Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
		}
		else if (!ADC_LeftWallExists && ADC_RightWallExists)
		{
			Motion_SetNextCommand(MOTION_COMMAND_LEFT90);  // forced left
		}
		else if (ADC_LeftWallExists && !ADC_RightWallExists)  // forced right
		{
			Motion_SetNextCommand(MOTION_COMMAND_RIGHT90);
		}
		else if (ADC_LeftWallExists)  // U-turn only
		{
			Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
		}
		else  // open choice, left or right
		{
			if (Nav_GetRandomBit())
			{
				Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
			}
			else
			{
				Motion_SetNextCommand(MOTION_COMMAND_RIGHT90);
			}
		}
	}	
}

#define L_OPEN (!ADC_LeftWallExists)
#define R_OPEN (!ADC_RightWallExists)
#define F_OPEN (!ADC_FrontWallExists)

void Nav_RandomWander2(void)
{
	// Go forward. Turn when blocked, picking a random direction
	if (Motion_Done() && Maze_IsFlooded())
	{
		if (F_OPEN)
		{
			if (L_OPEN && R_OPEN) // three-way split
			{
				if (Nav_GetRandomBit()) Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
				else
				{
					if (Nav_GetRandomBit()) Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_LEFT90));
				else Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_RIGHT90));
				}
			}
			else if (L_OPEN)
			{
				if (Nav_GetRandomBit()) Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
				else Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_LEFT90));
			}
			else if (R_OPEN)
			{
				if (Nav_GetRandomBit()) Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
				else Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_RIGHT90));
			}
			else Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW); // forward only
		}
		else
		{
			if      ( L_OPEN && !R_OPEN) Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_LEFT90));  // only left
			else if (!L_OPEN &&  R_OPEN) Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_RIGHT90)); // only right
			else if (!L_OPEN && !R_OPEN) Motion_SetNextCommand(MOTION_COMMAND_LEFT90);  // dead end
			else
			{
				if (Nav_GetRandomBit()) Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
				else Motion_SetNextCommand(MOTION_COMMAND_RIGHT90);
			}
		}
	}
}

void Nav_FloodFill2(void)
{
	// Go forward. Turn when blocked, picking a random direction
	if (Motion_Done() && Maze_IsFlooded())
	{
		unsigned char this_value;
		unsigned char min_value;
				
		this_value = mazeFlags[Mouse_Position];
		
		
		if (F_OPEN)
		{
			if (L_OPEN && R_OPEN) // three-way split
			{
				if (mazeRouting[CellInMouseRel(MOUSE_FRONT)] < this_value) Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
				else
				{
					if (mazeRouting[CellInMouseRel(MOUSE_LEFT)] < mazeRouting[CellInMouseRel(MOUSE_RIGHT)]) Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_LEFT90));
					else Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_RIGHT90));
				}
			}
			else if (L_OPEN)
			{
				if (Nav_GetRandomBit()) Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
				else Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_LEFT90));
			}
			else if (R_OPEN)
			{
				if (Nav_GetRandomBit()) Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
				else Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_RIGHT90));
			}
			else Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW); // forward only
		}
		else
		{
			if      ( L_OPEN && !R_OPEN) Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_LEFT90));  // only left
			else if (!L_OPEN &&  R_OPEN) Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_RIGHT90)); // only right
			else if (!L_OPEN && !R_OPEN) Motion_SetNextCommand(MOTION_COMMAND_LEFT90);  // dead end
			else
			{
				if (Nav_GetRandomBit()) Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
				else Motion_SetNextCommand(MOTION_COMMAND_RIGHT90);
			}
		}
	}
}

void Nav_FloodFill(void)
{
	// Go forward. Turn when blocked, picking a random direction
	if (Motion_Done() && Maze_IsFlooded())
	{
		unsigned char this_value;
		unsigned char min_value;
				
		this_value = mazeFlags[Mouse_Position];
		
		if (F_OPEN &&
			mazeRouting[CellInMouseRel(MOUSE_FRONT)] < this_value)
		{
			Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
			TX8_BT_CPutString("NAV: Forward\r\n");
		}	
		else if (L_OPEN &&
			mazeRouting[CellInMouseRel(MOUSE_LEFT)] < this_value)
		{
			Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
			TX8_BT_CPutString("NAV: Left\r\n");
		}	
		else if (R_OPEN &&
			mazeRouting[CellInMouseRel(MOUSE_RIGHT)] < this_value)
		{
			Motion_SetNextCommand(MOTION_COMMAND_RIGHT90);
			TX8_BT_CPutString("NAV: Right\r\n");
		}	
		else  // dead end, turn around
		{
			Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
			TX8_BT_CPutString("NAV: Dead-end\r\n");
		}

	}
}

void Nav_RightWall(void)
{
	if (Motion_Done() && Maze_IsFlooded())
	{
		if (R_OPEN) Motion_SetNextCommand(MOTION_APPEND_FWD(MOTION_COMMAND_RIGHT90));
		else if (F_OPEN) Motion_SetNextCommand(MOTION_COMMAND_FWDFOLLOW);
		else Motion_SetNextCommand(MOTION_COMMAND_LEFT90);
	}
}


const char _navRandomness[] = {0x9a, 0x81, 0x47, 0x6b, 0x81, 0xbe, 0xb0, 0xf0,
                               0xdc, 0x18, 0x4f, 0x44, 0x9f, 0x62, 0xe8, 0x5a,
                               0xda, 0x6a, 0x7e, 0x08, 0x18, 0x22, 0x6f, 0x95,
                               0x2e, 0xbc, 0xa3, 0x91, 0x15, 0xa1, 0x9c, 0xfd};
unsigned char Nav_GetRandomBit(void)
{
	static char seed = 0;
	unsigned char bit = seed & (8-1);
	unsigned char byte = _navRandomness[seed/8];
	++seed;
	//TX8_BT_CPutString("Random byte: ");
	//TX8_BT_PutSHexByte(byte);
	byte >>= bit;
	byte &= 0x01;
	
	
	
	return byte;
}
