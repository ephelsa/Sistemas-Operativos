#include <stdio.h>
#include <math.h>


// Method's declaration
double geometricProgression(double, double);

// Main
int main(int argc, char *argv[]) {
  double number_x, number_n;

  // Read the numbers
  printf("Number X: ");
  scanf("%lf", &number_x);

  printf("Number N: ");
  scanf("%lf", &number_n);
  
  printf("The answer is %.0lf.\n", geometricProgression(number_x, number_n));

  return 0;
}

// Method's definition
double geometricProgression(double x, double n) {
  
  double value = 0;
  double expo;

  for (expo = 0; expo <= n; expo++) {
    value += pow(x, expo);
  }

  return value;
}