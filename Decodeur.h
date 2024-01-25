
#ifndef Decodeur_h
#define Decodeur_h

#include "Stream.h"

/***********************/
// Definition des formats
#define ENTIER 0
#define HEXA 1
#define FLOTTANT 2

/******************************************************************************
 * Definitions
 ******************************************************************************/
class Decodeur
{

public:
	Decodeur(Stream *stream, char separateur = ' ', char finDeMessage = '\n', int base = FLOTTANT);
	void setSeparateur(char);
	char getSeparateur();
	void setFinDeMessage(char);
	char getFinDeMessage();
	void setBase(int);
	int getBase();

	bool available();
	int getArgCount();
	char getCommand();
	String getCommandString();
	float getArg(int);
	String getArgString(int);
	String getMessage();

private:
	bool lireBuffer();
	void updateArgCount();
	float convertirArg(String p);
	int HexaToDecimal(const char *Hexa);
	String _message;	// Buffer pour emmagasiner le dernier message reçu
	int _NbArg;			// Variable pour le nombre d'arguments contenu dans le message
	char _separateur;	// Caractère de séparation dans le message
	char _finDeMessage; // Caractère de fin attendu dans le message
	int _base;			// Variable pour contenir la base numérique (Entier, flottant ou hexadécimal)
	Stream *_MyStream;	// Pointeur pour permettre de sélectionner l'objet de communication Stream
};

#endif
