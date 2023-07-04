#include "decode_tokens.h"


struct Keyword asKeywordList[MAX_KEYWORD_NR]=
{
	{CALL,"callib"},
	{LEFT, "left" },
	{RIGHT, "right"},
	{GOTO, "goto" }
};

unsigned char Decoder::ucFindTokensInString(char *pcCommand)
{
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	enum Stan eStan=DELIMITER;

	
	for(ucCharacterCounter=0;;ucCharacterCounter++)
	{
		ucCurrentCharacter=pcCommand[ucCharacterCounter]; 
		switch(eStan)
		{
			case TOKEN:
			{
				if(ucTokenNr==MAX_TOKEN_NR){
					return ucTokenNr;
				}
				else if(ucCurrentCharacter==NULL){
					return ucTokenNr;
				}
				else if(ucCurrentCharacter!=' '){
					eStan=TOKEN;
				}
				else{
					eStan=DELIMITER;
				}
				break;
			}
			case DELIMITER:
			{
				if(ucCurrentCharacter==NULL){
					return ucTokenNr;
				}
				else if(ucCurrentCharacter==' '){ 
					eStan=DELIMITER;
				}
				else{
					eStan=TOKEN;
					asToken[ucTokenNr].uValue.pcString=pcCommand+ucCharacterCounter; 
					ucTokenNr++;
				}
				break;
			}
		}
	}
}



enum Result Decoder::eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode)
{

	unsigned char ucKeywordCounter;
	
	for(ucKeywordCounter=0; ucKeywordCounter< MAX_KEYWORD_NR; ucKeywordCounter++)
	{
		if(EQUAL == eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr))
		{
			*peKeywordCode= asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}	
	
	return ERROR;
}



void Decoder::DecodeTokens(void)
{
	unsigned char ucTokenCounter;
	struct Token *psCurrentToken;
	unsigned int uiTokenValue;
	enum KeywordCode eTokenCode;
	for(ucTokenCounter = 0; ucTokenCounter< ucTokenNr; ucTokenCounter++)
	{
		psCurrentToken = &asToken[ucTokenCounter]; /*bedziemy modyfikowac zawartosc tablicy astoken ale najpierw musimy dostac sie do jej zawartosci poprzez adres*/
		
		if(OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue))
		{
			psCurrentToken->eType=NUMBER;
			psCurrentToken->uValue.uiNumber=uiTokenValue;
		}
		else if(OK == eStringToKeyword(psCurrentToken->uValue.pcString, &eTokenCode)){
			psCurrentToken->eType = KEYWORD;
			psCurrentToken->uValue.eKeyword = eTokenCode;
		}
		else{
			psCurrentToken->eType=STRING;
		}
	}
}


void Decoder::DecodeMsg(char *pcCommand)
{
	ucTokenNr = ucFindTokensInString(pcCommand);
	ReplaceCharactersInString(pcCommand, ' ', NULL);
	DecodeTokens();
}


