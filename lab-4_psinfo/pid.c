#include "headers/pid.h"
#include "headers/fileio.h"
#include <string.h>

int total_char(char *, char, char);
unsigned short chars_contained_in_title(char *, char *);
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

unsigned short chars_contained_in_title(char *line, char *chs) {
    unsigned short contained = 0;

    for (int i = 0; chs[i] != '\0'; i++) {
        if (line[i] != chs[i])
            return contained;
    }
    contained = 1;

    return contained;
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

        char *line = calloc(total_line, sizeof(line));

        for (int j = 0; fgets(line, total_line, proc) != NULL; j++) {

            int title_size = total_char(line, line[0], 10);
            int info_size = total_char(line, 9, 10);

            char *title = malloc(title_size * sizeof(char));


            if (chars_contained_in_title(line, "Name:\0") == 1) {
                pids[i].name = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].name);
            } else if (chars_contained_in_title(line, "State:\0") == 1) {
                pids[i].state = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].state);
            } else if (chars_contained_in_title(line, "VmSize:\0") == 1) {
                pids[i].vmSize = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].vmSize);
            } else if (chars_contained_in_title(line, "VmExe:\0") == 1) {
                pids[i].vmExe = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].vmExe);
            } else if (chars_contained_in_title(line, "VmData:\0") == 1) {
                pids[i].vmData = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].vmData);
            } else if (chars_contained_in_title(line, "VmStk:\0") == 1) {
                pids[i].vmStk = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].vmStk);
            } else if (chars_contained_in_title(line, "voluntary_ctxt_switches:\0") == 1) {
                pids[i].voluntary_ctxt_switches = separate_memory(info_size);
                sscanf(line, "%s %s", title, pids[i].voluntary_ctxt_switches);
            } else if (chars_contained_in_title(line, "nonvoluntary_ctxt_switches:\0") == 1) {
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