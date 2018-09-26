#include "headers/pid.h"
#include "headers/fileio.h"


/** This method fille the PIDS struct with the complete information. */
void fill_pids_information(int size, PID_INFO *pids) {

    char line[56][120];

    for (int i = 0; i < size; i++) {
        printf("PID.c: %s\n", pids[i].p_id);

        FILE *proc = open_proc_folder(pids[i].p_id);        

        for (int j = 0; fgets(line[j], 120, proc) != NULL; j++) {
            printf("Line [%02d][%02d]: %s\n", i, j, line[j]);

        }

        pids[i].name = line[0];
        pids[i].state = line[2];

        fclose(proc);
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