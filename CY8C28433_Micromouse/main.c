//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "MicromouseModules.h"

void main(void)
{
	// -------------------- Setup --------------------
	
	M8C_EnableGInt; // Enable Global Interrupts
	Encoder_Init(); // encoder.h
	Motor_Init();   // motor.h
	LED_Init();     // ui.h
	Debug_Init();     // ui.h
	ADC_Init();     // adc.h
	Sched_Init();   // sched.h
	Motion_Init();  // motion.h
	Maze_Init();
	
	SleepTimer_Start();
	SleepTimer_EnableInt();

	// ------------------ End Setup ------------------

	SleepTimer_SyncWait(8, SleepTimer_WAIT_RELOAD);
	
	while(1)
	{
		Sched_RunQueue();
	}
}

