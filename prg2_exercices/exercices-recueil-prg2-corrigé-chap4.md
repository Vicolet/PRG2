# Chapitre 4 : Chaînes de caractères

## Exercice 4.1 Implémentation de strlen

Proposez une implémentation de la fonction strlen dont le prototype et la sémantique sont
donnés ci-dessous :

```c
size_t strlen(const char* s);
```

**Sémantique :**

Renvoie le nombre de caractères de la chaîne s (le '\0' final n'est pas comptabilisé)
Écrire aussi un petit programme permettant de tester votre fonction. 

## Solutions :

```c
size_t strlen(const char* s) {
    size_t length = 0;
    while (*s != '\0') {
        length++;
        s++;
    }
    return length;
}
```

## Exercice 4.2 Implémentation de strcpy

Proposez une implémentation de la fonction strcpy dont le prototype et la sémantique sont
donnés ci-dessous :

```c
char* strcpy(char* to, const char* from);
```

**Sémantique :**

Recopie la chaîne from dans la chaîne to et retourne un pointeur sur to.
Écrire aussi un petit programme permettant de tester votre fonction

## Solutions :

```c
char *strcpy(char *to, const char *from) {
    char *tmp = to;
    while ((*to++ = *from++) != '\0');
    return tmp;
}
```

## Exercice 4.3 Implémentation de strncpy

Proposez une implémentation de la fonction strncpy dont le prototype et la sémantique sont
donnés ci-dessous :
```c
char* strncpy(char* to, const char* from, size_t size);
```

**Sémantique :**

Recopie-les size premiers caractères de la chaîne from dans la chaîne to et retourne un
pointeur sur to. De manière plus précise :

- Si size <= strlen(from), size caractères sont copiés dans to.
Attention : Aucune marque de fin de chaîne ('\0') n'est copiée dans to
- Si size > strlen(from), strlen(from) caractères ainsi que size - strlen(from) '\0' sont copiés
dans to.

Écrire aussi un petit programme permettant de tester votre fonction. 

## Solutions :

```c
char *strncpy(char *to, const char *from, size_t size) {
    size_t i;
    for (i = 0; i < size && from[i] != '\0'; ++i)
        to[i] = from[i];
    for (; i < size; ++i)
        to[i] = '\0';
    return to;
}
```

## Exercice 4.4 Implémentation de strcat

Proposez une implémentation de la fonction strcat dont le prototype et la sémantique sont
donnés ci-dessous :

```c
char* strcat(char* to, const char* from);
```

**Sémantique :**

Concatène la chaîne from à la suite de la chaîne to et retourne un pointeur sur to.
Écrire aussi un petit programme permettant de tester votre fonction. 

## Solutions :

```c
char *strcat(char *to, const char *from) {
    char *tmp = to;
    while (*to) to++; // se positionner sur '\0'
    while ((*to++ = *from++) != '\0');
    return tmp;
} 
```

## Exercice 4.5 Implémentation de strncat
Proposez une implémentation de la fonction strncat dont le prototype et la sémantique sont
donnés ci-dessous :

```c
char* strncat(char* to, const char* from, size_t size);
```

**Sémantique :**

Concatène la chaîne from à la suite de la chaîne to et retourne un pointeur sur to… mais au
plus size caractères de la chaîne from sont copiés. Ici, contrairement à strncpy (voir exercice 4.3), 
un caractère '\0' est toujours ajouté à la fin de la chaîne (quel que soit le critère qui arrête la concaténation).

Écrire aussi un petit programme permettant de tester votre fonction.

## Solutions :

```c
char* strncat(char* to, const char* from, size_t size) {
    char* tmp = to;
    if (size) {
        while (*to) to++;
        while ( (*to++ = *from++) != '\0' ) {
            if (--size == 0) {
                *to = '\0';
                break;
            }
        }
    }
    return tmp;
}
```


## Exercice 4.6 Implémentation de strcmp
Proposez une implémentation de la fonction strcmp dont le prototype et la sémantique sont
donnés ci-dessous :

```c
int strcmp(const char* s, const char* t);
```

**Sémantique :**

Compare les deux chaîne s et t et retourne un résultat > 0 si s > t, = 0 si s = t et < 0 si s < t.

Écrire aussi un petit programme permettant de tester votre fonction.

## Solutions :

```c

```

## Exercice 4.7 Implémentation de strchr
Proposez une implémentation de la fonction strchr dont le prototype et la sémantique sont
donnés ci-dessous :

```c
char* strchr(const char* s, int c);
```

Sémantique :

Retourne un pointeur sur la première occurrence du "caractère" c dans la chaîne s ou NULL si
c n'est pas trouvé.

Écrire aussi un petit programme permettant de tester votre fonction.

## Solutions :

```c

```

## Exercice 4.8 Prénom et nom
Écrire une fonction C qui prend en paramètres un prénom et un nom et qui retourne une
nouvelle chaîne sous la forme "prénom nom".

Exemple : "James" + "Bond" => "James Bond".

Écrire aussi un petit programme de test qui, après avoir demandé à l'utilisateur d'entrer un
prénom, puis un nom, affiche à l'écran, en utilisant les services de la fonction ci-dessus :

```La chaine "prénom nom" comporte n caractères.```

Soit, dans notre exemple :

```La chaine "James Bond" comporte 10 caractères.```

## Solutions :

```c

```

## Exercice 4.9 Inversion d'une chaîne
Proposer une implémentation pour chacune des fonctions d'inversion d'une chaîne suivantes :
1. ```c
   void inverser_1(char* s);
   ```
2. ```c
   char* inverser_2(const char* s);
   ```
   NB renvoie s en cas de problème
   
Écrire aussi un petit programme permettant de tester les deux fonctions.

Lister les avantages/inconvénients respectifs des 2 fonctions ci-dessus.
**NB** Hormis strlen, aucune autre fonction de string.h ne doit être utilisée ici. 

## Solutions :

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NB Ne fait rien si s vaut NULL
void inverser_1(char *s);

// NB Renvoie s si s vaut NULL ou en cas de mémoire insuffisante
char *inverser_2(const char *s);

int main(void) {
    char s1[] = "ABCD"; // Attention : inverser_1 ne fonctionnerait pas avec :
    // const char* s1 = "ABCD" (car "ABCD" est une chaîne cste,
// ... donc(!) non modifiable
    printf("s1 avant inversion = %s\n", s1);
    inverser_1(s1);
    printf("s1 apres inversion = %s\n", s1);

    const char *s2 = "ABCD";
    char *s3 = inverser_2(s2);
    printf("\ns2 avant inversion = %s\n", s2);
    printf("inverse de s2 = %s\n", s3);
    printf("s2 apres inversion = %s\n", s2);

    free(s3);

    inverser_1(NULL); // Ne doit pas "planter" le programme
    inverser_2(NULL); // Idem

    return EXIT_SUCCESS;
}

void inverser_1(char *s) {
    if (s != NULL) {
        char c, *ptr = s + strlen(s) - 1;
        while (s < ptr) {
            c = *s;
            *s++ = *ptr;
            *ptr-- = c;
        }
    }
}

char *inverser_2(const char *s) {
    if (s != NULL) {
        const size_t TAILLE = strlen(s);
        char *r = (char *) calloc(TAILLE + 1, sizeof(char));
        if (r != NULL) {
            char *ptr = r + TAILLE - 1;
            for (; *s; s++)
                *ptr-- = *s;
            return r;
        }
    }
    return (char *) s;
} 
```

Avantages (+) / désavantages (-) de inverser_1:

- (+) rapide, car pas d'allocation dynamique
- (-) La chaîne originale étant modifiée, il n'est pas possible de passer une chaîne constante en paramètre effectif

Avantages (+) / désavantages (-) de inverser_2 :

- (+) La chaîne originale n'étant pas modifiée, il est possible de passer une chaîne constante en paramètre effectif
- (-) Plus lente, car nécessite une allocation dynamique