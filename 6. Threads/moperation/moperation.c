#include "moperation.h"

/* Is a VINFO default struct. */
const VINFO VINFO_INITIALIZER = { NULL, NULL, 0, -1 ,0, 0 };

/* Is the status used in pthread_exit and pthread_join */
const int STATUS_SUCCESS = 10;


/***********************/
/*** Private Methods ***/
/***********************/

void p_operation_init(TH_ARGS *th_args);

/**
 * Purpose: Do the calculation of dot product. This method is passed to pthread_create.
 * 
 * @params TH_ARGS contains all the necessary arguments to works.
 * 
 * @return void.
*/
void p_operation_init(TH_ARGS *th_args) {    
    /* Local sum of products vector. */
    double m_sum = 0;

    /* This condition help to works when the size of vectors is less than number of threads */
    for (int i = th_args->start; i <= th_args->end; i++) {
        m_sum += th_args->v->a[i] * th_args->v->b[i];

        //printf("[%d] Executing -> %f x %f\n", th_args->id, th_args->v->a[i], th_args->v->b[i]);
    }

    /* To avoid the RC on "global variable". */
    pthread_mutex_lock(th_args->mutex);
    th_args->v->sum += m_sum;
    pthread_mutex_unlock(th_args->mutex);

    /* Terminates the thread calls with the status_succes code. This code is the same at make join. */
    pthread_exit((void *)(intptr_t)STATUS_SUCCESS);
}


/**********************/
/*** Public Methods ***/
/**********************/

/**
 * Purpose: Make the dot product sequential.
 * 
 * @params double to calculate and store the elapsed time operating.
 * @params VINFO data structe to know the vectors and store the result.
 * 
 * @return void.
*/
void s_operation(double *elapsed_time, VINFO *v) {
    *elapsed_time = omp_get_wtime();  // Time start.
    /* Dot product calculation. */
    for (int i = 0; i < v->size; i++)
        v->sum += v->a[i] * v->b[i];

    *elapsed_time = omp_get_wtime() - *(elapsed_time);    // Time end.
}

/**
 * Purpose: Management the parallel operation. 
 *  
 * @params double to calculate and store the elapsed time operating.
 * @params VINFO data structe to know the vectors and store the result.
 * 
 * @return void.
*/
void p_operation(double *elapsed_time, VINFO *v) {
    /* Handlers to manipulate the threads. */
    pthread_t th_handler[v->threads];
    /* Mutex to lock the var to avoid a RC. */
    pthread_mutex_t mutex;
    /* To know the pthread_join status. */
    void *status;
    /* Threads information. */
    TH_ARGS th_args[v->threads];

    
    *elapsed_time = omp_get_wtime();  // Time start.

    /* Mutex initialization. This returns 0 is was successful. */
    int mutex_ans = pthread_mutex_init(&mutex, NULL);

    /* Check if mutex intialization was OK. */
    if (mutex_ans != 0)
        error_thread_mutex(mutex_ans);

    /* This is to know if the operations can be distributing to all threads in multiples. */
    v->diff = v->size % v->threads;
    /* If can't be (parity), the size of vectors change to be assigned in multiples. */
    v->size = v->size - v->diff;

    /* The different to be assigned in multiples is stored in this var. */
    int diff = v->diff;

    /* It's the portion that correspond to each thread. */
    int size_per_thread = v->size / v->threads;

    /** The assignment of the operations range to each one threads starts since at the end. 
     * This is to solve the parity. */
    for (int i = v->threads - 1; i >= 0; i--) {
        int th;

        th_args[i].v = v;
        th_args[i].id = i;

        /** EXPLAIN 1: T starts. 
         * 100 assigned to 4 threads (T). 
         *       T4.start: i=3 -> 300 / 4 = 75
         *       T3.start: 50
         *       T2.start: 25
         *       T1.start: 0 
        */ 
        th_args[i].start = size_per_thread * i;
        
        /** EXPLAIN 2: T ends.
         * 100 assigned to 4 threads (T).
         *      T4.end: (100 / 4) + start (75) - 1= 99
         *      T3.end: 74
         *      T2.end: 49
         *      T1.end: 24
        */
        th_args[i].end = size_per_thread + th_args[i].start - 1;
        th_args[i].mutex = &mutex;
        th_args[i].handler = &th_handler[i];

        /* This help to solve the parity adding 1 position starting by end to start. */
        /** EXPLAIN 3: Parity.
         * v: 10; T: 4
         * 
         * Integer divisions applies floor function, ever.
         * This is equal to 2 positions for each thread. 2 positions will not be operating.
         * 
         * So, the diff is equals to 2 (10 % 4).
         * The new size is 8 (v - diff).
         * 
         * While the diff is greater than 0, then 1 position will be added to T4 and T3.
         * 
         * T4: 3
         * T3: 3
         * T2: 2
         * T1: 2
        */
        if (diff > 0) {
            th_args[i].end += diff;
            diff--;
            th_args[i].start += diff;
        }

        /* Thread creation. */
        th = pthread_create(th_args[i].handler, 
                        NULL, 
                        (void *) p_operation_init, 
                        (void *) &th_args[i]);

        /* Validate the pthread creation. */
        if (th != 0) 
            error_thread_create(th_args[i].id, th);


        //printf("[%d] Start: %d - End: %d\n", i, th_args[i].start, th_args[i].end);
    }


    for (int i = v->threads - 1; i >= 0; i--) {
        /* Threads join. */
        int th = pthread_join(*(th_args[i].handler), &status);

        /* Validate the pthread join. */
        if (th != 0)
            error_thread_join((intptr_t)status, th_args[i].id, th);


        //printf("Thread [%d] - Status %ld\n", th_args[i].id, (intptr_t)status);
    }
    *elapsed_time = omp_get_wtime() - *(elapsed_time);    // Time end.

    /* Destroy the mutex. */
    pthread_mutex_destroy(&mutex);
}

/**
 * Purpose: Liberate the memory separated dynamically.
 * 
 * @params VINFO the only things that are allocate dynamically in memory 
 *          are vector a and b.
 * 
 * @return void.
*/
void freeVINFO(VINFO *v) {
    free(v->a);
    free(v->b);

    v->a = NULL;
    v->b = NULL;
}