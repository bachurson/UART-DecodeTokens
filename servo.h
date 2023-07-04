#ifndef SERVO_H
#define SERVO_H
#include "stepper.h"

enum ServoState {CALLIB, IDLE, IN_PROGRESS, OFFSET};
enum DetectorState {ACTIVE, INACTIVE};

class Servo : public Stepper
{
	public:
		void Init(void);
		void Callib(void);
		void GoTo(unsigned int uiPosition);
		static void TimerCallback();
		void CompareString(char * ucDestination);
		void Step(enum Step Direction);
		
	private:
		enum ServoState eState;
		enum DetectorState eReadDetector();
		unsigned int uiCurrentPosition;
		unsigned int uiDesiredPosition;
		void DetectorInit(void);
		void States(void);
};

#endif 
