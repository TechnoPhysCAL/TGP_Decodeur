
#ifndef Decodeur_h
#define Decodeur_h

#include "Stream.h"

/***********************/
// Definition des formats
#define BINAIRE 2
#define DECIMAL 10
#define HEXA 16


/******************************************************************************
 * Definitions
 ******************************************************************************/
class Decodeur
{

public:
	Decodeur(Stream *stream, char separateur = ' ', char finDeMessage = '\n');

	void setSeparateur(char);
	char getSeparateur();
	void setFinDeMessage(char);
	char getFinDeMessage();

	bool refresh();
	bool isAvailable();
	int getArgCount();
	char getCommand();
	String getCommandString();
	float getArg(int, unsigned int base=DECIMAL);
	String getArgString(int);
	String getMessage();

private:
	void lireBuffer();
	void updateArgCount();
	float convertirArg(String p,unsigned int base);
	int HexaToDecimal(const char *Hexa);
	String _message;	// Buffer pour emmagasiner le dernier message reçu
	int _NbArg;			// Variable pour le nombre d'arguments contenu dans le message
	char _separateur;	// Caractère de séparation dans le message
	char _finDeMessage; // Caractère de fin attendu dans le message
	int _base;			// Variable pour contenir la base numérique (Entier, flottant ou hexadécimal)
	Stream *_MyStream;	// Pointeur pour permettre de sélectionner l'objet de communication Stream
};

#endif
