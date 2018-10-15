#include <stdio.h>
#include <memory.h>

// Method declaration
void reverseNumber(long);

int main(int argc, char * argv[]) {

  long normal_n;

  // Read the number
  printf("Type the number to reverse: ");
  scanf("%ld", &normal_n);

  // Answer
  printf("The normal number is [%ld].\n", normal_n);
  reverseNumber(normal_n);

  return 0;
}

// Method definition
void reverseNumber(long normal) {
  long helper = normal; // This is to don't modify the original number.
  int temp;

  printf("The reversed number is [");

  while(helper > 0) {
      temp = helper % 10;
      printf("%d", temp);

      helper /= 10;
  }

  printf("].\n");
}