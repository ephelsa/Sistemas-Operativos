#ifndef PID_H_
#define PID_H_

#include <stdio.h>
#include <stdlib.h>
/**
 * Struct type PID_INFO will contains:
 * pid
 * name
 * state
 * VmTotal
 * VmExe
 * VmData
 * VmStk
 * voluntary_ctxt_switches
 * novoluntary_ctxt_switches
*/

typedef struct pid_info {
    char *p_id;
    char *name;
    char *state;
    char *vmSize;
    char *vmExe;
    char *vmData;
    char *vmStk;
    int voluntary_ctxt_switches;
    int novoluntary_ctxt_switches;
} PID_INFO;


/**
 * Methods
*/

PID_INFO* read_all_pid(int, char*[]);

unsigned short validate_pid(char*);

#endif