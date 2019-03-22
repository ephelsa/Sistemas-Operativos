#include "moperation.h"

const VINFO VINFO_INITIALIZER = { NULL, NULL, 0, -1 ,0 };
const int STATUS_SUCCESS = 10;


void s_operation(VINFO *v) {
    for (int i = 0; i < v->size; i++)
        v->sum += v->a[i] * v->b[i];
}

void p_operation(TH_ARGS *th_args) {    
    double m_sum = 0;

    /* Size < thread sol  */
    for (int i = th_args->start; i <= th_args->end; i++) {
        m_sum += th_args->v->a[i] * th_args->v->b[i];

        printf("[%d] Executing -> %f x %f\n", th_args->id, th_args->v->a[i], th_args->v->b[i]);
    }


    pthread_mutex_lock(th_args->mutex);
    th_args->v->sum += m_sum;
    pthread_mutex_unlock(th_args->mutex);

    pthread_exit((void *)(intptr_t)STATUS_SUCCESS);
}

void freeVINFO(VINFO *v) {
    free(v->a);
    free(v->b);

    v->a = NULL;
    v->b = NULL;
}