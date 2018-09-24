#ifndef FILEIO_H_
#define FILEIO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pid.h"

/**
 * Methods
 * 
 * Read file
 * Write a file
*/

FILE *open_proc_folder(char*);
void create_file(int, PID_INFO []);


#endif