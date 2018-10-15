#include <stdio.h>
#include <stdlib.h>

// Methods declarations
int multiple(int, int);

// Main
int main(int argc, char* argv[]) {

  // Validation
  if (argc != 3) {
    printf("Usage: %s <number a> <number b>.\n", argv[0]);
    
    return 1;
  }

  char *message = "NOT MULTIPLE";

  // Arguments
  int num_a = atoi(argv[1]);
  int num_b = atoi(argv[2]);

  if (multiple(num_a, num_b)) {
    message = "MULTIPLE";
  }

  printf("The number %d is %s of %d.\n", num_b, message, num_a);

  return 0;
}

// Methods definitions
/* Multiple */
int multiple(int a, int b) {
  if (b % a == 0) {
    return 1;
  } 

  return 0;
} 