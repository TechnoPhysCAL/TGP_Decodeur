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
// Déclaration des variables et constantes publiques
//***************************************************************/

/***************************************************************
// Constructeur
//***************************************************************/
Decodeur::Decodeur(Stream *stream, char separateur, char finDeMessage)
{
	_MyStream = stream;
	_separateur = separateur;

	_finDeMessage = finDeMessage;
	_message = "";
	_NbArg = 0;
}

/****************************************************************
Fonction pour consommer le stream et mettre à jour les informations du décodeur.
****************************************************************/
bool Decodeur::refresh()
{
	lireBuffer();
	return isAvailable();
}

/****************************************************************
Fonction pour indiquer si une commande à été reçue.
****************************************************************/
bool Decodeur::isAvailable()
{
	return _message.length() > 0;
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
	return _message.length() == 0 ? 0 : _message.charAt(0);
}

/****************************************************************
Fonction pour retourner la commande reçue, tout le mot complet en String.
****************************************************************/
String Decodeur::getCommandString()
{
	return _message.length() == 0 ? "" : _message.substring(0, _message.indexOf(_separateur, 1));
}

/****************************************************************
Fonction pour retourner l'argument sélectionné
****************************************************************/
float Decodeur::getArg(int noArg, unsigned int base)
{
	return convertirArg(getArgString(noArg), base);
}

/****************************************************************
Fonction pour retourner l'argument sélectionné sous forme textuel String
****************************************************************/
String Decodeur::getArgString(int noArg)
{
	int compteur = noArg + 1;
	if (_message.length() == 0)
	{
		return "";
	}
	int decalage = 0;
	while (compteur > 0 && decalage >= 0)
	{
		decalage = _message.indexOf(_separateur, decalage + 1);
		compteur--;
	}
	int nextDecalage = _message.indexOf(_separateur, decalage + 1);

	if (decalage > 0)
	{
		if (nextDecalage > decalage)
		{
			return _message.substring(decalage + 1, nextDecalage);
		}
		else
		{
			return _message.substring(decalage + 1);
		}
	}
	else
	{
		return "";
	}
}

/****************************************************************
Fonction pour obtenir le message original entier trimmé.
****************************************************************/
String Decodeur::getMessage()
{
	return _message;
}

void Decodeur::setSeparateur(char value)
{
	_separateur = value;
}
char Decodeur::getSeparateur()
{
	return _separateur;
}
void Decodeur::setFinDeMessage(char value)
{
	_finDeMessage = value;
}
char Decodeur::getFinDeMessage()
{
	return _finDeMessage;
}

/***************************************************************************************
//Méthodes privées
//**************************************************************************************/

/*********************************************************
//Routine pour stocker le dernier message reçu et mettre à jour les variables nécessaires.
//********************************************************/

void Decodeur::lireBuffer()
{
	if (_MyStream->available())
	{
		_message = _MyStream->readStringUntil(_finDeMessage);
		_message.trim();
		_message.replace("\0", "");
	}
	else
	{
		_message = "";
	}
	updateArgCount();
}

/*********************************************************
//Routine pour compter le nombre d'arguments disponibles dans le message
//********************************************************/
void Decodeur::updateArgCount()
{
	_NbArg = 0;

	int decalage = _message.indexOf(_separateur, 1);

	while (decalage > 0)
	{
		decalage = _message.indexOf(_separateur, decalage + 1);
		_NbArg++;
	}
}
/*********************************************************
// Fonction pour convertir l'argument textuel en nombre, selon la base numérique prévue.
//********************************************************/

float Decodeur::convertirArg(String p, unsigned int base)
{
	if (p.length() == 0 || base < 2 || base > 36)
	{
		return 0;
	}
	const char *c = p.c_str();
	 char * endPtr ;
	switch (base)
	{
	case 10:
		return atof(c); // Conversion en base 10 avec décimales
		break;
	default:
		return (float)strtol(c, &endPtr, base); // Conversion en valeur d'une autre base, sans décimale
	}
}