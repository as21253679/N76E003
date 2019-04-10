#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

#define TH0_INIT        0xFC //5.0ms@XTAL=12MHz, Period = (10.85/2) ms@XTAL=22.1184MHz
#define TL0_INIT        0x0F
#define TH1_INIT        0xE0 //2.5ms@XTAL=12MHz, Period = (5.425/2) ms@XTAL=22.1184MHz
#define TL1_INIT        0x00
int count=0,count2=0;

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

void Timer1_ISR (void) interrupt 3          //interrupt address is 0x001B
{
	TH1 = TH1_INIT;
	TL1 = TL1_INIT;   
	
	if(count2>10000)
	{
		P11 = ~P11;															// GPIO toggle when interrupt
		count2=0;
	}
	count2++;
}

void Initial_Timer0(void)
{
	TIMER0_MODE0_ENABLE;                        //Timer 0 mode configuration
	clr_T0M;
	TH0 = TH0_INIT;
	TL0 = TL0_INIT;
	set_ET0;                                    //enable Timer0 interrupt
	set_TR0;                                    //Timer0 run
}

void Initial_Timer1(void)
{
	TIMER1_MODE0_ENABLE;                        //Timer 1 mode configuration
	clr_T1M;
	TH1 = TH1_INIT;
	TL1 = TL1_INIT;
	set_ET1;                                    //enable Timer1 interrupt
	set_TR1;                                    //Timer1 run
}

void main (void)
{
	TMOD = 0XFF;
	Set_All_GPIO_Quasi_Mode;

	Initial_Timer0();
	//Initial_Timer1();
	set_EA;                                     //enable interrupts

  while(1);
}
