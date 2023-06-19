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

## Solutions :

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
_**N** pos = 0 correspond à la position du bit de poids le plus faible_

Exemples : getBit(0, 5) = 1; getBit(1, 5) = 0; getBit(2, 5) = 1

## Solutions :

```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_SIZE sizeof(int) * 8

typedef unsigned short ushort;

ushort getBit(ushort pos, int n);

int main(void) {
	for (ushort pos = 0; pos < INT_SIZE; ++pos)
		printf("bit %hu = %hu\n", pos, getBit(pos, 10));
	return EXIT_SUCCESS;
}

ushort getBit(ushort pos, int n) {
	assert(pos < INT_SIZE);
	return n >> pos & 1; // NB Ici, >> pas dangereux

//	const int MASK = 1 << pos;
//	return (n & MASK) == MASK; // A priori possible mais utilise ==

//	return n & 1 << pos ? 1 : 0; // A priori possible mais utilise ?:
}
```

## Exercice 1.6 Fixer la valeur du nième bit

Sans faire usage de l'instruction if et en utilisant exclusivement des
opérateurs de manipulation de bits, implémenter la fonction dont le prototype
et la sémantique sont donnés ci-dessous.

```c
int* setBit(unsigned short pos, unsigned short bitValue, int* n) 
```

*Sémantique*
Met le bit en position pos dans la représentation binaire du nombre n à la valeur
bitValue
_**NB** pos = 0 correspond à la position du bit de poids le plus faible_

## Solutions :

```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_SIZE (sizeof(int) * 8)

int *setBit(unsigned short pos, unsigned short bitValue, int *n);

int main(void) {
	int n = 0;
	printf("n = %d\n", n);
	printf("n = %d\n", *setBit(0, 1, &n));
	printf("n = %d\n", *setBit(0, 0, &n));
	printf("n = %d\n", *setBit(1, 1, &n));

	for (unsigned short pos = 0; pos < INT_SIZE; ++pos)
		setBit(pos, 1, &n);

	printf("n = %d\n", n);

	int m = -1;
	printf("m = %d\n", *setBit(31, 0, &m));

	return EXIT_SUCCESS;
}

int *setBit(unsigned short pos, unsigned short bitValue, int *n) {
	assert(pos < INT_SIZE);
	assert(bitValue == 0 || bitValue == 1);
	{ // Variante 1
		const int MASK_1 = 1 << pos,
			MASK_2 = bitValue << pos;
		*n = (*n & ~MASK_1) | MASK_2;
	}
	// { // Variante 2
	// const int MASK = 1 << pos;
	// *n ^= (-bitValue ^ *n) & MASK;
	// }
	// { // Variante 3
	// const int MASK = 1 << pos;
	// *n = bitValue ? *n | MASK : *n & ~MASK; // ... mais usage de ?:
	// }
	return n;
}
```

## Exercice 1.7 Position du bit à 1 de plus faible poids

En exploitant au maximum les opérateurs de manipulation de bits, implémenter la
fonction dont le prototype et la sémantique sont donnés ci-dessous.

```c
short lowestOrderSetBit(int n);
```

**Sémantique**
Retourne la position du bit à 1 de plus faible poids. Retourne -1 si aucun bit
n'est à 1.
***NB** pos = 0 correspond à la position du bit de poids le plus faible*

## Solutions :

```c
#define INT_SIZE sizeof(int)*8

short lowestOrderSetBit(int n) {
    short order;
    if (n == 0) {
        order = -1;
    } else {
        for (unsigned short pos = 0; pos < INT_SIZE; ++pos) {
            // Si le bit courant est à 1
            if (n & 1 << pos) {
                order = (short) pos;
                break;
            }
        }
    }
    return order;
}
```

## Exercice 1.8 Représentation binaire d'un entier

En exploitant au maximum les opérateurs de manipulation de bits, implémenter la
fonction dont le prototype et la sémantique sont donnés ci-dessous.

```c
void decimalToBinary(int32_t n, int8_t binary[]);
```

**Sémantique**
Convertit en binaire le nombre entier décimal n et place le résultat dans le
tableau binary

## Solutions :

```c
#define INT32_T_SIZE sizeof(int32_t) * 8

void decimalToBinary(int32_t n, int8_t binary[]) {
    for (size_t i = INT32_T_SIZE; i > 0; --i) {
        binary[i - 1] = n & 1;
        n >>= 1;
    }
}
```

## Exercice 1.9 printf (1)
Que va afficher le programme ci-dessous ?
_(Indiquez par b la présence d'un espace blanc)_
```c
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    int n = 127;
    double x = 12.3456;
    printf("R1 : |%-4d|\n", n);
    printf("R2 : |%04d|\n", n);
    printf("R3 : |%x|\n", n);
    printf("R4 : |%#o|\n", n);
    printf("R5 : |%f|\n", x);
    printf("R6 : |%5.2f|\n", x);
    printf("R7 : |%.2e|\n", x);
    printf("R8 : |%g|\n", x);
    return EXIT_SUCCESS;
}
```

## Solutions :
- R1 : |127b|
- R2 : |0127|
- R3 : |7f|
- R4 : |0177|
- R5 : |12.345600|
- R6 : |12.35|
- R7 : |1.23e+01|
- R8 : |12.3456|

## Exercice 1.10 printf (2)
Soit le squelette de code suivant :
````c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 255;
    double x = 12.345;
    <à compléter>

    return EXIT_SUCCESS;
}
````

Compléter le code ci-dessus de sorte qu'à l'exécution, il reproduise à l'identique l'output suivant :
```
0377
FF
+###255
1.235e+01
12.345
12.3450
```

## Solutions :
````c
printf("%04o\n", n);
printf("%X\n", n);
printf("+###%d\n", n);
printf("%.e\n", x);
printf("%f\n", x);
printf("%07f\n", x);
````

## Exercice 1.11 printf (3)
Compléter le code ci-dessous de telle sorte que celui-ci affiche à l'exécution :
i = 1
j = 4294967295
Important Le code, une fois complété, doit compiler sans warnings.

```c
#include <stdio.h>
#include <stdlib.h>

<à compléter>

int main(void) {
    size_t i = 1;
    uint32_t j = UINT32_MAX;

<à compléter>

    return EXIT_SUCCESS;
}
```

## Solutions :

```c
#include <stdio.h>
#include <stdlib.h>

#include <inttypes.h>

int main(void) {
    size_t i = 1;
    uint32_t j = UINT32_MAX;

    printf("i = %zu\n", i);
    printf("j = %" PRIu32 "\n", j);

    return EXIT_SUCCESS;
}
```

## Exercice 1.12 scanf
Le code ci-dessous n'est pas correct. Le récrire complètement de sorte à corriger toutes les
erreurs / maladresses commises.
```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    char c;
    printf("Donnez un nombre entier et un caractere : ");
    scanf("%d%c", n, c);
    printf("n = %d, c = %c\n", n, c);
    return EXIT_SUCCESS;
}

```

## Solutions : 
```c
#include <stdlib.h>
#include <stdio.h>

void clear_stdin(void);

int main(void) {
    int n;
    char c;
    printf("%s", "Donnez un nombre entier et un caractere : ");
    if (scanf("%d %c", &n, &c) == 2)
        printf("n = %d, c = %c\n", n, c);
    clear_stdin();

    return EXIT_SUCCESS;
}

void clear_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
```
**N.B.** ```clear_stdin``` ne fonctionne que si le buffer n'est pas initialement vide.
Une autre variante, fonctionnant dans tous les cas, consisterait à écrire :
```c
void clear_stdin(void) {
    fseek(stdin, 0, SEEK_END);
}
```

## Exercice 1.13 Lire au maximum n caractères d'une chaîne
Soit le programme C suivant :
```c
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_NOM 20

int main(void) {
    char nom[TAILLE_NOM + 1];

    printf("Entrez votre nom (%d caract. max) : ", TAILLE_NOM);
    scanf("%20s", nom);

    printf("Votre nom est \"%s\"\n", nom);
    system("PAUSE");
    return EXIT_SUCCESS;
}
```
1) Ce programme, pourtant très simple, comporte 3 défauts majeurs. Lesquels ?
2) Récrire le code du programme ci-dessus en corrigeant lesdits défauts

## Solutions : 
#### 1)
1) Le programme ne fonctionne pas correctement si le nom saisi contient des espaces
   … car scanf cesse de lire dès lors qu'un espace est rencontré.
2) Dans scanf, on a écrit "%20s", avec 20 "en dur"… quand bien même on a défini dans le
   code une constante symbolique pour cela. Serait beaucoup mieux de faire en sorte de
   construire le descripteur de format du scanf de telle sorte que si la constante symbolique
   venait à être modifiée le descripteur de format soit automatiquement corrigé en
   conséquence.
3) Le buffer de lecture n'est pas vidé.

#### 2)
```c
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_NOM 20

void clear_stdin(void);

int main(void) {
    char nom[TAILLE_NOM + 1];
    char format[10];

    sprintf(format, " %%%d[^\n]", TAILLE_NOM);
    printf("Entrez votre nom (%d caract. max) : ", TAILLE_NOM);
    scanf(format, nom);
    clear_stdin();

    printf("Votre nom est \"%s\"\n", nom);
    return EXIT_SUCCESS;
}

void clear_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
```
**N.B.** La solution ci-dessus n'est pas parfaite... car elle ne supprime pas les éventuels
"whitespace characters" superflus présents en fin de chaîne. Pour pallier à cela, il faudrait
"trimmer" la chaîne nom.
