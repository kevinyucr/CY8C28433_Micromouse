#include "ui.h"

void LED_Init(void)
{
	LED_All_Off();
}
                
void LED_ShowWalls(void)
{
	LED_All_Off();
	if (ADC_FilteredLeftWallExists)  LED_Left_On();
	if (ADC_FilteredFrontWallExists) LED_Front_On();
	if (ADC_FilteredRightWallExists) LED_Right_On();
}
				
void Debug_Init(void)
{
	TX8_BT_Start(TX8_BT_PARITY_NONE);
	
}

void Debug_Update(void)
{
	int debug_regs[5];
	char str[7];
	unsigned char i;
	
	M8C_DisableGInt;
	debug_regs[0] = encoderCurrentCount.left;
	debug_regs[1] = encoderCurrentCount.right;
	debug_regs[2] = adcIRFront;
	debug_regs[3] = adcIRLeft;
	debug_regs[4] = adcIRRight;
	M8C_EnableGInt;
	
	for (i = 0; i < 5; ++i)
	{
		itoa(str, debug_regs[i], 10);
		TX8_BT_PutString(str);
		TX8_BT_PutChar(' ');
	}
	TX8_BT_PutCRLF();
}