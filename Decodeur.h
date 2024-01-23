
#ifndef Decodeur_h
#define Decodeur_h

#include "Stream.h"

/***********************/
//Definition des formats
#define ENTIER 0
#define HEXA 1
#define FLOTTANT 2

/******************************************************************************
* Definitions
******************************************************************************/
class Decodeur
{

public:
	Decodeur(Stream *stream);
	Decodeur(Stream *stream, char separateur, int base);
	bool available();
	int getArgCount();
	char getCommand();
	String getCommandString();
	float getArg(int);
	String getArgString(int);

private:
	bool lireBuffer();
	void updateArgCount();
	float convertirArg(String p, int base);
	int HexaToDecimal(const char *Hexa);
	
};

#endif
