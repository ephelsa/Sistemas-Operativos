#ifndef __M_ERROR__
#define __M_ERROR__

#include <stdio.h>
#include <stdlib.h>

/******************************************************************/
/* Purpose: Show erros and terminate the program if is necessary. */
/******************************************************************/

void error_usage(char *filename);
void error_vector_diff(int a, int b);

void error_thread_create(int id, int error);
void error_thread_join(int status, int id, int error);
void error_thread_mutex(int error);

void warning_threads_greater_size(int n_thread, int size);


#endif