#ifndef COMMAND_DECODER_H
#define COMMAND_DECODER_H
#include "decode_tokens.h"
#include "servo.h"

class Uart_Decoder : private Decoder {
public:
    Uart_Decoder(Servo &servo) : MyServo(servo) {}
    void Command_Decoder(char * cUart_Message);
private:
    Servo &MyServo;
};
	
#endif
