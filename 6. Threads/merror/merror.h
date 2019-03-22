#ifndef __M_ERROR__
#define __M_ERROR__

#include <stdio.h>
#include <stdlib.h>

void error_usage(char *filename);
void error_vector_diff(int a, int b);
void error_thread_create(int id);
void error_thread_join(int status, int id);

#endif