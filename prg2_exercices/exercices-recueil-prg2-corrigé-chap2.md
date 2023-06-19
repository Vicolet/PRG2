# Chapitre 2 : Pointeurs

## Exercice 2.1 Les bases…

Ecrire un programme C qui :

1) Déclare une variable n de type int et l'initialise à la valeur 1
2) Déclare un pointeur ptr pointant sur n
3) Affiche à l'écran la valeur de l'objet pointé par ptr
4) Affiche à l'écran l'adresse contenue dans ptr
5) Affiche l'adresse de ptr

## Solutions :

1) ```int n = 1;```
2) ```int* ptr = &n;```
3) ```printf("%d\n", *ptr);```
4) ```printf("%p\n", ptr);```
5) ```printf("%p\n", &ptr);```

## Exercice 2.2 Paramètres d'entrée-sortie

Écrire une fonction C sans valeur de retour (void) qui prend comme paramètre d'entrée un
nombre réel x (de type double) et qui renvoie, par paramètres d'entrée-sortie, le carré et le
cube de x.

## Solutions :

```c
void carre_et_cube(double x, double *squared, double *cube) {
    *squared = x * x;
    *cube = *squared * x;
}
```

## Exercice 2.3 Fonction avec valeur de retour de type pointeur

Que va produire à l'exécution le programme C ci-dessous ?

```c
#include <stdio.h>
#include <stdlib.h>

int *carres(const int tab[]);

int main(void) {
    int tab[] = {1, 2, 3};
    const size_t N = sizeof(tab) / sizeof(int);
    int *ptr = carres(tab);
    for (size_t i = 0; i < N; ++i)
        printf("%d ", ptr[i]);
    printf("\n");
    return EXIT_SUCCESS;
}

int *carres(const int tab[]) {
    const size_t N = sizeof(tab) / sizeof(int);
    int copie[N];
    for (size_t i = 0; i < N; ++i)
        copie[i] = tab[i] * tab[i];
    return copie;
}
```

## Solutions :

Le programme ci-dessus produit un comportement indéterminé et peut entraîner des résultats incorrects ou imprévisibles.

## Exercice 2.4 Interprétation de déclarateurs avec pointeurs

Traduire en français les déclarations C suivantes :
(Exemple : pour int* ptr, il faut répondre "ptr est un pointeur sur int")

1) ```char** a[10];```
2) ```double* (*b)(void);```
3) ```double (*c)(double*);```
4) ```int* d[10];```
5) ```int (*e)[10];```
6) ```int (*(*f[5])(void))[10];```
7) ```double (**g)[5];```

## Solutions :

1) a est un tableau de 10 pointeurs pointant chacun sur un pointeur sur char
2) b est un pointeur sur une fonction sans paramètre renvoyant un pointeur sur un double
3) c est un pointeur sur une fonction prenant en paramètre un pointeur sur double et livrant un double
4) d est un tableau de 10 pointeurs sur int
5) e est pointeur sur un tableau de 10 int
6) f est un tableau de 5 pointeurs pointant chacun sur une fonction sans paramètre et livrant un pointeur sur un tableau
   de 10 int
7) g est un pointeur contenant l'adresse d'un pointeur sur un tableau de 5 double

## Exercice 2.5 Écriture de déclarateurs avec pointeurs

Écrire les déclarations C correspondant aux énoncés suivants :

1) t est un tableau de 10 pointeurs pointant chacun sur un int constant
2) t est un tableau de 10 pointeurs constants pointant chacun sur un int
3) p est un pointeur sur une fonction prenant en paramètre un pointeur sur une fonction
   (prenant en paramètre un double et livrant un double) et renvoyant un pointeur sur int
4) p est un pointeur constant sur un tableau de 10 pointeurs sur double
5) t est un tableau de 10 pointeurs pointant chacun sur une fonction prenant un double
   comme paramètre et renvoyant un pointeur sur char
6) f est une fonction prenant en paramètre un pointeur constant sur char et renvoyant un
   pointeur constant contenant l’adresse d’un pointeur sur char
7) f est une fonction sans paramètre renvoyant un pointeur sur un tableau de 10 pointeurs
   constants sur char

## Solutions :

1) ```const int *t[10];```
2) ```int* const t[10] = <initialisation>;``` // **N.B.** équivalent à dire que t est tableau constant de pointeurs
3) ```int* (*p)(double (*)(double));```
4) ```double* (* const p)[10] = <initilisation>;```
5) ```char* (*t[10])(double) ;```
6) ```char** const f(char* const);```
7) ```char* const ((f*)(void))[10];```

## Exercice 2.6 Affectations entre pointeurs

Soient les déclarations suivantes :

```int i = 1, j = 2;```
```int* pi1 = &i;```
```int* pi2 = &j;```
```double x = 3.0;```
```double* pd = &x;```
```void* pv;```

Quel sera dans un programme l’effet des instructions suivantes ?

1) pi1 = pi2;
2) pd = pi1;
3) pi1 = pd;
4) pv = pi1;
5) pv = &i;
6) pv = pi1;
   pi2 = pv;
7) if (pi1 = pi2)…;

## Solutions :

1) OK. pi1 désigne le même entier que pi2 (soit, dans notre cas, 2)
2) Produit warning : ```assignment from incompatible pointer type```
   Il est par contre possible d'écrire : ```pd = (double*) pi1;```
3) Produit warning : ```assignment from incompatible pointer type```
   Il est par contre possible d'écrire : ```pi1 = (int*) pd;```
   À noter que dans les cas 2 et 3), les conversions explicites peuvent conduire ensuite, lors du déréférencement, à des
   résultats non escomptés.
   Exemple : ```printf("%d\n", *pi1);``` n'affichera pas 3 comme (peut-être) espéré.
4) OK. pv contient maintenant l'adresse contenue dans pi1
   … mais attention : cette adresse ne peut pas être exploitée sans autres.
   Si, après avoir effectué l'affectation pv = pi1, on tente d'écrire, par exemple : ```printf("%d\n", *pv);```
   , on obtient une erreur à la compilation. On peut par contre écrire : ```printf("%d\n", *((int*)pv));```
5) Idem que 4)
6) OK. En C (mais pas en C++), un pointeur de type void* peut être converti implicitement en un pointeur d'un autre type
7) OK. Affecte à pi1 l'adresse contenue dans pi2 et la condition est vraie si pi2 n'est pas NULL

## Exercice 2.7 Arithmétique des pointeurs (1)

Que va afficher le programme main ci-dessous ?
_(Conseil : Aidez-vous d'un petit dessin)_

```c
#include <inttypes.h>
#include <stddef.h> // pour ptrdiff_t
#include <stdlib.h>
#include <stdio.h>

int main(void) {

    int a[] = {10, 20, 30, 40, 50};
    int *p[] = {a, a + 1, a + 2, a + 3, a + 4};
    int **pp = &p[2];
    int ***ppp = &pp;
    printf("1) %d\n", *a);
    printf("2) %d\n", **p);
    printf("3) %d\n", **pp++);
    printf("4) %d\n", ***ppp);
    pp = p;
    printf("5) %d\n", **++pp);
    pp = p;
    printf("6) %d\n", ++**pp);
    pp = p;
    printf("7) %d\n", *pp[1]);
    pp = p;
    printf("8) %" PRIdPTR "\n", (ptrdiff_t) (*(p + 1) - *pp));

    return EXIT_SUCCESS;
}
```

## Solutions :

tableau d'aide :

|  a   | 10 |  20   |  30   |  40   |  50   |
|:----:|:--:|:-----:|:-----:|:-----:|:-----:|
|      | ↑  |   ↑   |   ↑   |   ↑   |   ↑   |
|  *p  | a  | a + 1 | a + 2 | a + 2 | a + 2 |
|      |    |       |   ↑   |       |       |
| **p  |    |       | &p[2] |       |       |
|      |    |       |   ↑   |       |       |
| ***p |    |       |  &pp  |       |       |

1) 10
2) 10
3) 30
4) 40
5) 20
6) 11
7) 20
8) 1

## Exercice 2.8 Arithmétique des pointeurs (2)

Que va afficher le programme main ci-dessous ?
_(Conseil : Aidez-vous d'un petit dessin)_

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int t[6], i, *p;
    for (p = &t[5]; p > &t[-1]; p--)
        *p = (int) (p - t);

    for (i = 0; i < 6; i++)
        printf("%d ", t[i]);
    printf("\n");

    for (i = 0, ++p; i < 6; i++)
        printf("%d ", *p++ / 2);
    printf("\n");
    return EXIT_SUCCESS;
}
```

## Solutions :

```c
0 1 2 3 4 5 
0 0 1 1 2 2 
```

## Exercice 2.9 Arithmétique des pointeurs (3)

Soient les déclarations suivantes :

```c
const char* c[] = {"elle", "mangera", "une", "petite", "tomme"};
const char** d[] = {c+1, c+2, c+3, c+4, c};
const char*** e = &d[3];
```

Quelles valeurs fournissent les expressions suivantes ?
_(Conseil : Aidez-vous d'un petit dessin)_

a) c[3][0]
b) (**d)[5]
c) (**e)[*d-c]
d) (d[3]-3)[0][3]
e) **d + 5
f) *d[3] + 2
g) *(*e[-3] + 5)
h) **c
i) e[0][0][e-d]+1
j) 0[c][0] - 'd' + 'B'

**Remarques**

- Pour les chaînes de caractères (char *), donner le résultat entre guillemets. Ex : "ABC".
- Pour les caractères (char), donner la représentation littérale. Ex : ‘a’.

## Solutions :

a) 'p'
b) 'r'
c) 'o'
d) 'g'
e) "ra"
f) "mme"
g) 'r'
h) 'e'
i) code ASCII de 'n' // car 'm' + 1 = 'n'
j) code ASCII de 'C' // car tab[i] = i[tab]

## Exercice 2.10 Arithmétique des pointeurs (4)

Que va afficher le programme main ci-dessous ?
_(Conseil : Aidez-vous d'un petit dessin)_

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *c[] = {"comprendre", "les", "pointeurs", "c\'est", "difficile"};
    const char **cp[] = {c, c + 2, c + 4, c + 1, c + 3};
    const char ***cpp = cp;
    int i;
    for (i = 0; i < 3; i++)
        printf("%c", *(**cpp + i));
    printf("%c", *(*cp[0] + 2));
    printf("%s ", *cpp[2] + 8);
    printf("%s ", *++*++cpp);
    for (i = 1; i < 4; i++)
        printf("%c", *(cpp[-1][i % 3] + 2));
    printf("%c", **--*cpp);
    printf("%s\n", **++cpp + 7);
    return EXIT_SUCCESS;
} 
```

## Solutions :

```comme c'est simple```

## Exercice 2.11 Formalisme pointeur et tableaux 1D

Écrire d'au moins 6 manières différentes, mais toujours en utilisant le formalisme pointeur,
une fonction C initialiser, sans valeur de retour (void), permettant d'initialiser à une valeur
donnée (de type int), tous les éléments d'un tableau à 1 dimension (1D) de taille quelconque et
composé d'entiers (de type int).

## Solutions :

```c
#include <stdio.h>
#include <stdlib.h>

void initialiser1(int* tableau, size_t taille, int valeur) {
    for (size_t i = 0; i < taille; ++i) {
        tableau[i] = valeur;
    }
}

void initialiser2(int* tableau, size_t taille, int valeur) {
    int* ptr = tableau;
    int* fin = tableau + taille;
    while (ptr < fin) {
        *ptr = valeur;
        ++ptr;
    }
}

void initialiser3(int* tableau, size_t taille, int valeur) {
    int* fin = tableau + taille;
    for (; tableau < fin; ++tableau) {
        *tableau = valeur;
    }
}

void initialiser4(int* tableau, size_t taille, int valeur) {
    int* ptr = tableau;
    for (size_t i = 0; i < taille; ++i) {
        *(ptr + i) = valeur;
    }
}

void initialiser5(int* tableau, size_t taille, int valeur) {
    for (size_t i = 0; i < taille; ++i, ++tableau) {
        *tableau = valeur;
    }
}

void initialiser6(int* tableau, size_t taille, int valeur) {
    int* fin = tableau + taille;
    while (tableau < fin) {
        *tableau++ = valeur;
    }
}

int main(void) {
    int tableau[5];

    initialiser1(tableau, 5, 42);
    // ou initialiser2(tableau, 5, 42);
    // ou initialiser3(tableau, 5, 42);
    // ou initialiser4(tableau, 5, 42);
    // ou initialiser5(tableau, 5, 42);
    // ou initialiser6(tableau, 5, 42);

    for (size_t i = 0; i < 5; ++i) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
```

## Exercice 2.12 Inversion d'un tableau 1D (1)

Implémenter la fonction C dont le prototype et la sémantique sont donnés ci-dessous :

```c
 void inverser(int* debut, int* fin);

 ```

**Sémantique**
Inverse le contenu du tableau 1D défini par _début_ et _fin_ où début, resp. _fin_, désigne l'adresse
du premier, resp. du dernier, élément du tableau à inverser.

## Solutions :

```c
void inverser(int *debut, int *fin) {
    assert(debut != NULL);
    assert(fin != NULL);
    while (debut < fin) {
        int tampon = *debut;
        *debut++ = *fin;
        *fin-- = tampon;
    }
}
```

## Exercice 2.13 Méli-mélo

Que va afficher le programme main ci-dessous ?
_(On suppose travailler ici avec une architecture 32 bits)_

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i = 1, j = 2;
    int *p = &i, *q = &j;
    
    *p = (int) q;
    *q = (int) p;
    p = (int *) *p;
    q = (int *) *q;
    i = 3, j = 4;
    printf("*p = %d *q = %d\n", *p, *q);
    
    return EXIT_SUCCESS;
}
```

## Solutions :

```*p = 4 *q = 3```

## Exercice 2.14 Pointeurs, tableaux et fonctions

Que va afficher le programme main ci-dessous ?

```c
#include <stdio.h>
#include <stdlib.h>

void f(int *p1, int p2);

int main(void) {
    int a = 5, b = 6;
    int t[2] = {3, 4};
    int *p = NULL, *q = NULL;

    f(&a, b);
    printf("1) %d, %d\n", a, b);

    p = &a;
    q = &b;
    f(q, *p);
    printf("2) %d, %d\n", *p, *q);

    f(t + 1, *t);
    printf("3) %d, %d\n", t[0], t[1]);

    f((int *) (&p), b);
    printf("4) %d, %d\n", a, b);

    return EXIT_SUCCESS;
}

void f(int *p1, int p2) {
    *p1 = 2 * p2;
}
```

## Solutions :

## Exercice 2.15 Utilisation de calloc

Ecrire une fonction C initialiser permettant 1°) de créer un tableau (à 1 dimension) de taille
donnée, composé d'entiers (de type int), 2°) d'initialiser à une valeur donnée (de type int) tous
les éléments de ce tableau.

#### **IMPORTANT**

La fonction :

- ne doit comporter que 2 paramètres : le premier fixant la taille (le nombre d'éléments) du
  tableau à créer, le second fixant la valeur à donner à tous les éléments du tableau
- doit utiliser les services de la fonction calloc
  Écrire aussi un petit programme de test permettant de vérifier le bon fonctionnement de votre
  fonction.

## Solutions :

## Exercice 2.16 Inversion d'un tableau 1D (2)

Implémenter la fonction C dont le prototype et la sémantique sont donnés ci-dessous :

```c
int* inverse(const int* debut, const int* fin);
```

**Sémantique**
Renvoie le tableau inverse du tableau 1D défini par début et fin où début, resp. fin, désigne
l'adresse du premier, resp. du dernier, élément du tableau à inverser.

## Solutions :

## Exercice 2.17 Adresses du min et du max d'un tableau 1D

Ecrire une fonction C qui prend en paramètre un tableau tab 1D de int de taille quelconque et
qui renvoie en valeur de retour les adresses du plus petit élément et du plus grand élément1 de
tab _(ou NULL si tab vaut NULL ou si tab est vide)_.
Dans le cas où il y aurait plusieurs plus petits éléments on renverra l'adresse de celui dont l'indice dans tab est le
plus petit (idem dans le cas du plus grand élément).

## Solutions :

## Exercice 2.18 Manipulation de la mémoire (1)

Ecrire un programme C qui :

1) déclare et initialise un tableau tab1 à une dimension de int
2) copie (sans utiliser de boucle) le contenu de tab1 dans un autre tableau tab2
3) affiche tab1 et tab2
4) se termine

NB Prévoir une fonction dédiée à l'affichage d'un tableau sous la forme [valeur1, valeur2,…].
Écrire cette fonction en utilisant exclusivement le formalisme pointeur.

## Solutions :

## Exercice 2.19 Manipulation de la mémoire (2)

Sans utiliser de boucle, compléter la partie notée <à compléter> dans le programme C cidessous de telle sorte que
celui-ci affiche à l'exécution :
[0, 0, 0]
[1, 1, 1]
[2, 2, 2]

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3

void afficher … // Le code de la fonction afficher a volontairement été omis ici

int main(void) {

    int tab[SIZE] = {0};
    afficher(tab, SIZE);
    for (size_t i = 0; i < SIZE; ++i)
        tab[i]++;
    afficher(tab, SIZE);
    //<à compléter>

    for (size_t i = 0; i < SIZE; ++i)
        tab[i] += 2;
    afficher(tab, SIZE);

    return EXIT_SUCCESS;
}
```

## Solutions :

## Exercice 2.20 Manipulation de la mémoire (3)

Que va afficher à l'exécution le programme C suivant ?

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char str[] = "memmove est tres utile......";
    memmove(str + 17, str + 12, 10);
    printf("%s\n", str);
    return EXIT_SUCCESS;
}
```

## Solutions :

## Exercice 2.21 Initialisation d'une matrice

Écrire une fonction C sans valeur de retour (void) qui initialise une matrice m x n de int avec
des 1 sur les 4 "bords" et des 0 partout ailleurs.
Écrire aussi un petit programme de test permettant de vérifier le bon fonctionnement de votre
fonction.

## Solutions :

## Exercice 2.22 Somme des valeurs d'une matrice

Écrire une fonction C qui renvoie la somme des coefficients de la matrice m x n de double
passée en paramètre.
Écrire aussi un petit programme de test permettant de vérifier le bon fonctionnement de votre
fonction sur la matrice 3 x 4 suivante :

$$M =
\begin{pmatrix}
1 & 2.5 & 3 & 4\\
5 & 6 & 7.5 & 8\\
9.5 & 10 & 11 & 12
\end{pmatrix}$$

## Solutions :

## Exercice 2.23 Diagonale d'une matrice carrée

Ecrire une fonction C qui prend en paramètre une matrice n x n de int et qui renvoie en valeur
de retour le vecteur correspondant aux éléments de la diagonale gauche de ladite matrice.
Exemple : Si matrice =

$$\begin{pmatrix} 
1 & 2 & 3\\ 
4 & 5 & 6\\ 
7 & 8 & 9 
\end{pmatrix}$$

La fonction doit renvoyer le vecteur :

$$\begin{pmatrix} 
1\\ 
5\\ 
9 
\end{pmatrix}$$

Écrire aussi un petit programme de test permettant de vérifier le bon fonctionnement de votre
fonction.

## Solutions :

## Exercice 2.24 Calcul d'une intégrale

Écrire une fonction C permettant d'intégrer, par la méthode des trapèzes, n'importe quelle
fonction f(x) (x de type double) entre deux bornes A et B (également de type double). Le
nombre de pas d'intégration est aussi un paramètre de la fonction d'intégration.

Tester votre fonction d'intégration en écrivant un petit programme permettant de calculer :

$$\ \int_{0}^{\infty} e^(-x^2) \,dx \  ( = \sqrt{\pi}/2 = 0.886227)$$

$$\ \int_{0}^{\pi/2} sin(x) \,dx \  ( = 1)$$
