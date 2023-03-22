#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n = 127;                    // |127b|
	double x = 12.3456;             // |0127|
	printf("R1 : |%-4d|\n", n);     // |7f|
	printf("R2 : |%04d|\n", n);     // |0177|
	printf("R3 : |%x|\n", n);       // |12.345600|
	printf("R4 : |%#o|\n", n);      // |12.35|
	printf("R5 : |%f|\n", x);       // |1.23e+01|
	printf("R6 : |%5.2f|\n", x);    // |12.3456|
	printf("R7 : |%.2e|\n", x);
	printf("R8 : |%g|\n", x);

	return EXIT_SUCCESS;
}