#include "command_decoder.h"


void Uart_Decoder::Command_Decoder(char * cUart_Message){
	ucTokenNr = 0;
	DecodeMsg(cUart_Message);
	if((ucTokenNr!=0) && (asToken[0].eType == KEYWORD)){
		switch(asToken[0].uValue.eKeyword){
			case CALL:
				MyServo.Callib();
				break;
			case LEFT:
				MyServo.Step(Servo::Left);
				break;
			case RIGHT:
				MyServo.Step(Servo::Right);
				break;
			case GOTO:
				MyServo.GoTo(asToken[1].uValue.uiNumber);
				break;
			default:
				break;
		}
	}
}

