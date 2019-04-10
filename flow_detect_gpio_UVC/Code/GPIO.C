#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#define TH0_INIT        0xFC //5.0ms@XTAL=12MHz, Period = (10.85/2) ms@XTAL=22.1184MHz
#define TL0_INIT        0x0F
#define TH1_INIT        0xE0 //2.5ms@XTAL=12MHz, Period = (5.425/2) ms@XTAL=22.1184MHz
#define TL1_INIT        0x00
int count=0;

void Initial_Timer0(void)
{
	TIMER0_MODE0_ENABLE;                        //Timer 0 mode configuration
	clr_T0M;
	TH0 = TH0_INIT;
	TL0 = TL0_INIT;
	set_ET0;                                    //enable Timer0 interrupt
	set_TR0;                                    //Timer0 run
}

void Timer0_ISR (void) interrupt 1          //interrupt address is 0x000B
{
	TH0 = TH0_INIT;
	TL0 = TL0_INIT;    

	if(count>10000)
	{
		P12 = ~P12;															// GPIO toggle when interrupt
		count=0;
	}
	count++;
}

void main (void) 
{														
	P07_Input_Mode;
	P12_PushPull_Mode;
	P06_PushPull_Mode;
	
	TMOD = 0XFF;
	Initial_Timer0();
	set_EA;                                     //enable interrupts

	while(1);
}
