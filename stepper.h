#ifndef STEPPER_H
#define STEPPER_H
#include "led.h"

//enum Step{Left, Right};

class Stepper : public Led
{
	public:
		void StepLeft(void);
		void StepRight(void);
		enum Step{Left, Right};
	private:
		unsigned char ucLedCtr;	
		void Step(enum Step Direction);
};

#endif
