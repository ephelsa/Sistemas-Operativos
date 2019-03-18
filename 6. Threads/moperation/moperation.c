#include <stdio.h>
#include <stdlib.h>

#include "moperation.h"


void s_multiplication(int *v_a, int *v_b, int **ans, int size) {
    int *mul = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        mul[i] = v_a[i] * v_b[i];
    }

    *ans = mul;
}

int s_sum(int *vector, int size) {
    int total_sum = 0;

    for(int i = 0; i < size; i++) {
        total_sum += vector[i];
    }

    return total_sum;
}