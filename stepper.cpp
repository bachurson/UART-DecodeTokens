#include "stepper.h"
#include <LPC21xx.H>

#define LED0_bm 1<<16
#define LED1_bm 1<<17 
#define LED2_bm 1<<18 
#define LED3_bm 1<<19


void Stepper::Step(enum Step Direction)
{

	if (Direction==Left)
	{
		ucLedCtr++;
	}
	else if (Direction==Right)
	{
		ucLedCtr--;
	}
		On(ucLedCtr%4);
}

void Stepper::StepLeft(void)
{
	Step(Left);
}

void Stepper::StepRight(void)
{
	Step(Right);
}

