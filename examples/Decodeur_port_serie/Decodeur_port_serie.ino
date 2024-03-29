#include <Decodeur.h> //Pour utiliser la librairie Decodeur

Decodeur monDecodeur(&Serial); // Le décodeur utilisera le texte provenant du port Serie

void setup()
{
  Serial.begin(115200); // Démarrage du port série afin d'envoyer des lignes de texte pour les fins de démonstrations.
}

void loop()
{

  monDecodeur.refresh();
  if (monDecodeur.isAvailable()) // Si du texte a été reçu par le décodeur;
  {
    Serial.println("---------------------------------------------------");
    Serial.print("Message reçu          : ");
    Serial.println(monDecodeur.getMessage());

    Serial.print("Commande (un caractère) : ");
    Serial.println(monDecodeur.getCommand()); // Envoyer sur le port série le nom de la commande décodée.
    Serial.print("Commande (mot complet): ");
    Serial.println(monDecodeur.getCommandString()); // Envoyer sur le port série le nom de la commande décodée.

    Serial.print("Nombre d'arguments    : ");
    Serial.println(monDecodeur.getArgCount()); // Envoyer sur le port série le nombre d'arguments décodée.

    Serial.print("Arguments numériques                   : ");
    for (int no = 0; no < monDecodeur.getArgCount(); no++) // Pour chaque argument
    {
      Serial.print(monDecodeur.getArg(no)); // Envoyer sur le port série la valeur de l'argument (si on parvient à l'interpréter comme un nombre).
      Serial.print(" , ");
    }

    Serial.print("\nArguments textuels                   : ");
    for (int no = 0; no < monDecodeur.getArgCount(); no++) // Pour chaque argument
    {
      Serial.print(monDecodeur.getArgString(no)); // Envoyer sur le port série le texte brut de l'argument.
      Serial.print(" , ");
    }

    Serial.print("\nArguments interprétés en hexadécimal : ");
    for (int no = 0; no < monDecodeur.getArgCount(); no++) // Pour chaque argument
    {
      Serial.print(monDecodeur.getArg(no, HEX)); // Envoyer sur le port série la valeur de l'argument (si on parvient à l'interpréter comme un nombre hexadécimal).
      Serial.print(" , ");
    }

    Serial.print("\nArguments interprétés en binaire     : ");
    for (int no = 0; no < monDecodeur.getArgCount(); no++) // Pour chaque argument
    {
      Serial.print(monDecodeur.getArg(no, BIN)); // Envoyer sur le port série la valeur de l'argument (si on parvient à l'interpréter comme un nombre binaire).
      Serial.print(" , ");
    }
    Serial.println("");

  }
}
