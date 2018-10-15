#include <stdio.h>
#include <math.h>

// Method declaration
int factorial(int);
double calculateSerie(int, int);

// Main
int main(int argc, char *argv[]) {
  int number_x = 0, number_n = 0;

  // Read the numbers
  printf("X value: ");
  scanf("%d", &number_x);

  printf("Number of terms: ");
  scanf("%d", &number_n);

  printf("Result: %lf\n", calculateSerie(number_x, number_n));

  return 0;
}

// Method definition
/* To calculate the factorial */
int factorial(int number) {
  int fac = 1;
  int counter;

  for (counter = 1; counter <= number; counter++) {
    fac *= counter;
  }

  return fac;
}

/* To calculate the serie */
double calculateSerie(int x, int n) {
  double serie = 0; // The serie start's at 0
  int counter;

  for (counter = 0; counter < n; counter++) {
    int expo = counter * 2; // This is the reason to change
    int facto = factorial(expo);  // Calculate the factorial

    double number = pow(x, expo) / facto; // The result of individual opertation

    if (counter % 2 == 0) {
      serie += number;
      printf(" + ");

    } else {
      serie -= number;
      printf(" - ");
    }

    printf("%d^%d/%d!", x, expo, expo);
  }

  printf("\n");

  return serie; // The result of the serie
}
