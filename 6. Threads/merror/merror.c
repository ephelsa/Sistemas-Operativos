#include "merror.h"


/**
 * Purpose: Show an incorrect usage of the program or something like that.
 *          Terminate the program execution.
 * 
 * @param char* is used to show in screen the name of the file (argv[0]).
 * 
 * @return void.
 */
void error_usage(char *filename) {
    printf("Error: Usage isn't correct.\n\n");
    printf("Try again.\n");
    printf("\t%s <execution_option> <file_a> <file_b> <optional: #threads> \n", filename);
    printf("\texecution_option: Type of execution.\n");
    printf("\ts: Sequential.\n");
    printf("\tp: Parallel\n");

    exit(EXIT_FAILURE);
}

/**
 * Purpose: Show in screen the different size between vectors.
 *          Terminate the program execution.
 * 
 * @param int is the size of vector a.
 * @param int is the size of vector b.
 * 
 * @return void
*/
void error_vector_diff(int a, int b) {
    printf("Error: Vectors have different sizes (%d and %d).\n\n", a, b);
    printf("Try again.\n");
    printf("\tVectors must have the same size.\n");

    exit(EXIT_FAILURE);
}

/**
 * Purpose: Show in screen an error code and the "id" thread when a problem occurs in
 *          the thread creation.
 *          Terminate the program execution.
 * 
 * @param int is the thread "id".
 * @param int is the error returned by pthread_create
 * 
 * @return void.
*/
void error_thread_create(int id, int error) {
    printf("Error: Thread[%d] creation failed.\n", id);
    printf("Try again.\n");
    printf("\tVerify ERRORS in man pthread_create. Error number: %d\n", error);

    exit(EXIT_FAILURE);
}

/**
 * Purpose: Show in screen an error code, thread "id", and status when a problem occurs 
 *          with the thread is trying to joining.
 *          Terminate the program execution.
 * 
 * @params int is the status code sent by pthread_exit to join.
 * @params int is the thread "id".
 * @params int is the error code returned by pthread_join.
 * 
 * @return void.
*/
void error_thread_join(int status, int id, int error) {
    printf("Error: Thread[%d] joining (status: %d) failed.\n", id, status);
    printf("Try again.\n");
    printf("\tVerify ERRORS in man pthread_join. Error number: %d\n", error);

    exit(EXIT_FAILURE);
}

/**
 * Purpose: Show in screen an error code initializing the mutex.
 *          Terminate the program execution.
 * 
 * @param int is the error code returned by pthread_mutex_init.
 * 
 * @return void.
*/
void error_thread_mutex(int error) {
    printf("Error: Mutex initializer failed.\n");
    printf("Try again.\n");
    printf("\tVerify ERRORS in man pthread_mutex_init. Error number: %d\n", error);

    exit(EXIT_FAILURE);
}