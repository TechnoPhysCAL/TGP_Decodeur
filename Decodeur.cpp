/****************************************************************
// Librairie TGP Decodeur
//Auteur : Claude Bouchard
//Date : janvier 2024
//version : 2.0.0
//Description: Permet de lire et décoder des commandes et des
//arguments provenant d'un objet de type Stream, dans un format simplifié tel que
// "{commande} {argNum0} {argNum1} ...",
//***************************************************************/
#include "Stream.h"
#include "Decodeur.h"

/***************************************************************
// Déclaration des variables et constantes privées
//***************************************************************/

String _instruction; // Buffer pour emmagasiner le dernier message reçu
int _NbArg;			 // Variable pour le nombre d'arguments contenu dans le message
char _separateur;	 // Charactère de séparation dans le message
int _base;			 // Variable pour contenir la base numérique (Entier, flottant ou hexadécimal)
Stream *_MyStream;	 // Pointeur pour permettre de sélectionner l'objet de communication Stream

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
// Constructeur spécialisé pour modifier le caractère de séparation et la base numérique
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
	return lireBuffer();
}

/****************************************************************
Fonction pour indiquer le nombre d'arguments reçu.
****************************************************************/
int Decodeur::getArgCount()
{
	return _NbArg;
}

/****************************************************************
Fonction pour retourner la commande reçue, seulement le premier caractère.
****************************************************************/
char Decodeur::getCommand()
{
	return _instruction.length() == 0 ? 0 : _instruction.charAt(0);
}

/****************************************************************
Fonction pour retourner la commande reçue, tout le mot complet en String.
****************************************************************/
String Decodeur::getCommandString()
{
	return _instruction.length() == 0 ? "" : _instruction.substring(0, _instruction.indexOf(_separateur, 1));
}

/****************************************************************
Fonction pour retourner l'argument sélectionné
****************************************************************/
float Decodeur::getArg(int noArg)
{
	int compteur = noArg + 1;
	if (_instruction.length() == 0)
	{
		return 0;
	}
	int decalage = 0;
	while (compteur > 0 && decalage >= 0)
	{
		decalage = _instruction.indexOf(_separateur, decalage + 1);
		compteur--;
	}
	int nextDecalage = _instruction.indexOf(_separateur, decalage + 1);

	if (decalage > 0)
	{
		if (nextDecalage > decalage)
		{
			return convertirArg(_instruction.substring(decalage + 1, nextDecalage), _base);
		}
		else
		{
			return convertirArg(_instruction.substring(decalage + 1), _base);
		}
	}
	else
	{
		return 0;
	}
}

/****************************************************************
Fonction pour retourner l'argument sélectionné sous forme textuel String
****************************************************************/
String Decodeur::getArgString(int noArg)
{
	int compteur = noArg + 1;
	if (_instruction.length() == 0)
	{
		return "";
	}
	int decalage = 0;
	while (compteur > 0 && decalage >= 0)
	{
		decalage = _instruction.indexOf(_separateur, decalage + 1);
		compteur--;
	}
	int nextDecalage = _instruction.indexOf(_separateur, decalage + 1);

	if (decalage > 0)
	{
		if (nextDecalage > decalage)
		{
			return _instruction.substring(decalage + 1, nextDecalage);
		}
		else
		{
			return _instruction.substring(decalage + 1);
		}
	}
	else
	{
		return "";
	}
}

/***************************************************************************************
//Méthodes privées
//**************************************************************************************/

/*********************************************************
//Routine pour stocker le dernier message reçu et mettre à jour les variables nécessaires.
//********************************************************/

bool Decodeur::lireBuffer()
{
	if (_MyStream->available())
	{
		_instruction = _MyStream->readString();
		_instruction.trim();
		updateArgCount();
		if (_instruction.length() > 0)
		{

			return true;
		}
	}

	return false;
}

/*********************************************************
//Routine pour compter le nombre d'arguments disponibles dans le message
//********************************************************/
void Decodeur::updateArgCount()
{
	_NbArg = 0;

	int decalage = _instruction.indexOf(_separateur, 1);

	while (decalage > 0)
	{
		decalage = _instruction.indexOf(_separateur, decalage + 1);
		_NbArg++;
	}
}
/*********************************************************
// Fonction pour convertir l'argument textuel en nombre, selon la base numérique prévue.
//********************************************************/

float Decodeur::convertirArg(String p, int base)
{
	const char *c = p.c_str();
	switch (base)
	{
	case ENTIER:
		return atoi(c);
		break; // Conversion token en valeur integer et sauvegarde
	case HEXA:
		return HexaToDecimal(c); // Conversion token en valeur hexadecimale et sauvegarde
		break;
	case FLOTTANT:
		return atof(c); // Conversion token en valeur hexadecimale et sauvegarde
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
