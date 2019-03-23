#ifndef __M_OPERATION__
#define __M_OPERATION__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>

#include "../merror/merror.h"

/**************************************************************/
/* Purpose: Manipulate the operations to know the dot product.*/
/**************************************************************/

/**
 * Purpose: Store all info relationated with the dot product.
*/
typedef struct vector_info {
    double *a;
    double *b;
    double sum;
    int size;
    int diff;
    int threads;
} VINFO;

/**
 * Purpose: Store the thread information.
*/
typedef struct thread_args {
    VINFO *v;
    int id;
    int start;
    int end;
    pthread_mutex_t *mutex;
    pthread_t *handler;
} TH_ARGS;

const VINFO VINFO_INITIALIZER;
const int STATUS_SUCCESS;


void s_operation(double *elapsed_time, VINFO *v);
void p_operation(double *elapsed_time, VINFO *v);

void freeVINFO(VINFO *v);

#endif