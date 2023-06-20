# Chapitre 3 : Types composés

## Exercice 3.1 Correction d’erreurs

Réécrire complètement le code ci-dessous de telle sorte à corriger toutes les maladresses et
erreurs qu’il contient.
Une fois dûment corrigé le programme devrait afficher à l’exécution :

```a = 1, b = "ABC"```

**NB** Aucune ligne de code ne doit être ajoutée ou supprimée.

```c
#include <stdio.h>
#include <stdlib.h>

struct S {
    int a,
    char b[3]
}

void afficher(S *s);

int main(void) {
    S s = {a = 1; b = "ABC"};
    afficher(s);
    return EXIT_SUCCESS;
}

void afficher(S *s) {
    printf("a = %d, b = " % s
    "\n", s.a, s.b);
}
```

## Solutions :

```c
#include <stdio.h>
#include <stdlib.h>

struct S {
    int a;
    char b[3];
};

void afficher(struct S *s);

int main(void) {
    struct S s = {.a = 1, .b = "ABC"};
    afficher(&s);
    return EXIT_SUCCESS;
}

void afficher(struct S *s) {
    printf("a = %d, b = \"%s\"\n", (*s).a, (*s).b);
}
```

## Exercice 3.2 Affichage d'une personne (1)

On suppose qu'une personne se caractérise par :

- son nom (20 caractères effectifs au maximum)
- sa taille en cm (type uint8_t)
- la couleur de ses yeux (type enum; couleurs possibles : bleu, vert, gris, marron, noir)

Écrire un programme C qui, dans un premier temps, déclare, le plus proprement possible, tous
les types nécessaires à la modélisation d'une personne (n'hésitez pas à faire usage de typedef)
et qui, dans un second temps, déclare/définit deux fonctions (sans valeur de retour) afficher_1
et afficher_2, permettant d'afficher l'ensemble des caractéristiques de la personne passée en
paramètre. L'argument de la fonction afficher_1 doit être passé par valeur, celui de afficher_2,
par adresse.

Testez votre programme en considérant comme exemple de personne : Toto qui mesure 180
cm et qui a les yeux bleus.

## Solutions :

```c
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define TAILLE_NOM_MAX 20

typedef enum {
    bleu, vert, gris, marron, noir
} YEUX;

const char *couleurYeux[] = {"bleu", "vert", "gris", "marron", "noir"};


typedef struct {
    char *nom[TAILLE_NOM_MAX];
    uint8_t taille; // en [cm]
    YEUX yeux;
} Personne;

void afficher_1(Personne p);

void afficher_2(Personne *p);


int main(void) {
    Personne test = {.nom="TOTO", .taille=180, .yeux=bleu};
    afficher_1(test);
    afficher_2(&test);
    return EXIT_SUCCESS;
}

void afficher_1(Personne p) {
    printf("Nom = %s, Taille = %d, Couleur des yeux = %s\n", *p.nom, p.taille, couleurYeux[p.yeux]);
}

void afficher_2(Personne *p) {
    printf("Nom = %s, Taille = %d, Couleur des yeux = %s\n", *(p->nom), p->taille, couleurYeux[p->yeux]);
}
```

## Exercice 3.3 Affichage de plusieurs personnes

Essentiellement le même exercice que le précédent, mais on souhaite ici afficher non pas une
personne, mais plusieurs.

Plus précisément, il est demandé :

- de modéliser le concept de Personne en s’affranchissant de la contrainte des 20 caractères
max pour le nom
- de déclarer un tableau contenant les 3 personnes suivantes :
  - Paul qui mesure 180 cm et qui a les yeux bleus
  - Pierre qui mesure 175 cm et qui a les yeux verts
  - Jean-Jacques qui mesure 182 cm et qui a les yeux marron
- d'écrire :
  - une fonction permettant l'affichage d'une personne (passée par adresse)
  - une fonction permettant l'affichage d'un tableau de personnes

Exemple d'exécution du programme :
```
  Nom    : Paul
  Taille : 180
  Yeux   : bleus
  
  Nom    : Pierre
  Taille : 175
  Yeux   : verts
  
  Nom    : Jean-Jacques
  Taille : 182
  Yeux   : marron
```

## Solutions :

```c
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define TAILLE_NOM_MAX 20

typedef enum {
    bleu, vert, gris, marron, noir
} YEUX;

const char *couleurYeux[] = {"bleu", "vert", "gris", "marron", "noir"};


typedef struct {
    char *nom[TAILLE_NOM_MAX];
    uint8_t taille; // en [cm]
    YEUX yeux;
} Personne;

void afficher_1(Personne p);

void afficher_2(Personne *p);

void afficher_personne(Personne *p);
void afficher_tableau(Personne TABLEAU[], size_t size);


int main(void) {
    Personne PARTICIPANTS[] = {{.nom="Paul", .taille=180, .yeux=bleu},
                               {.nom="Pierre", .taille=175, .yeux=vert},
                               {.nom="Jean-Jacques", .taille=182, .yeux=marron},
    };

    const size_t SIZE = sizeof(PARTICIPANTS)/sizeof(Personne);

    afficher_tableau(PARTICIPANTS, SIZE);

    return EXIT_SUCCESS;
}

void afficher_personne(Personne *p) {
    printf("%-7s: %s\n%-7s: %d\n%-7s: %s\n", "Nom", *(p->nom), "Taille", p->taille, "Yeux", couleurYeux[p->yeux]);
}

void afficher_tableau(Personne TABLEAU[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        afficher_personne(&TABLEAU[i]);
        printf("\n");
    }
}
```

## Exercice 3.4 Lendemain d’une date

Écrire un programme C qui détermine et affiche le lendemain d’une date donnée.
Exemple Le lendemain du 30.04.2016 est le 01.05.2016
Précisions

- Implémenter le concept de date sous la forme d’une structure à 3 membres : 
jour (de type uint_8), mois (de type uint_8) et année (de type uint16_t)
- Structurer le code en fonctions
- Tenir compte des années bissextiles dans le calcul du lendemain
- Afficher les dates au format jj.mm.aaaa

## Solutions :

```c
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Format d'affichage d'une date (jj.mm.aaaa)
const char *const FORMAT_DATE = "%02" PRIu8 ".%02" PRIu8 ".%04" PRIu16;
// Taille (nb de caractères) du format (jj.mm.aaaa)
const uint8_t TAILLE_FORMAT_DATE = 10;
typedef struct {
    uint8_t jour;
    uint8_t mois;
    uint16_t annee;
} Date;

uint8_t nbJoursDansMois(uint8_t mois, uint16_t annee);

bool estBissextile(uint16_t annee);

const char *toString(const char *format, uint8_t taille_format, const Date *d);

Date lendemain(const Date *d);

void test(const char *format, uint8_t taille_format, const Date *d);

int main(void) {
    test(FORMAT_DATE, TAILLE_FORMAT_DATE, &(Date) {28, 2, 2000});
    test(FORMAT_DATE, TAILLE_FORMAT_DATE, &(Date) {29, 2, 2000});
    test(FORMAT_DATE, TAILLE_FORMAT_DATE, &(Date) {30, 11, 2000});
    test(FORMAT_DATE, TAILLE_FORMAT_DATE, &(Date) {31, 12, 2000});
    return EXIT_SUCCESS;
}

uint8_t nbJoursDansMois(uint8_t mois, uint16_t annee) {
    static const uint8_t NB_JOURS_DANS_MOIS[] = {31, 28, 31, 30, 31, 30,
                                                 31, 31, 30, 31, 30, 31};
    if (mois == 2 && estBissextile(annee))
        return (uint8_t) (NB_JOURS_DANS_MOIS[1] + 1);
    else
        return NB_JOURS_DANS_MOIS[mois - 1];
}

bool estBissextile(uint16_t annee) {
    return annee % 400 == 0 || (annee % 4 == 0 && annee % 100);
}

const char *toString(const char *format, uint8_t taille_format, const Date *d) {
    char *str = (char *) calloc(taille_format + 1, sizeof(char));
    if (str)
        sprintf(str, format, d->jour, d->mois, d->annee);
    return str;
}

Date lendemain(const Date *d) {
    Date lendemain;
    if (d->jour != nbJoursDansMois(d->mois, d->annee))
        lendemain = (Date) {(uint8_t) (d->jour + 1), d->mois, d->annee};
    else if (d->mois < 12)
        lendemain = (Date) {1, (uint8_t) (d->mois + 1), d->annee};
    else
        lendemain = (Date) {1, 1, (uint16_t) (d->annee + 1)};
    return lendemain;
}

void test(const char *format, uint8_t taille_format, const Date *d) {
    Date leLendemain = lendemain(d);
    const char *const STR1 = toString(format, taille_format, d);
    const char *const STR2 = toString(format, taille_format, &leLendemain);
    printf("Le lendemain du %s est le %s\n", STR1, STR2);
    free((char *) STR1);
    free((char *) STR2);
}
```


## Exercice 3.5 Taille d’une structure

a) Soit la structure S1 suivante :
```c
struct S1 {
    int* ptr;
    int32_t a;
    int64_t b;
};
```
Quelle est la taille en bytes de S1
1) en architecture 32 bits ?
2) en architecture 64 bits ?

b) Soit la structure S2 suivante :
```c
struct S2 {
    int8_t a;
    int16_t b;
    char c;
    double* ptr;
};
```
   Quelle est la taille en bytes de S2
1) en architecture 32 bits ?
2) en architecture 64 bits ? 

## Solutions :

#### a) 
1) 12
2) 24

#### b)
1) 12
2) 16


## Exercice 3.6 Affichage d’une personne (2)

On souhaite modéliser des personnes, certaines de nationalité suisse, d'autres pas.
On suppose que toute personne (qu'elle soit suisse ou non) se caractérise par un nom (20
caractères effectifs max).

Pour les personnes de nationalité suisse, on souhaite (en plus du nom) aussi enregistrer le taux
d'activité exercé (entier exprimé en %).

Pour les personnes de nationalité étrangère, on souhaite (en plus du nom) aussi enregistrer le
type de permis de travail dont elle dispose (permis A, B ou C; à implémenter en tant que type
énuméré).

Écrire un programme C, qui, après avoir déclaré le plus proprement possible les types
nécessaires à la résolution de notre problème, déclare/initialise les 2 personnes suivantes :
- "Toto", suisse travaillant à 80%
- "Titi", étranger avec permis C

… puis affiche à l'écran l'ensemble des caractéristiques de chacune de ces 2 personnes.
Exemple d'exécution du programme :

```
Nom           : Toto
Nationalite   : Suisse
Taux activite : 80%

Nom           : Titi
Nationalite   : Etranger
Type permis   : C
```

## Solutions :

```c
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define TAILLE_NOM_MAX 20

typedef enum {
    A, B, C
} PERMIS_DE_SEJOUR;

const char *get_permis_de_sejour[] = {"A", "B", "C"};


typedef enum {
    Suisse, Etranger
} NATIONALITE;

const char *get_nationalite[] = {"Suisse", "Etranger"};

typedef union {
    uint8_t taux_activite;
    PERMIS_DE_SEJOUR permis_de_sejour;
} Specificites_nationalite;

typedef struct {
    const char *nom[TAILLE_NOM_MAX];
    NATIONALITE nationalite;
    Specificites_nationalite spec;
} Personne;

void affiche_personne(Personne *personne);


int main(void) {
    Personne personne_1 = {.nom="Toto", .nationalite=Suisse, .spec={.taux_activite=80}};
    Personne personne_2 = {.nom="Titi", .nationalite=Etranger, .spec={.permis_de_sejour=C}};
    affiche_personne(&personne_1);
    affiche_personne(&personne_2);

    return EXIT_SUCCESS;
}

void affiche_personne(Personne *personne) {
    printf("%-15s: %s\n%-15s: %s\n%-15s: ", "Nom", *(personne->nom), "Nationalite",get_nationalite[personne->nationalite], "Taux activite");
    if(personne->nationalite == Suisse)
        printf("%d%%\n", personne->spec.taux_activite);
    else
        printf("%s\n", get_permis_de_sejour[personne->spec.permis_de_sejour]);
}
```


