# Librairie TGP Decodeur

Permet de décoder les messages selon le format 'C a1 a2 a3 ...' où C est une lettre ou un mot représentant une commande donnée, suivie d'une liste d'arguments de taille et de type variable. La fin de la ligne doit se terminer par le caractère '\n'.

La librairie fonctionne avec tout objet qui implémente la classe [Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/); l'objet fournira le texte brut qui sera décodé.

## Notes de version

### 2.0.0:
- Refonte du code au complet. On laisse tomber la mise en buffer des arguments, on stocke tout le message reçu dans un String et on décode les arguments seulement sur demande. 
- Ajout des méthodes getCommandString() et getArgString() pour permettre d'utiliser tout le texte tel quel de chaque morceau du message.
- Ajout de la méthode getMessage() pour relire le message trimé reçu.

### 1.1.2 :
- Changé l'URL du projet pour pointer sur GitHub.

### 1.1.1 :
- Idem que précédent, avec un correcif pour le caractère '\n' et '\r'.

### 1.1.0 :
- Correction si le message reçu ne contient qu'un retour de chariot.

### 1.0.0 :
- Première version officielle, crée à partir de l'ancienne librairie SerieTPhys.




## Utilisation

On utilise cette librairie pour implémenter un mode de message simplifié du type "commande arg0 arg1 arg2 ...", où "commande"" est généralement un seul caractère et les arguments sont habituellement numériques, et peuvent se suivre sans limite théorique.

Voici des exemples de messages qui pourrait être utilisée:
"R 1 2"
"T 3.45"
"g -7.8 0 45"

La librairie permet également de supporter des commandes ou des arguments sous forme de texte. Voici des exemples:
"tourner 45"
"set version 2"

### Considérations

- Avant le début du décodage du message, la fonction trim() est appliquée sur le texte reçu, ce qui aura pour effet de retirer tout espace blanc avant et après le message.

- Lors du décodage du message, deux caractères de séparation consécutifs seront interprétés comme contenant ayant un argument vide entre les deux. Par exemple, le message "g 1  2" doit être vu comme étant une commande contenant trois arguments "g 1 {vide} 2". C'est donc à l'utilisateur de prendre soin du formatage de ses messages pour éviter ce genre d'arguments "fantômes".


### Exemples

Voici un exemple simple, avec une commande à une lettre et des arguments numériques
```cpp
#include <Decodeur.h> 

Decodeur monDecodeur(&Serial); //fournir un objet qui implémente la classe Stream

void setup()
{
 Serial.begin(115200); //Ou tout autre instruction d'initialisation pour le port de communication
}

void loop()
{

  if (monDecodeur.available()) // Si un message est disponible
  {

   char command = monDecodeur.getCommand();   //Obtenir le premier caractère de commande décodé
   int argCount =  monDecodeur.getArgCount(); //Obtenir le nombre d'arguments décodé.
    
  for (int no = 0; no < argCount; no++) //Pour chaque argument
    {
      float arg = monDecodeur.getArg(no)); //Obtenir l'argument d'indice 'no'
    }
  }
}

```

Voici une version avancée, pouvant utiliser une commande et des arguments textuels
```cpp
#include <Decodeur.h> 

Decodeur monDecodeur(&Serial); //fournir un objet qui implémente la classe Stream

void setup()
{
 Serial.begin(115200); //Ou tout autre instruction d'initialisation pour le port de communication
}

void loop()
{

  if (monDecodeur.available()) // Si du texte est disponible
  {

   String command = monDecodeur.getCommandString();   //Obtenir le mot de commande décodé
   int argCount =  monDecodeur.getArgCount(); //Obtenir le nombre d'arguments décodé.
    
  for (int no = 0; no < argCount; no++) //Pour chaque argument
    {
      String arg = monDecodeur.getArgString(no)); //Obtenir l'argument d'indice 'no' sous forme de texte
    }
  }
}

```

## Constructeurs
```cpp
Decodeur(Stream *stream)
Decodeur(Stream *stream,char separateur)
Decodeur(Stream *stream,char separateur, char finDeMessage)
Decodeur(Stream *stream,char separateur, char finDeMessage, int base)
```
On spécifie l'objet qui implémente la classe [Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/) (dans Arduino on retrouve les objets suivants: Serial, Ethernet, Wire, SD). On doit fournir l'addresse de l'objet, en ajoutant le caractère '&' devant celui-ci (voir section Utilisation).

On spécifie facultativement le caractère servant à séparer la commande et les arguments (par défaut, l'espace ' '), le caractère servant à signifier la fin du message (par défaut '\n') ainsi que la base attendu des arguments (mots définis ENTIER, HEXA ou FLOTTANT).

## Méthodes disponibles

```cpp
bool available()
```
Cette méthode indique si un message a été reçu et décodé.

---
```cpp
char getCommand()
```
Permet de lire le caractère de commande décodé.

---
```cpp
String getCommandString()
```
Permet de lire tout le mot de commande décodé.

---
```cpp
int getArgCount()
```
Permet de lire le nombre d'arguments décodés.

---

```cpp
float getArg(int index)
```
Permet de lire l'argument d'index donné. Retourne 0 en cas d'indice non valide, ou si l'argument n'a pas été correctement décodé.
La variable retournée est de type float, on peut le réduire à un entier par 'casting explicite'.

---

```cpp
String getArgString(int index)
```
Permet de lire l'argument d'index donné, sous forme de String. Retourne une chaîne vide "" en cas d'indice non valide.


---
```cpp
void setSeparateur(char);
char getSeparateur();
```
Permet de lire et écrire le caractère pour séparer les arguments du message.


---
```cpp
void setFinDeMessage(char);
char getFinDeMessage();
```
Permet de lire et écrire le caractère marquant la fin du message.

---
```cpp
void setBase(int);
int getBase();
```
Permet de lire et écrire le type de base numérique attendu pour les arguments (ENTIER, FLOTTANT ou HEXA).