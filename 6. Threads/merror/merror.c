#include "merror.h"


void error_usage(char *filename) {
    printf("Error: Usage isn't correct.\n\n");
    printf("Try again.\n");
    printf("\t%s <execution_option> <file_a> <file_b> <optional: #threads> \n", filename);
    printf("\texecution_option: Type of execution.\n");
    printf("\ts: Sequential.\n");
    printf("\tp: Parallel\n");

    exit(EXIT_FAILURE);
}

void error_vector_diff(int a, int b) {
    printf("Error: Vectors have different sizes (%d and %d).\n\n", a, b);
    printf("Try again.\n");
    printf("\tVectors must have the same size.\n");

    exit(EXIT_FAILURE);
}

void error_thread_create(int id) {
    printf("Error: Thread[%d] creation failed.\n", id);
    printf("Try again.\n");
    printf("\tVerify ERRORS in man pthread_create.\n");

    exit(EXIT_FAILURE);
}

void error_thread_join(int status, int id) {
    printf("Error: Thread[%d] joining (status: %d) failed.\n", id, status);
    printf("Try again.\n");
    printf("\tVerify ERRORS in man pthread_join.\n");

    exit(EXIT_FAILURE);
}