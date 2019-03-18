#include <stdio.h>
#include <stdlib.h>

#include "merror.h"


void usageError(char *filename) {
    printf("Error: Usage isn't correct.\n\n");
    printf("Try again.\n");
    printf("\t%s <execution_option> <file_a> <file_b> <optional: #threads> \n", filename);
    printf("\texecution_option: Type of execution.\n");
    printf("\ts: Sequential.\n");
    printf("\tp: Parallel\n");

    exit(EXIT_FAILURE);
}

void vectorDifError(int a, int b) {
    printf("Error: Vectors have different sizes (%d and %d).\n\n", a, b);
    printf("Try again.\n");
    printf("\tVectors must have the same size.\n");

    exit(EXIT_FAILURE);
}