#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

  // Input
  int final_value;
  printf("Final result (Starting at 1): ");
  scanf("%d", &final_value);

  // Counters
  int f_value;
  int s_value;

  for (f_value = 1; f_value <= 10; f_value++) {
    for (s_value = 1; s_value <= final_value; s_value++) {
      printf("%dx%d=%d\t", s_value, f_value, f_value*s_value);
    }

    printf("\n");
  }

  printf("\n");

  return 0;
}