#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Method declaration
int launch();

int main() {
  int n_launches, c = 0, s = 0;
  char launched;

  // Read the number of launches
  printf("Number of launches: ");
  scanf("%d", &n_launches);

  // To calculate the launches
  while(n_launches > 0) {
    n_launches--;

    if (launch() == 0) {
      launched = 'C';
      c++;
    } else {
      launched = 'S';
      s++;
    }

    printf("%c", launched);
  }
  printf(", #C = %d and #S = %d\n", c, s);

  return 0;
}

// Method definition
/* This method only calculate the launched once */
int launch() {
  int random;

  srand(time(NULL));
  random = rand() % 2; // For 0 and 1

  return random;
}