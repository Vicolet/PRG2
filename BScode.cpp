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