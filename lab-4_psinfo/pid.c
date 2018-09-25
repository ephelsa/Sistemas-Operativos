#include "headers/pid.h"
#include "headers/fileio.h"


/** This method fille the PIDS struct with the complete information. */
void fill_pids_information(int size, PID_INFO *pids) {

    for (int i = 0; i < size; i++) {
        printf("PID.c: %s\n", pids[i].p_id);


        FILE *proc = open_proc_folder(pids[i].p_id);
        
        char line[120];

        for (int j = 0; fgets(line, sizeof(line), proc) != NULL; j++) {
            printf("Line [%02d][%02d]: %s", i, j, line);
        }

    }
}

/* This method validate if is a number. */
unsigned short validate_pid(char *pid) {
    for (int i = 0; pid[i] != '\0'; i++) {
        if (pid[i] < 48 || pid[i] > 57) {
            printf("Error: %s is an invalid PID.\n", pid);
            exit(1);
        }
    }

    return 1;
}