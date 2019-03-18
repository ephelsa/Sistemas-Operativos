#include <stdio.h>
#include <stdlib.h>

#include "mfile/mfile.h"
#include "merror/merror.h"
#include "moperation/moperation.h"


typedef struct exeparams {
    int type_exe;
    char *fn_a;
    char *fn_b;
    int size;
    int threads;
}PARAMS;


void validateParams(int argc, char **argv, PARAMS *parameters);
void setVector(int **vector, char *filename, int *size);


int main(int argc, char **argv) {

    PARAMS parameters;
    validateParams(argc, argv, &parameters);

    int *vector_a;
    int *vector_b;
    int *ans;
    
    setVector(&vector_a, parameters.fn_a, &parameters.size);
    setVector(&vector_b, parameters.fn_b, &parameters.size);

    s_multiplication(vector_a, vector_b, &ans, parameters.size);

    printf("Mul1: %d\n", ans[0]);
    printf("Mul2: %d\n", ans[1]);
    printf("Mul3: %d\n", ans[2]);

    printf("Answer: %d\n", s_sum(ans, parameters.size));

    free(vector_a);
    free(vector_b);
    free(ans);
    
    return 0;
}

void validateParams(int argc, char **argv, PARAMS *parameters) {
    if (argc == 4 || argc == 5) {
        if (argv[1][0] == 's' || argv[1][0] == 'S' || argv[1][0] == 'p' || argv[1][0] == 'P') {
            parameters->type_exe = argv[1][0];
        }
        else {
            usageError(argv[0]);
        }

        parameters->fn_a = argv[2];
        parameters->fn_b = argv[3];

        parameters->size = -1;

        if (argc == 5)
            parameters->threads = atoi(argv[4]);
        else
            parameters->threads = 0;
    } else {
        usageError(argv[0]);        
    }
}

void setVector(int **vector, char *filename, int *size) {
    FILE *fn = openFile(filename, "r");
    int msize = getFileLines(&fn);

    getFileData(&fn, vector, msize);

    closeFile(&fn);

    if (*size != msize && *size != -1)
        vectorDifError(*size, msize);

    *size = msize;
}