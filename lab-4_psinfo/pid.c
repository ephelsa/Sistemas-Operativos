#include "headers/pid.h"
#include "headers/fileio.h"
#include <string.h>

int total_char(char *, char, char);
char *separate_memory(int);


int total_char(char *line, char start, char end) {
    int count = 0, total = 1;
    unsigned short counting = 0;

    for (char ch = line[count]; ch != end && ch != '\0'; ch = line[count]) {

        if (counting == 0 && ch == start)
            counting = 1;
        
        if (counting == 1)
            total++;

        if (ch == 32)
            line[count] = 127;

        count++;
    }

    return total;
}

char *separate_memory(int size) {
    char *info = malloc(size * sizeof(char));

    if (info == NULL) {
        printf("Error: Memory Allocation.\n");

        exit(1);
    }

    return info;
}

/** This method fill the PIDS struct with the complete information. */
void fill_pids_information(int size, PID_INFO *pids) {

    const int total_line = 120;

    for (int i = 0; i < size; i++) {
        FILE *proc = open_proc_folder(pids[i].p_id);   
        int tlif = total_lines_in_file(proc, total_line);

        proc = open_proc_folder(pids[i].p_id);   
        char *line = calloc(total_line, sizeof(line));

        for (int j = 0; fgets(line, total_line, proc) != NULL; j++) {

            int title_size = total_char(line, line[0], 10);
            int info_size = total_char(line, 9, 10);

            char *title = malloc(title_size * sizeof(char));

            if (j == 0) {
                //pids[i].name = malloc(info_size * sizeof(char));
                pids[i].name = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].name);
            } else if (j == 2) {
                //pids[i].state = malloc(info_size * sizeof(char));
                pids[i].state = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].state);
            } else if (j == 17) {
                //pids[i].vmSize = malloc(info_size * sizeof(char));
                pids[i].vmSize = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].vmSize);
            } else if (j == 27) {
                //pids[i].vmExe = malloc(info_size * sizeof(char));
                pids[i].vmExe = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].vmExe);
            } else if (j == 25) {
                //pids[i].vmData = malloc(info_size * sizeof(char));
                pids[i].vmData = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].vmData);
            } else if (j == 26) {
                //pids[i].vmStk = malloc(info_size * sizeof(char));
                pids[i].vmStk = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].vmStk);
            } else if (j == (tlif - 2)) {
                //pids[i].voluntary_ctxt_switches = malloc(info_size * sizeof(char));
                pids[i].voluntary_ctxt_switches = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].voluntary_ctxt_switches);
            } else if (j == (tlif - 1)) {
                //pids[i].novoluntary_ctxt_switches = malloc(info_size * sizeof(char));
                pids[i].novoluntary_ctxt_switches = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].novoluntary_ctxt_switches);
            }

            free(title);
        }

        fclose(proc);
    }
}

/* This method is to liberate the space in PIDs */
void liberate_pids_memory(PID_INFO *pids, int number_pids) {
    
    for (int i = 0; i < number_pids; i++) {
        free(pids[i].name);
        free(pids[i].state);
        free(pids[i].vmSize);
        free(pids[i].vmExe);
        free(pids[i].vmData);
        free(pids[i].vmStk);
        free(pids[i].voluntary_ctxt_switches);
        free(pids[i].novoluntary_ctxt_switches);
    }

    free(pids);
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