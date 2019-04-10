#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

void main (void) 
{														
	P11_Input_Mode;
	P12_PushPull_Mode;
	P13_PushPull_Mode;
	P14_PushPull_Mode;
	P13=1;
	P14=0;
	while(1)
	{
		P12=1;
		Timer0_Delay1ms(300);
		P12=0;
		Timer0_Delay1ms(300);
	}
}
