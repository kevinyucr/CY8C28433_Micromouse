#include "ui.h"

//#define DEBUG_BINARY
#define DEBUG_TEXT

void LED_Init(void)
{
	LED_All_Off();
}
                
void LED_ShowWalls(void)
{
	LED_All_Off();
	if (ADC_FrontWallExists) LED_Front_On();
	if (ADC_LeftWallExists) LED_Left_On();
	if (ADC_RightWallExists) LED_Right_On();
}
				
void Debug_Init(void)
{
	TX8_BT_Start(TX8_BT_PARITY_NONE);
	
}

void Debug_PrintRelDirection(MouseRelative d)
{
	if (d == MOUSE_WEST)
	{
		--Mouse_Position;
	}
	else if (d == MOUSE_EAST)
	{
		++Mouse_Position;
	}
	else if (d == MOUSE_NORTH)
	{
		Mouse_Position += MAZE_WIDTH;
	}
	else if (d == MOUSE_SOUTH)
	{
		Mouse_Position -= MAZE_WIDTH;
	}
}	

void Debug_Update(void)
{
	int debug_regs[4];
	char str[7];
	unsigned char i;
	
	M8C_DisableGInt;
	debug_regs[0] = encoderCurrentCount.right;
	debug_regs[1] = adcIRLeft;
	debug_regs[2] = adcIRFront;
	debug_regs[3] = adcIRRight;
	M8C_EnableGInt;
	
	#ifdef DEBUG_BINARY
	TX8_BT_PutChar(0xAB);
	TX8_BT_PutChar(0xCD);
	TX8_BT_PutChar(8);
	TX8_BT_PutChar(0);
	TX8_BT_PutChar(debug_regs[0] & 0x00FF);
	TX8_BT_PutChar(debug_regs[0] >> 8);
	TX8_BT_PutChar(debug_regs[1] & 0x00FF);
	TX8_BT_PutChar(debug_regs[1] >> 8);
	TX8_BT_PutChar(debug_regs[2] & 0x00FF);
	TX8_BT_PutChar(debug_regs[2] >> 8);
	TX8_BT_PutChar(debug_regs[3] & 0x00FF);
	TX8_BT_PutChar(debug_regs[3] >> 8);
	#endif
	#ifdef DEBUG_TEXT
	for (i = 0; i < 5; ++i)
	{
		itoa(str, debug_regs[i], 10);
		TX8_BT_PutString(str);
		TX8_BT_PutChar(' ');
	}
	TX8_BT_PutCRLF();
	#endif
	
	//LED_ShowWalls();
	
	/*
	if (ADC_FrontWallExists)
	{
		TX8_BT_PutSHexInt(adcIRFront);
		TX8_BT_PutCRLF();
	}
	*/
	
	// LEDs for show

}