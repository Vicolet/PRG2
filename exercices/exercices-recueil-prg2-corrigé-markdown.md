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

#define ABS(X) (((X) > 0) ? (X) : (-X))

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
3) Est-il possible de récrire (sans utiliser la fonction abs de stdlib) la macro ABS de
   manière à éviter le(s) problème(s) du point 2) ? 

## Solutions : 

1) Ce programme va afficher :
   1. 2
   2. 2
   3. code ASCII de 'A' (65)
   4. 3
   5. 1 0
   6. 0 0 
   7. 1 -1
