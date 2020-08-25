
#ifndef Decodeur_h
#define Decodeur_h

#include "Stream.h"

#define _maxComLine 200		//Nombre maximal de caractères reçue pour une commande complète. Ex: w 1 2 3 4 5 => 11 caractères
#define _maxArg 10			//Nombre maximal d'arguments à recevoir suivant la commande
#define _maxCommandeStr 15	//Longueur maximale d'une commande de type string
/***********************/
//Definition des formats
#define ENTIER 0
#define HEXA 1
#define FLOTTANT 2
#define TEXTE 3


/******************************************************************************
* Definitions
******************************************************************************/
class Decodeur{

public:
	Decodeur(Stream *stream);
	Decodeur(Stream *stream,char separateur,int format);
  	bool isAvailable();
  	int getArgCount();
  	char getCommand();
  	float getArg(int);
	//char *getArgStr();

private:
	bool lireBuffer();
	bool decoderCommande();
	float convertirArg(char *p, int base);
	int HexaToDecimal(const char* Hexa);
	void SplitToken(char Buf[], char *Comm, float Arg[], int base);

};

#endif