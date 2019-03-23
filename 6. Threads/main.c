#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mfile/mfile.h"
#include "merror/merror.h"
#include "moperation/moperation.h"

#define SEC 0
#define PAR 1

/**
 * Purpose: Store in this data structure the parameters passed though arguments.
*/
typedef struct exeparams {
    short type_exe;
    char *filename;
    char *fn_a;
    char *fn_b;
    int threads;
}PARAMS;

/**
 * Purpose: Store in this data structure the time of:
 *          Setting (parameters validation and set the vectors with data from files).
 *          Operation (time taken to do the dot product).      
*/
typedef struct elapsedtime {
    double settings;
    double operation;
}TIME;


/********************/
/*** Declarations ***/
/********************/
void validate_params(int argc, char **argv, PARAMS *parameters);
void set_vector(double **vector, char *filename, int *size);
void start(PARAMS p, double *operation_time, VINFO *v);


const PARAMS PARAMS_INITIALIZER = { 0, NULL, NULL, NULL, 0 };
const TIME TIME_INITIALIZER = { 0, 0 };

/* Main method */
int main(int argc, char **argv) {
    /* Data structures initialization. */
    TIME elapsed_time = TIME_INITIALIZER;
    PARAMS parameters = PARAMS_INITIALIZER;
    VINFO vectors = VINFO_INITIALIZER;

    /* Settings. */
    elapsed_time.settings = omp_get_wtime(); // Setting time
    validate_params(argc, argv, &parameters);
    vectors.threads = parameters.threads;
    set_vector(&vectors.a, parameters.fn_a, &vectors.size);
    set_vector(&vectors.b, parameters.fn_b, &vectors.size);
    elapsed_time.settings = omp_get_wtime() - elapsed_time.settings;    // Setting elapsed time

    /* Operations. */
    start(parameters, &(elapsed_time.operation), &vectors);

    /* Print the results. */
    printf("Size: %d\n", vectors.size + vectors.diff);
    printf("Answer: %lf\n\n", vectors.sum);

    printf("Threads: %d\n", vectors.threads);
    printf("Settings time: %lf seconds\n", elapsed_time.settings);
    printf("Operation time: %lf seconds\n", elapsed_time.operation);
    printf("Elapsed time: %lf seconds\n", (elapsed_time.settings + elapsed_time.operation));


    /* Free memory allocated */
    freeVINFO(&vectors);


    exit(EXIT_SUCCESS);
}

/**
 * Purpose: Validate the parameters and store these in PARAMS structure.
 * 
 * @params int number of parameters.
 * @params char array with parameters.
 * @params PARAMS data structure to store the information.
 * 
 * @return void.
*/
void validate_params(int argc, char **argv, PARAMS *parameters) {
    parameters->filename = argv[0];

    /* Validate the total of parameters. */
    if (argc == 4 || argc == 5) {
        /* Set if is sequential or parallel. If isn't one of both, shows a error. */
        if (argv[1][0] == 's' || argv[1][0] == 'S') {
            parameters->type_exe = SEC;
        } else if(argv[1][0] == 'p' || argv[1][0] == 'P') {
            parameters->type_exe = PAR;
        }
        else {
            error_usage(parameters->filename);
        }

        /* Store the filesname. */
        parameters->fn_a = argv[2];
        parameters->fn_b = argv[3];

        /* Store the number of threads. */
        if (argc == 5)
            parameters->threads = atoi(argv[4]);
        else
            parameters->threads = 1;
    } else {
        error_usage(argv[0]);        
    }
}

/**
 * Purpose: Store a vector array with data from a file.
 * 
 * @params double Pointer of vector to store the data.
 * @params char name of the file that contains the vector.
 * @params int pointer to store the size the vectors.
 * 
 * @return void.
*/
void set_vector(double **vector, char *filename, int *size) {
    FILE *fn = openFile(filename, "r");
    int msize = getFileLines(&fn);

    getFileData(&fn, vector, msize);

    closeFile(&fn);

    /* If is equals to the default size, that's mean this is the first file analyzed. */
    if (*size != msize && *size != VINFO_INITIALIZER.size)
        error_vector_diff(*size, msize);

    /* Store in the structure. */
    *size = msize;
}

/**
 * Purpose: Start the operation by validating if it is sequential or parallel.
 * 
 * @params PARAMS to know the execution type.
 * @params double Pointer to store the operation time.
 * @params VINFO to know the vector information and store the dot product.
 * 
 * @return void.
*/
void start(PARAMS p, double *operation_time, VINFO *v) {
    if (p.type_exe == SEC) 
        s_operation(operation_time, v);
    else if (p.type_exe == PAR)
        p_operation(operation_time, v);
    else
        error_usage(p.filename);
}
