#include <stdio.h>

int main(int argc, char *argv[]) {
  // Get the line's number
  int number;
  
  // Receive the number
  printf("Type a number: ");
  scanf("%d", &number);

  // Counters
  int i_counter;
  int j_counter;
  
  int byte;

  for (i_counter = 1; i_counter <= number; i_counter++) {
    printf("[%d]\t", i_counter);
    
    for (j_counter = i_counter; j_counter < i_counter*2; j_counter++) {
      
      // Set byte
      if (j_counter % 2 == 0) {
        byte = 0;
      } else {
        byte = 1;
      }
      printf("%d", byte);
    }

    printf("\n");
  }

  return 0;
}