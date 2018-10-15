#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

  //Validation.
  if (argc != 2) {
    printf("Usage: p1 <value int>\n");

    return 1;
  }

  int sale = atoi(argv[1]);
  double commission = 0;

  // If the value is negative.
  if (sale < 0) {
    printf("Positive values only.\n");

    return 1;
  } 

  // Commission value.
  if (sale > 0 && sale <= 20000) {
    commission = sale * 0.05;
  } else if (sale > 20000 && sale <= 50000) {
    commission = sale * 0.07;
    commission += 1000;
  } else if (sale > 50000) {
    commission = sale * 0.1;
    commission += 3100;
  }

  printf("The commission is: %.3f.\n", commission);

  return 0;
}