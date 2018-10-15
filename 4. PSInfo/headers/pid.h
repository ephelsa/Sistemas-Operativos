#ifndef PID_H_
#define PID_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * Struct PID_INFO contains:
 * pid  Process ID.
 * name Process name.
 * state    Process state.
 * VmSize   Size in memory.
 * VmExe    Zone Text.
 * VmData   Zone data.
 * VmStk    Zone Stack.
 * voluntary_ctxt_switches  Voluntary context switches.
 * novoluntary_ctxt_switches    Non voluntary context switches.
*/

typedef struct pid_info {
    char *p_id; 
    char *name; 
    char *state;    
    char *vmSize;   
    char *vmExe;    
    char *vmData;   
    char *vmStk;    
    char *voluntary_ctxt_switches;    
    char *novoluntary_ctxt_switches;  
} PID_INFO;


/** This method fill the PIDs information. Allocates memory dynamically.
 * @int Number of PIDs.
 * @PID_INFO* PIDS to fill.
 * 
 * @return void.
*/
void fill_pids_information(int, PID_INFO *);

/** After use the PIDS information, is necessary deallocate the memory space.
 * @PID_INFO* PIDS to deallocates.
 * @int Number of PIDs.
 * 
 * @return void.
*/
void liberate_pids_memory(PID_INFO *, int);


/** This method validate if a PID is a valid number.
 * @char* A process id.
 * 
 * @return If is valid returns 1 else 0.
*/
unsigned short validate_pid(char*);

#endif