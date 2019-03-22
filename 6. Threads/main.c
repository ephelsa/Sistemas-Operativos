#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#include "mfile/mfile.h"
#include "merror/merror.h"
#include "moperation/moperation.h"

#define SEC 0
#define PAR 1

typedef struct exeparams {
    short type_exe;
    char *fn_a;
    char *fn_b;
    int threads;
}PARAMS;

typedef struct elapsedtime {
    double settings;
    double operation;
}TIME;


void validateParams(int argc, char **argv, PARAMS *parameters);
void setVector(double **vector, char *filename, int *size);
void parallelOperation(double *elapsed_time, VINFO *v);


int main(int argc, char **argv) {

    TIME elapsed_time;
    PARAMS parameters;
    VINFO vectors = VINFO_INITIALIZER;

    /* Settings */
    elapsed_time.settings = omp_get_wtime(); // Setting time
    validateParams(argc, argv, &parameters);
    vectors.threads = parameters.threads;
    setVector(&vectors.a, parameters.fn_a, &vectors.size);
    setVector(&vectors.b, parameters.fn_b, &vectors.size);
    elapsed_time.settings = omp_get_wtime() - elapsed_time.settings;    // Setting elapsed time

    /* Sequential */
    //elapsed_time.operation = omp_get_wtime();  // Elapsed time
    //s_operation(&vectors);
    //elapsed_time.operation = omp_get_wtime() - elapsed_time.operation;    // Operations elpased

    /* Parallel */
    parallelOperation(&(elapsed_time.operation), &vectors);
    //pthread_exit(NULL);

    printf("Size: %d\n", vectors.size);
    printf("Answer: %lf\n", vectors.sum);

    printf("Settings time: %lf seconds\n", elapsed_time.settings);
    printf("Operation time: %lf\n", elapsed_time.operation);
    printf("Elapsed time: %lf seconds\n", (elapsed_time.settings + elapsed_time.operation));


    /* Free memory allocated */
    freeVINFO(&vectors);




    return 0;
}

void validateParams(int argc, char **argv, PARAMS *parameters) {
    if (argc == 4 || argc == 5) {
        if (argv[1][0] == 's' || argv[1][0] == 'S') {
            parameters->type_exe = SEC;
        } else if(argv[1][0] == 'p' || argv[1][0] == 'P') {
            parameters->type_exe = PAR;
        }
        else {
            error_usage(argv[0]);
        }

        parameters->fn_a = argv[2];
        parameters->fn_b = argv[3];

        if (argc == 5)
            parameters->threads = atoi(argv[4]);
        else
            parameters->threads = 0;
    } else {
        error_usage(argv[0]);        
    }
}

void setVector(double **vector, char *filename, int *size) {
    FILE *fn = openFile(filename, "r");
    int msize = getFileLines(&fn);

    getFileData(&fn, vector, msize);

    closeFile(&fn);

    if (*size != msize && *size != -1)
        error_vector_diff(*size, msize);

    *size = msize;
}

/* creation*, joining*, size % threads != 0, size < threads */

// Modificar el start i + loqueseagregue y el end + lo que se agregye
// verificar con modulos ejem 31 % 16

void parallelOperation(double *elapsed_time, VINFO *v) {
    *elapsed_time = omp_get_wtime();  // Elapsed time
    pthread_t th_handler[v->threads];
    void *status;
    TH_ARGS th_args[v->threads];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    for (int i = 0; i < v->threads; i++) {
        int th;

        th_args[i].v = v;
        th_args[i].id = i;
        th_args[i].start = ((v->size * i) / v->threads);
        th_args[i].end = (v->size / v->threads) + th_args[i].start - 1;
        th_args[i].mutex = &mutex;

        th = pthread_create(&th_handler[i], 
                        NULL, 
                        (void *) p_operation, 
                        (void *) &th_args[i]);

        if (th != 0) 
            error_thread_create(th_args[i].id);


        printf("[%d] Start: %d - End: %d\n", i, th_args[i].start, th_args[i].end);
    }

    for (int i = 0; i < v->threads; i++) {
        int th = pthread_join(th_handler[i], &status);

        if (th != 0)
            error_thread_join((intptr_t)status, th_args[i].id);


        printf("Thread [%d] - Status %ld\n", th_args[i].id, (intptr_t)status);
    }
    *elapsed_time = omp_get_wtime() - *(elapsed_time);    // Operations elpased


    pthread_mutex_destroy(&mutex);
}