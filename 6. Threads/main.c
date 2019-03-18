#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

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

typedef struct elapsedtime {
    float settings;
    float operations;
}TIME;


void validateParams(int argc, char **argv, PARAMS *parameters);
void setVector(int **vector, char *filename, int *size);


int main(int argc, char **argv) {

    TIME elapsed_time;
    PARAMS parameters;
    struct timeval start, end;

    elapsed_time.settings = omp_get_wtime(); // Setting time

    validateParams(argc, argv, &parameters);

    int *vector_a;
    int *vector_b;
    int *ans;
    int sum = 0;
    
    setVector(&vector_a, parameters.fn_a, &parameters.size);
    setVector(&vector_b, parameters.fn_b, &parameters.size);

    elapsed_time.settings = omp_get_wtime() - elapsed_time.settings;    // Setting elapsed time

    elapsed_time.operations = omp_get_wtime();
    s_multiplication(vector_a, vector_b, &ans, parameters.size);
    
    sum =  s_sum(ans, parameters.size);
    gettimeofday(&end, NULL);   // Operation time

    elapsed_time.operations = omp_get_wtime() - elapsed_time.operations;



    /* Free memory allocated */
    free(vector_a);
    free(vector_b);
    free(ans);









    printf("Size: %d\n", parameters.size);
    printf("Answer: %d\n", sum);

    printf("Settings time: %lf seconds\n", elapsed_time.settings);
    printf("Operation time: %lf seconds\n", elapsed_time.operations);
    printf("Elapsed time: %lf seconds\n", (elapsed_time.settings + elapsed_time.operations));


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