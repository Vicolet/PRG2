# Chapitre 5 : Fichiers

## Exercice 5.1 Lecture intégrale d'un fichier texte

On suppose disposer du fichier texte suivant :

> 1
> 
> 2
> 
> 3
> 
> 4
> 
> 5

Écrire le plus proprement possible un programme C qui permette d'afficher à l'écran le
contenu intégral de ce fichier.

## Solutions :

```c
#include <stdio.h>
#include <stdlib.h>

// mettre le chemin tu fichier sous format windows avec les \\ 2 backslashs
#define NOM_FICHIER "C:\\Users\\victo\\OneDrive\\HEIG-VD\\2022-2023\\PROGBS\\BSccode\\test.txt"

int main(void) {
    FILE *f = fopen(NOM_FICHIER, "r");
    if (!f) { // Si ouverture du fichier impossible
        printf("Ouverture du fichier \"%s\" impossible.\n", NOM_FICHIER);
        return EXIT_FAILURE;
    } else {
        int n;
        while (fscanf(f, "%d", &n) != EOF)
            printf("%d\n", n);
        // fermer le fichier
        fclose(f);
        return EXIT_SUCCESS;
    }
}
```

## Exercice 5.2 Écriture d'un fichier binaire
Écrire un programme C permettant de stocker dans un fichier binaire nommé personnes.dat
des données relatives à des personnes.

On suppose qu'une personne se caractérise par les propriétés suivantes :

- son nom (20 caractères max)
- son prénom (15 caractères max)
- son âge (de type unsigned short)

Les données des diverses personnes doivent être saisies par l'utilisateur. On conviendra que la
saisie se termine dès lors que l'utilisateur entre un nom de personne vide. 

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_NOM 20
#define TAILLE_MAX_PRENOM 15
typedef char Nom[TAILLE_MAX_NOM + 1];
typedef char Prenom[TAILLE_MAX_PRENOM + 1];
typedef unsigned short Age;

typedef struct {
    Nom nom;
    Prenom prenom;
    Age age;
} Personne;

void saisie(char *chaine, size_t taille);

void clear_stdin(void);

int main(void) {
    const char *const NOM_FICHIER = "C:\\Users\\victo\\OneDrive\\HEIG-VD\\2022-2023\\PROGBS\\BSccode\\test.txt";
    FILE *fichier = fopen(NOM_FICHIER, "wb");
    if (!fichier) {
        printf("Desole! Le fichier \"%s\" n'a pas pu etre ouvert", NOM_FICHIER);
        return EXIT_FAILURE;
    }
    Personne p;
    printf("--- Pour finir la saisie, donnez un nom 'vide' ---\n");
    do {
        printf("\nNom: ");
        saisie(p.nom, TAILLE_MAX_NOM);
        if (strlen(p.nom) == 0)
            break;
        printf("Prenom : ");
        saisie(p.prenom, TAILLE_MAX_PRENOM);
        printf("Age: ");
        scanf("%hu", &p.age);
        clear_stdin();
        fwrite(&p, sizeof(Personne), 1, fichier);
    } while (1);

    fclose(fichier);
    return EXIT_SUCCESS;
}

void saisie(char *chaine, size_t taille) {
    fgets(chaine, (int) taille + 1, stdin);
    clear_stdin();
    for (size_t i = 0; i < taille; ++i)
        if (chaine[i] == '\n') {
            chaine[i] = '\0';
            break;
        }
}

void clear_stdin(void) {
    fseek(stdin, 0, SEEK_END);
}
```

## Exercice 5.3 Lecture intégrale d'un fichier binaire

On suppose disposer du fichier binaire personnes.dat créé dans l'exercice précédent.

Écrire le plus proprement possible un programme C qui recopie le contenu intégral du fichier
binaire personnes.dat dans un fichier texte personnes.txt, histoire de rendre les informations
contenues dans le fichier binaire lisibles par un être humain.

Faire en sorte que les données du fichier texte apparaissent alignées en colonnes, comme suit :
```
Nom             Prenom              Age
Federer         Roger               37
Nadal           Rafael              33
Djokovic        Novak               32
del Potro       Juan Martin         30
```

## Solutions :
 ```c
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX_NOM 20
#define TAILLE_MAX_PRENOM 15
typedef char Nom[TAILLE_MAX_NOM + 1];
typedef char Prenom[TAILLE_MAX_PRENOM + 1];
typedef unsigned short Age;
typedef struct {
    Nom nom;
    Prenom prenom;
    Age age;
} Personne;

int main(void) {
    const char *const NOM_FICHIER_BINAIRE = "C:\\Users\\victo\\OneDrive\\HEIG-VD\\2022-2023\\PROGBS\\BSccode\\personne.dat";
    FILE *fichier_binaire = fopen(NOM_FICHIER_BINAIRE, "rb");
    if (!fichier_binaire) {
        printf("Desole! Le fichier \"%s\" n'a pas pu etre ouvert\n",
               NOM_FICHIER_BINAIRE);
        return EXIT_FAILURE;
    } else {
        const char *const NOM_FICHIER_TEXTE = "C:\\Users\\victo\\OneDrive\\HEIG-VD\\2022-2023\\PROGBS\\BSccode\\personne.txt";
        FILE *fichier_texte = fopen(NOM_FICHIER_TEXTE, "w");
        if (!fichier_texte) {
            printf("Desole! Le fichier \"%s\" n'a pas pu etre ouvert\n",
                   NOM_FICHIER_TEXTE);
            fclose(fichier_binaire);
            return EXIT_FAILURE;
        } else {
            Personne p;
            fprintf(fichier_texte, "%-*s %-*s %s\n",
                    TAILLE_MAX_NOM, "Nom", TAILLE_MAX_PRENOM, "Prenom", "Age");
            while (fread(&p, sizeof(Personne), 1, fichier_binaire)) {
                fprintf(fichier_texte, "%-*s %-*s %3hu\n",
                        TAILLE_MAX_NOM, p.nom, TAILLE_MAX_PRENOM, p.prenom, p.age);
            }
            fclose(fichier_binaire);
            fclose(fichier_texte);
            return EXIT_SUCCESS;
        }
    }
}
```

## Exercice 5.4 Recherche séquentielle dans un fichier binaire

Écrire un programme C permettant, à partir du fichier personnes.dat créé dans l'exercice 5.2,
de retrouver et d'afficher à l'écran les informations relatives à une personne de nom donné.

**Exemples d'exécution**

```
Quel nom recherchez-vous ? : Wawrinka
Desole! Le nom "Wawrinka" ne figure pas dans le fichier

Quel nom recherchez-vous ? : del Potro
Juan Martin del Potro, 30 ans
```

## Solutions :
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAILLE_MAX_NOM 20
#define TAILLE_MAX_PRENOM 15
typedef char Nom[TAILLE_MAX_NOM + 1];
typedef char Prenom[TAILLE_MAX_PRENOM + 1];
typedef unsigned short Age;
typedef struct {
    Nom nom;
    Prenom prenom;
    Age age;
} Personne;

void lire(char *chaine, size_t taille);

int main(void) {
    const char *const NOM_FICHIER = "C:\\Users\\victo\\OneDrive\\HEIG-VD\\2022-2023\\PROGBS\\BSccode\\personne.dat";
    FILE *fichier = fopen(NOM_FICHIER, "rb");
    if (!fichier) {
        printf("Desole! Le fichier \"%s\" n'a pas pu etre ouvert\n", NOM_FICHIER);
        return EXIT_FAILURE;
    } else {
        {
            Personne p;
            Nom nomRecherche;
            printf("Quel nom recherchez-vous ? : ");
            lire(nomRecherche, TAILLE_MAX_NOM);
            bool trouve = false;
            while (!trouve && fread(&p, sizeof(Personne), 1, fichier))
                trouve = strcmp(p.nom, nomRecherche) == 0;
            fclose(fichier);
            if (trouve)
                printf("%s %s, %hu ans\n", p.prenom, p.nom, p.age);
            else
                printf("Desole! Le nom \"%s\" ne figure pas dans le fichier\n",
                       nomRecherche);
            return EXIT_SUCCESS;
        }
    }
}

void lire(char *chaine, size_t taille) {
    fgets(chaine, (int) taille + 1, stdin);
    fseek(stdin, 0, SEEK_END);
    for (size_t i = 0; i < taille; ++i)
        if (chaine[i] == '\n') {
            chaine[i] = '\0';
            break;
        }
}
```