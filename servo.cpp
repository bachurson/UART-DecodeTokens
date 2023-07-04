#include <LPC21xx.H>
//#include <cstddef>
#include <string.h>
#include <stdio.h>
#include "servo.h"
#include "stepper.h"
#include "timer_interrupts.h"


#define DETECTOR_bm (1<<10)

extern char ucDestination[100];
	
Servo *g_pServo = NULL;

void Servo::TimerCallback()
{
	if(g_pServo!=NULL)
	{
		g_pServo->States(); //odwoluje sie to obiektu stworzonego w main
	}
   
}

void Servo::Init()
{
	DetectorInit();
	Callib();
}

void Servo::DetectorInit(void){
	IO0DIR=IO0DIR&(~DETECTOR_bm);
}

void Servo::Callib(void)
{
	eState = CALLIB;
	while(eState==CALLIB){}
}

enum DetectorState Servo::eReadDetector()
{
  if ((IO0PIN & DETECTOR_bm) == 0) 
	{
    return ACTIVE;
  }
	else
	{
		return INACTIVE;
	}
}


void Servo::GoTo(unsigned int uiPosition)
{
	eState=IN_PROGRESS;
	uiDesiredPosition = uiPosition;
	while(eState==IN_PROGRESS){}
}

void Servo::CompareString(char * ucDestination){
	if(strcmp("callib", ucDestination)==0){
		Callib();
	}
	else if(strcmp("left", ucDestination)==0){
		Servo::Step(Left);
	}
	else if(strcmp("right", ucDestination)==0)
	{
		Servo::Step(Right);
	}
}



void Servo::Step(enum Step Direction){
	eState=IN_PROGRESS;
	if(Direction==Left)
	{
		if(uiCurrentPosition<6){
			uiCurrentPosition=48+uiCurrentPosition;
		}
		uiDesiredPosition=uiCurrentPosition-6;
	}
	else if(Direction==Right)
	{
		uiDesiredPosition=uiCurrentPosition+6;
	}
	while(eState==IN_PROGRESS){}
}


void Servo::States(void)
{	
	switch(eState)
			{			
				case CALLIB:
					if(eReadDetector() == INACTIVE) 
					{
						if(uiCurrentPosition>17 | uiCurrentPosition==0){
							StepRight();
						}
						else{
							StepLeft();
						}
					} 
					else
					{
						uiCurrentPosition=0;
						uiDesiredPosition=0;
						eState=IDLE;
					}
					break;
			
					
				case IDLE: 	
					if(uiCurrentPosition==uiDesiredPosition){}
					
					else
					{
						eState=IN_PROGRESS;
					}
						
					break;
					
			
				case IN_PROGRESS: 
					if(uiCurrentPosition>uiDesiredPosition)
					{
						StepLeft();
						uiCurrentPosition--;
					}
					else if(uiCurrentPosition<uiDesiredPosition)
					{
						StepRight();
						uiCurrentPosition++;
					}
					else
					{
						eState=IDLE;
					}
					break;
					
			}
}


