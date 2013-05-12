#include "adc.h"

// Stores last dark value reading
unsigned int adcIRLeftDark;
unsigned int adcIRRightDark;
unsigned int adcIRFrontDark;

// Stores last offset-corrected reading
unsigned int adcIRLeft;
unsigned int adcIRRight;
unsigned int adcIRFront;

unsigned int adcUser;

// stores a queue of bits that each represent an raw boolean wall reading
// new readings get shifted in the left
// used for hysterisis on the wall true/false readings
unsigned char adcIRFrontFilterQueue;
unsigned char adcIRLeftFilterQueue;
unsigned char adcIRRightFilterQueue;
unsigned char adcFilteredWallState;

unsigned char adcGood;
unsigned char adcButtonPressed;
 
//unsigned int adcSideCenterDistance;
//unsigned int adcFrontCenterDistance;

void ADC_Init(void)
{
	IR_Emitter_Off();
	
	adcButtonPressed = 0;

	adcIRFrontFilterQueue = 0;
	adcIRLeftFilterQueue = 0;
	adcIRRightFilterQueue = 0;
	adcFilteredWallState = 0;
	
	SAR10_EnableInt(); // Enable SAR10 interrupt
	SAR10_Start();     // Power on SAR10 block
}

void ADC_Update(void)
{
	if (IR_Emitter_Powered)
	{
		// ------------ Read reflected light levels ------------
		
		SAR10_SetADCChannel(ADC_CHAN_IR_FRONT);
		SAR10_Trigger();                     // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);  // Wait while data is not ready
		adcIRFront = SAR10_iGetData();       // Read result
		adcIRFront -= adcIRFrontDark;        // Correct reading for ambient lighting
		
		SAR10_SetADCChannel(ADC_CHAN_IR_LEFT);
		SAR10_Trigger();                     // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);  // Wait while data is not ready
		adcIRLeft = SAR10_iGetData();        // Read result
		adcIRLeft -= adcIRLeftDark;          // Correct reading for ambient lighting
		
		SAR10_SetADCChannel(ADC_CHAN_IR_RIGHT);
		SAR10_Trigger();                     // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);  // Wait while data is not ready
		adcIRRight = SAR10_iGetData();       // Read result
		adcIRRight -= adcIRRightDark;        // Correct reading for ambient lighting
		
		SAR10_SetADCChannel(ADC_CHAN_USER);
		SAR10_Trigger();                     // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);  // Wait while data is not ready
		adcUser = SAR10_iGetData();          // Read result
		
		if (adcUser < 10) adcButtonPressed = 1;
		
		if (adcIRLeft > 1023) adcIRLeft = 0;
		if (adcIRFront > 1023) adcIRFront = 0;
		if (adcIRRight > 1023) adcIRRight = 0;
		
		IR_Emitter_Off();
		/*
		//------------ Perform hysteresis ------------
		adcIRFrontFilterQueue <<= 1;
		adcIRLeftFilterQueue  <<= 1;
		adcIRRightFilterQueue <<= 1;
		adcIRFrontFilterQueue |= ADC_FrontWallExists;
		adcIRLeftFilterQueue  |= ADC_LeftWallExists;
		adcIRRightFilterQueue |= ADC_RightWallExists;
		
		// if each filtering queue has 8 consecutive 1's or 0's set the appropriate
		// filtered reading flag.
		if (adcIRFrontFilterQueue == 0xFF) { adcFilteredWallState |= ADC_MASK_FRONT; }
		else if (adcIRFrontFilterQueue == 0x00) { adcFilteredWallState &= ~ADC_MASK_FRONT; }
		
		if (adcIRLeftFilterQueue == 0xFF) { adcFilteredWallState |= ADC_MASK_LEFT; }
		else if (adcIRLeftFilterQueue == 0x00) { adcFilteredWallState &= ~ADC_MASK_LEFT; }
		
		if (adcIRRightFilterQueue == 0xFF) { adcFilteredWallState |= ADC_MASK_RIGHT; }
		else if (adcIRRightFilterQueue == 0x00) { adcFilteredWallState &= ~ADC_MASK_RIGHT; }
		*/
		//LED_ShowWalls();
	}
	else
	{	
		//------------ Read ambient light levels ------------
		
		SAR10_SetADCChannel(ADC_CHAN_USER);
		SAR10_Trigger();                      // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);   //Wait while data is not ready
		adcUser = SAR10_iGetData();           // Read result
	
		SAR10_SetADCChannel(ADC_CHAN_IR_FRONT);
		SAR10_Trigger();                      // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);   //Wait while data is not ready
		adcIRFrontDark = SAR10_iGetData();    // Read result
		adcIRFrontDark += ADC_OFFSET_IR_FRONT;// Apply offset
		
		SAR10_SetADCChannel(ADC_CHAN_IR_LEFT);
		SAR10_Trigger();                      // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);   //Wait while data is not ready
		adcIRLeftDark = SAR10_iGetData();     // Read result
		adcIRLeftDark += ADC_OFFSET_IR_LEFT;  // Apply offset
		
		SAR10_SetADCChannel(ADC_CHAN_IR_RIGHT);
		SAR10_Trigger();                      // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);   //Wait while data is not ready
		adcIRRightDark = SAR10_iGetData();    // Read result
		adcIRRightDark += ADC_OFFSET_IR_RIGHT;// Apply offset
		
		IR_Emitter_On();
		
		adcGood = 1;
	}
}

// ------------ utility algos ------------

#define swap(a, b, temp) temp = a; \
                         a = b; \
						 b = temp;
