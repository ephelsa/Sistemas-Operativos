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
    char *p_id; // args
    char *name; // 0
    char *state;    // 2
    char *vmSize;   // 17
    char *vmExe;    // 27
    char *vmData;   // 25
    char *vmStk;    // 26
    char *voluntary_ctxt_switches;    // total - 1
    char *novoluntary_ctxt_switches;  // total
} PID_INFO;


/**
 * Methods
*/

void fill_pids_information(int, PID_INFO *);

unsigned short validate_pid(char*);

#endif