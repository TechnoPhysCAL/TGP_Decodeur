/****************************************************************
// Librairie Decodeur
//Auteurs : Claude Bouchard
//Date : janvier 2024
//version : 2.0.0
//Description: Permet de lire et décoder des commandes et des
//arguments provenant d'un objet de type Stream, dans un format simplifié
//***************************************************************/
#include "Stream.h"
#include "Decodeur.h"

/***************************************************************
// Déclaration des variables et constantes privées
//***************************************************************/

String _instruction; // Buffer pour emmagasiner les entrées du UART
int _NbArg;			 // Variable pour le nombre d'argument
char _separateur;	 // Séparateur par défaut est un espace
int _base;			 // Variable pour contenir la base
Stream *_MyStream;	 // Pointeur pour permettre de sélectionner le type de communication

/***************************************************************
// Constructeur
//***************************************************************/
Decodeur::Decodeur(Stream *stream)
{
	_MyStream = stream;
	_separateur = ' ';
	_base = ENTIER;
	_NbArg = 0;
	_instruction = "";
}

/****************************************************************
Fonction pour initialiser le décodage du Stream de données.
Permet de configurer aussi le type de séparateur entre chaque
arguments ainsi que la base. La base doit être:
****************************************************************/
Decodeur::Decodeur(Stream *stream, char separateur, int base)
{
	_MyStream = stream;
	_separateur = separateur;
	_base = base;
	_NbArg = 0;
	_instruction = "";
}

/****************************************************************
Fonction pour indiquer si une commande à été reçue.
****************************************************************/
bool Decodeur::available()
{
	return lireBuffer()
}

/****************************************************************
Fonction pour indiquer le nombre d'arguments reçues.
****************************************************************/
int Decodeur::getArgCount()
{
	if (_instruction.length() == 0)
		return 0;
	int decalage = _instruction.indexOf(_separateur, 1);
	if (decalage < 0)
		return 0;
	int nb = 0;
	while (decalage > 0)
	{
		decalage = _instruction.indexOf(_separateur, decalage);
		nb++;
	}
	return nb;
}

/****************************************************************
Fonction pour retourner la commande reçue.
****************************************************************/
char Decodeur::getCommand()
{
	return _instruction.length() == 0 ? 0 : _instruction.charAt(0);
}

/****************************************************************
Fonction pour retourner l'argument sélectionnée
****************************************************************/
float Decodeur::getArg(int noArg)
{
	int compteur = noArg + 1;
	if (_instruction.length() == 0)
		return 0;
	int decalage = 0;
	while (compteur > 0 && decalage >= 0)
	{
		decalage = _instruction.indexOf(_separateur, decalage);
		compteur--;
	}
	if (decalage < 0)
	{
		return decalage > 0 ? convertirArg(_instruction.substring(decalage)) : 0;
	}
}

/***************************************************************************************
//Méthodes privées
//**************************************************************************************/

/*********************************************************
//Routine pour décoder les tokens de la commande
//********************************************************/

bool Decodeur::lireBuffer()
{
	if (_MyStream->available())
	{
		_instruction = _MyStream->readString();
	}
	else
	{
		_instruction = "";
	}
}

/*********************************************************
// Fonction pour convertir l'argument textuel en type float
//********************************************************/

float Decodeur::convertirArg(char *p, int base)
{
	switch (base)
	{
	case ENTIER:
		return atoi(p);
		break; // Conversion token en valeur integer et sauvegarde
	case HEXA:
		return HexaToDecimal(p); // Conversion token en valeur hexadecimale et sauvegarde
		break;
	case FLOTTANT:
		return atof(p); // Conversion token en valeur hexadecimale et sauvegarde
		break;
	default:
		return 0;
	}
}

/*********************************************************
// Fonction pour convertir une chaîne de caractères
// exprimée en valeur hexadécimale en sa valeur décimale
// correspondante.
//********************************************************/
int Decodeur::HexaToDecimal(const char *Hexa)
{
	int ret = 0, t = 0, n = 0;
	const char *c = Hexa;
	while (*c && (n < 16))
	{
		if ((*c >= '0') && (*c <= '9'))
			t = (*c - '0');
		else if ((*c >= 'A') && (*c <= 'F'))
			t = (*c - 'A' + 10);
		else if ((*c >= 'a') && (*c <= 'f'))
			t = (*c - 'a' + 10);
		else
			break;
		n++;
		ret *= 16;
		ret += t;
		c++;
		if (n >= 8)
			break;
	}
	return ret;
}
