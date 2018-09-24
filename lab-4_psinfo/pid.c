#include "headers/pid.h"

PID_INFO* read_all_pid(int size, char *pid[]) {
    PID_INFO* pid_array;
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