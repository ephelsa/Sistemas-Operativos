#ifndef FILEIO_H_
#define FILEIO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pid.h"


/** This method open a file in /proc/[pid]/status.
 * @char* [pid] is to complete the route.
 * 
 * @return A file opened to be read.
*/
FILE *open_proc_folder(char*);

/** This method create a file with the PIDs information.
 * @int Number of pids.
 * @PID_INFO* The information of PIDs.
 * 
 * @return void.
*/
void create_file(int, PID_INFO *);


#endif