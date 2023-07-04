#include "servo.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include "uart.h"
#include "command_decoder.h"


int main ()
{
	extern Servo *g_pServo;
	Timer0Interrupts_Init(1000000/50, &Servo::TimerCallback);
	Servo MyServo;
	Keyboard MyKeyboard;
	g_pServo = &MyServo;
	MyServo.Init();
	Uart_Decoder MyUart_Decoder(MyServo);
	UART_InitWithInt(9600);
	char ucDestination[RECIEVER_SIZE];
	extern char cReceivedChar;
	
	while(1)
	{
		if(eReciever_GetStatus()==READY)
		{
			Reciever_GetStringCopy(ucDestination);
			MyUart_Decoder.Command_Decoder(ucDestination);
		}
		
		switch(MyKeyboard.eRead())
		{
			case BUTTON_1 :
				MyServo.GoTo(12);
				break;
			case BUTTON_2 :  
				MyServo.GoTo(24);
				break;
			case BUTTON_3 :
				MyServo.GoTo(36);
				break;
			case BUTTON_4 :
				MyServo.Callib();
				break;
			default:
				break;	
		}
	}
}
