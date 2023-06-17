# Chapitre 1 : Introduction

## Exercice 1.1 Substitutions

En supposant les <?> du code ci-dessous remplacé par le code de format adéquat,
indiquer ce que va afficher le programme suivant ?

```c
#include <stdio.h>
#include <stdlib.h>

#define A 1
#define B 2
#define AB 3
#define F(X, Y) X##Y

int main(void) {
	int n = AB;

	printf("%<?>\n", n);
	printf("%<?>\n", "AB");
	printf("%<?>\n", F(A, B));

	return EXIT_SUCCESS;
}
```

## Solution :

- 3
- AB
- 3

## Exercice 1.2 Macros (1)

Le programme suivant contient une ou plusieurs erreurs. Corrigez-le de telle sorte
qu'il affiche à l'exécution :

25 -1

```c
#include <stdio.h>
#include <stdlib.h>

#define A = 2;
#define B = A + 1;
#define PLUS (X,Y) X+Y;
#define MOINS(X, Y) X-Y;

int main(void) {
	printf("%d %d\n", 5 * PLUS(A,B), MOINS(A + 1, B + 1));

	return EXIT_SUCCESS;
}
```

## Solutions :

```c
#define A 2
#define B A + 1
#define PLUS(X, Y) (X+Y)
#define MOINS(X, Y) (X)-(Y)
```

## Exercice 1.3 Macros (2)

Soit le programme suivant (ABS = macro "valeur absolue") :

````c
#include <stdio.h>
#include <stdlib.h>

#define ABS(X) (((X) > 0) ? (X) : (-X)

int main(void) {
	int n;
	printf("1. %d\n", ABS(2));
	printf("2. %d\n", ABS(-2));
	printf("3. %d\n", ABS('A'));
	
	n = -2;
	printf("4. %d\n", ABS(n + 1));
	
	n = -2;
	printf("5. %d", ABS(n++));
	printf(" %d\n", n);
	
	n = -2;
	printf("6. %d", ABS(++n));
	printf(" %d\n", n);

	n = -2;
	printf("7. %d", abs(++n));
	printf(" %d\n", n);
	return EXIT_SUCCESS;
}
````

1) Que va afficher ce programme ?
2) Expliquez-en quoi le programme ci-dessus est problématique.
3) Est-il possible de récrire (sans utiliser la fonction abs de stdlib) la macro 
   ABS de manière à éviter le(s) problème(s) du point 2) ?

## Solutions :

1) Ce programme va afficher :
    1) 2 // OK
    2) 2 // OK
    3) 65 // OK (code ASCII de 'A')
    4) 3 // Faux on se serait attendu à 1
    5) 1 0 // Faux (effets de bord)!   on se serait attendu à 2 -1
    6) 0 0 // Faux (effets de bord)!   on se serait attendu à 1 -1
    7) 1 -1 // OK (pas d'effets de bord avec)

2) Le programme est problématique pour 2 raisons :
    1. La macro est incorrecte (comme l'indique la valeur de la réponse 4).
       Si déjà, il faudrait écrire :
       ````c
       #define ABS(X) (((X) > 0) ? (X) : -(X))
       ````
    2. La macro est susceptible de produire des effets de bord (comme l'indique la
       valeur des réponses 5 et 6).

3) Oui, il suffit de réécrire le programme comme suit :

````c
#include <stdio.h>
#include <stdlib.h>

#define GENERIC_ABS(type)   \
type type##_abs(type x) {   \
   return x > 0 ? x : -x;   \
}

GENERIC_ABS(int) // Rappel : abs stdlib : int abs (int n)

int main(void) {
	int n;
	printf("1. %d\n", int_abs(2));
	printf("2. %d\n", int_abs(-2));
	printf("3. %d\n", int_abs('A'));
	n = -2;
	printf("4. %d\n", int_abs(n + 1));
	n = -2;
	printf("5. %d", int_abs(n++));
	printf(" %d\n", n);
	n = -2;
	printf("6. %d", int_abs(++n));
	printf(" %d\n", n);

	n = -2;
	printf("7. %d", abs(++n));
	printf(" %d\n", n);
	return EXIT_SUCCESS;
}
````

## Exercice 1.4 Opérateurs de manipulation de bits (1)

Que vaut chacune des expressions suivantes ?

1) 22 | 11
2) 0 ^ 19
3) 2 << 3
4) 30 & 14
5) 8 >> 2
6) 4 & 29
7) 9 << 4
8) 31 ^ 27
9) 23 | 3
10) -1 >> 1
11) -5 >> 1
12) 3 & ~2
13) 6 | 5 & 4

## Solutions :

1) 31
2) 19
3) 16
4) 14
5) 2
6) 4
7) 144
8) 4
9) 23
10) -1
11) -3
12) 1
13) 6

## Exercice 1.5 Récupérer la valeur du nième bit

Sans faire usage de l'instruction if et en utilisant exclusivement des opérateurs de
manipulation de bits, implémenter la fonction dont le prototype et la sémantique 
sont donnés ci-dessous.

````c
unsigned short getBit(unsigned short pos, int n);
````

**Sémantique**
Retourne la valeur du bit en position pos dans la représentation binaire du nombre n
_NB pos = 0 correspond à la position du bit de poids le plus faible_

Exemples : getBit(0, 5) = 1; getBit(1, 5) = 0; getBit(2, 5) = 1
