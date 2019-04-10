#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

int flag=0;

void Interrupt_ISR (void)   interrupt 0
{
	flag=1;
}

void main (void)
{
	int i=0;
  P12_PushPull_Mode;

	set_EPI;							// Enable pin interrupt
	set_EX0;              // Enable interrupt0 & low level trig
  set_EA;               // global enable bit
	
	while(1)
	{
		if(flag)
		{
			for(i=0;i<10;i++)
			{
				clr_GPIO1;
				Timer0_Delay1ms(100);
				set_GPIO1;
				Timer0_Delay1ms(100);
			}
			flag=0;
		}
	}
}

