#include "motion.h"

extern SEncCount motorSetpoint;

char motionCommandNext;
char motionCommandCurrent;

int _distanceTraveled;

void Motion_Init(void)
{
	motionCommandNext = MOTION_COMMAND_NONE;
	motionCommandCurrent = MOTION_COMMAND_NONE;
}

void Motion_Update(void)
{
	if (motionCommandCurrent == MOTION_COMMAND_NONE)
	{
		// If not currently running a command, load next command.
		// There is no next command, nothing happens and mouse maintains position
		motionCommandCurrent = MOTION_FIRST(motionCommandNext);
		motionCommandNext = MOTION_SECOND(motionCommandNext);
		
		Motor_Center();
		
		// These should only run once when the command is first loaded
		if (motionCommandCurrent == MOTION_COMMAND_NONE)
		{
			// Center setpoint and just stay in one place
		}
		else if (motionCommandCurrent == MOTION_COMMAND_FWD)
		{
			// setup for Forward
			
		}
		else if (motionCommandCurrent == MOTION_COMMAND_LEFT90)
		{
			// setup for Left90
		}
		else if (motionCommandCurrent == MOTION_COMMAND_RIGHT90)
		{
			// setup for Right90
		}
	}
	
	// Run movement commands if they are active
	if (motionCommandCurrent == MOTION_COMMAND_FWD)   //------------------------------------
	{
		_Motion_CommandForward();
	}
	else if (motionCommandCurrent == MOTION_COMMAND_LEFT90)  //------------------------------------
	{
		_Motion_CommandLeft90();
	}
	else if (motionCommandCurrent == MOTION_COMMAND_RIGHT90)  //------------------------------------
	{
		_Motion_CommandRight90();
	}
	else if (motionCommandCurrent == MOTION_COMMAND_FWDWAIT)  //------------------------------------
	{
		_Motion_CommandForwardWait();
	}
	else if (motionCommandCurrent == MOTION_COMMAND_FWDFOLLOW) //------------------------------------
	{
		_Motion_CommandForwardFollow();
	}
}

void Motion_MapAtCurrPos(void)  // This should really go in the Maze module...
{
	CompassRelative walldir;
	TX8_BT_CPutString("Mapped walls: ");
	
	if (ADC_FrontWallExists)
	{
		walldir = MouseToCompass(MOUSE_FRONT, Mouse_Direction);
		Maze_PrintCompass(walldir);
		Maze_AddWall(Mouse_Position, CompassToWallFlags(walldir));
	}
	if (ADC_LeftWallExists)
	{
		walldir = MouseToCompass(MOUSE_LEFT, Mouse_Direction);
		Maze_PrintCompass(walldir);
		Maze_AddWall(Mouse_Position, CompassToWallFlags(walldir));
	}
	if (ADC_RightWallExists)
	{
		walldir = MouseToCompass(MOUSE_RIGHT, Mouse_Direction);
		Maze_PrintCompass(walldir);
		Maze_AddWall(Mouse_Position, CompassToWallFlags(walldir));
	}
	TX8_BT_PutCRLF();
	
	TX8_BT_CPutString("Mouse Direction: ");
	Maze_PrintCompass(Mouse_Direction);
	TX8_BT_PutCRLF();
}

void _Motion_CommandForward(void)
{
	if (motorSetpoint.right < MOTION_COUNT_CELL)
		{
			motorSetpoint.right += MOTION_BASE_VELOCITY;
			motorSetpoint.left += MOTION_BASE_VELOCITY;
			
			motorSetpoint.left = abs(motorSetpoint.left);
			
			
			
		}
		else
		{
			// Setpoint reached
			motionCommandCurrent = MOTION_COMMAND_NONE;

		}

}

void _Motion_CommandRight90(void)
{
	if (motorSetpoint.left < MOTION_COUNT_ROT90)
	{
		motorSetpoint.left += MOTION_BASE_VELOCITY;
		if (motorSetpoint.left > MOTION_COUNT_ROT90) motorSetpoint.left = MOTION_COUNT_ROT90;
		
		motorSetpoint.right -= MOTION_BASE_VELOCITY;
		if (motorSetpoint.right < -MOTION_COUNT_ROT90) motorSetpoint.right = -MOTION_COUNT_ROT90;
	}
	else
	{
		// Setpoint reached
		motionCommandCurrent = MOTION_COMMAND_NONE;
		
		Mouse_Direction = RotateDirectionRight(Mouse_Direction,1);
		

		TX8_BT_CPutString("Right, Position: ");
		TX8_BT_PutSHexByte(Mouse_Position);
		TX8_BT_PutCRLF();
	}
}

void _Motion_CommandLeft90(void)
{
	if (motorSetpoint.right < MOTION_COUNT_ROT90)
	{
		motorSetpoint.right += MOTION_BASE_VELOCITY;
		if (motorSetpoint.right > MOTION_COUNT_ROT90) motorSetpoint.right = MOTION_COUNT_ROT90;
		
		motorSetpoint.left -= MOTION_BASE_VELOCITY;
		if (motorSetpoint.left < -MOTION_COUNT_ROT90) motorSetpoint.left = -MOTION_COUNT_ROT90;
	}
	else
	{
		// Setpoint reached
		motionCommandCurrent = MOTION_COMMAND_NONE;
		
		Mouse_Direction = RotateDirectionLeft(Mouse_Direction,1);

		TX8_BT_CPutString("Left, Position: ");
		TX8_BT_PutSHexByte(Mouse_Position);
		TX8_BT_PutCRLF();
	}
}

void _Motion_CommandForwardWait(void)
{
	if (motorSetpoint.right < MOTION_COUNT_CELL)
	{
		if (!ADC_FrontWallExists)
		{
			motorSetpoint.right += MOTION_BASE_VELOCITY;
			motorSetpoint.left += MOTION_BASE_VELOCITY;
		
			//motorSetpoint.left = abs(motorSetpoint.left);  // not sure what this does
		}
		
		
	}
	else
	{
		// Setpoint reached
		motionCommandCurrent = MOTION_COMMAND_NONE;
	}

}

void _Motion_CommandForwardFollow(void)
{
	int difference;
// 380
	if ( (adcIRFront >  100 && adcIRFront < 380) ||
	     (adcIRFront <= 100 && motorSetpoint.right < MOTION_COUNT_CELL) )
	{
	
		motorSetpoint.right += MOTION_BASE_VELOCITY;
		motorSetpoint.left += MOTION_BASE_VELOCITY;
	
		LED_All_Off();
		if (ADC_LeftWallExists && ADC_RightWallExists)
		{
			LED_Left_On();
			LED_Right_On();
			motorSetpoint.right -= (adcIRLeft - ADC_WALL_THRESHOLD) / 100;
			motorSetpoint.left -= (adcIRRight - ADC_WALL_THRESHOLD) / 100;
		}
		else if (ADC_LeftWallExists)
		{
			LED_Left_On();
			if (adcIRLeft > 550)
				motorSetpoint.right -= (adcIRLeft - 550) / 50;
			else
				motorSetpoint.left -= (550 - adcIRLeft) / 50;
		}
		else if (ADC_RightWallExists)
		{
			LED_Right_On();
			if (adcIRRight > 550)
				motorSetpoint.left -= (adcIRRight - 550) / 50;
			else
				motorSetpoint.right -= (550 - adcIRRight) / 50;
		}
		
	}
	else
	{
		// Setpoint reached
		motionCommandCurrent = MOTION_COMMAND_NONE;
		
		if (motorSetpoint.right > (MOTION_COUNT_CELL / 2))
		{
			// only change position if the move was "significant"
			// i.e. not a false move
			MoveMouseCompass(MouseToCompass(MOUSE_FRONT, Mouse_Direction));
		
			TX8_BT_CPutString("Forward, Position: ");
			TX8_BT_PutSHexByte(Mouse_Position);
			TX8_BT_PutCRLF();
			TX8_BT_CPutString("  Route: ");
			TX8_BT_PutSHexByte(mazeRouting[Mouse_Position]);
			TX8_BT_PutCRLF();
			

		}
		
		Motion_MapAtCurrPos();
	}

}

