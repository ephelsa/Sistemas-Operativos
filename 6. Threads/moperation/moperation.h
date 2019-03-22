#ifndef __M_OPERATION__
#define __M_OPERATION__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct vector_info {
    double *a;
    double *b;
    double sum;
    int size;
    int threads;
} VINFO;

typedef struct thread_args {
    VINFO *v;
    int id;
    int start;
    int end;
    pthread_mutex_t *mutex;
} TH_ARGS;


const VINFO VINFO_INITIALIZER;
const int STATUS_SUCCESS;


void s_operation(VINFO *v);
void p_operation(TH_ARGS *th_args);

void freeVINFO(VINFO *v);

#endif