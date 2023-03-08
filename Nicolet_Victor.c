/*
 -----------------------------------------------------------------------------------
 Nom du fichier : <Nicolet_Victor>.<c>
 Auteur(s)      : <Victor> <Nicolet>
 Date creation  : <08.03.2023>

 Description    : <Pratiquer les notions vues dans le chapitre 1 (Introduction) du cours.>

 Remarque(s)    : <� compl�ter>

 Compilateur    : Mingw-w64 gcc 12.2.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define sommer(a,b) ((a) + (b))

#define afficher(c, ...) do { \
printf(" ligne %d:  ", __LINE__);        \
printf(c,##__VA_ARGS__);      \
printf("\n");                 \
} while(0)

int main(void) {
    afficher("%d", sommer(1, 2));
    afficher("%d", sommer(INT_MIN, -1));
    afficher("%d", sommer(INT_MAX, 1));

    afficher("%lld", sommer(3LL, 4LL));
    afficher("%lld", sommer(LLONG_MIN, -1));
    afficher("%lld", sommer(LLONG_MAX, 1));

    const bool INCLURE_CAS_SPECIAL = true;

    if (INCLURE_CAS_SPECIAL)
        afficher("%lld - %lld", sommer(INT_MIN, -1LL), sommer(INT_MAX, 1LL));
    else
        afficher("%s", "Calcul spécial pas inclus.");

    return EXIT_SUCCESS;
}

/*
ligne 34 : 3
ligne 35 : -2147483648
ligne 36 : 2147483647
ligne 38 : 7
ligne 39 : -9223372036854775808
ligne 40 : 9223372036854775807
ligne 45 : -2147483649 - 2147483648
 */
