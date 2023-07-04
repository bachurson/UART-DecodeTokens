#include "strings.h"
#ifndef DECODE_TOKENS_H
#define DECODE_TOKENS_H
#define NULL 0
#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_STRING_LTH 6
#define MAX_KEYWORD_NR 4

enum TokenType {KEYWORD, NUMBER, STRING};
enum KeywordCode {CALL, LEFT, RIGHT, GOTO};
enum Stan{TOKEN, DELIMITER};

union TokenValue
{
	enum KeywordCode eKeyword; 
	unsigned int uiNumber; 
	char* pcString;
};

struct Token
{
	enum TokenType eType; 
	union TokenValue uValue;
};


struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1]; 
};


class Decoder
{
	private:
		unsigned char ucFindTokensInString(char *pcCommand);
		enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode);
		void DecodeTokens(void);
	protected:
		unsigned char ucTokenNr;
		void DecodeMsg(char *pcCommand);
		struct Token asToken[MAX_TOKEN_NR];	
};
	
#endif

