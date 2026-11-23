This project has been created as part of the 42 curriculum by mohfall
# get_next_line - @42Born2Code

Le projet **get_next_line** consiste à coder une fonction qui renvoie une ligne lue depuis un descripteur de fichier (`fd`). Ce projet permet de découvrir le concept des **variables statiques** en C et d'approfondir la gestion de la mémoire.

---

## Description

La fonction `get_next_line` lit un fichier ligne par ligne à chaque fois qu'elle est appelée. Si elle est intégrée dans une boucle, elle permet de lire l'intégralité du contenu du fichier jusqu'à la fin (`EOF`).

### Objectifs d'apprentissage :
* Manipulation des descripteurs de fichiers (`fd`).
* Utilisation et compréhension des **variables statiques**.
* Gestion rigoureuse des allocations dynamiques (`malloc` / `free`) pour éviter toute fuite de mémoire.

---

## Spécifications techniques

* **Nom de la fonction :** `get_next_line`
* **Prototype :** `char *get_next_line(int fd);`
* **Fichiers à rendre :** `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`
* **Paramètre :** `fd` — Le descripteur de fichier à lire.
* **Valeur de retour :**
  * La ligne lue (incluant le caractère `\n` s'il est présent).
  * `NULL` s'il n'y a plus rien à lire ou si une erreur survient.
* **Fonctions autorisées :** `read`, `malloc`, `free`.

---

## Instructions

Le comportement de la fonction dépend d'une macro appelée `BUFFER_SIZE`, qui définit le nombre de octets lus à chaque appel de la fonction `read`.

### 1. Inclusion dans votre code
Ajoutez le header dans votre fichier source :
```c
#include "get_next_line.h"
```

### 2. Exemple de code (`main.c`)
```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // Très important pour éviter les fuites de mémoire !
    }
    close(fd);
    return (0);
}
```

### 3. Compilation
Vous devez définir la taille du buffer lors de la compilation avec l'option `-D BUFFER_SIZE=n` :

```bash
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
```

---

## Resources
Pour valider le comportement face aux différents cas limites (Buffer de 1, Buffer immense, multiples fd pour la partie bonus), vous pouvez utiliser les testeurs de la communauté :

* [gnlTester par Tripouille](https://github.com "gnlTester Tripouille")
* [Get_Next_Line_Tester par o-aleksi](https://github.com "Get Next Line Tester")

