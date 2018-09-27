#include "headers/pid.h"
#include "headers/fileio.h"
#include <string.h>

/******************************/
/* Private method declaration */
/******************************/

/** This method count the chars in a line.
 * @char* The line to be counted.
 * @char The char to start counting.
 * @char The char to end counting.
 * 
 * @return the total of chars.
  */
int total_char(char *, char, char);

/** To know if a line starts whit those chars.
 * @char* The line to search.
 * @char* The chars to compare.
 * 
 * @return If is contained returns 1 else 0.
*/
unsigned short chars_contained_in_title(char *, char *);

/** This method separates memory. 
 * @int The size to be reserved.
 * 
 * @return Allocates memory.
*/
char *separate_memory(int);


/*****************************/
/* Private method definition */
/*****************************/

int total_char(char *line, char start, char end) {
    int count = 0, total = 1;
    /* Counting condition */
    unsigned short counting = 0;

    /* The loop ends when ch is equals to end or '\0' (end of file) */
    for (char ch = line[count]; ch != end && ch != '\0'; ch = line[count]) {
        /* Change the start condition */
        if (counting == 0 && ch == start)
            counting = 1;
        
        /* If the counting condition is true, add 1 to the total */
        if (counting == 1)
            total++;

        /* Delete the spaces */
        if (ch == 32)
            line[count] = 127;

        count++;
    }

    return total;
}

unsigned short chars_contained_in_title(char *line, char *chs) {
    unsigned short contained = 0;

    /* End when position in chs is equals to '\0' */
    for (int i = 0; chs[i] != '\0'; i++) {
        /* When a char is diferent, returns invalid. */
        if (line[i] != chs[i])
            return contained;
    }
    /* Change the sate of contained */
    contained = 1;


    return contained;
}

char *separate_memory(int size) {
    /* Reserve memory */
    char *info = malloc(size * sizeof(char));

    /* Validate the reserved */
    if (info == NULL) {
        printf("Error: Memory Allocation.\n");

        exit(1);
    }


    return info;
}


/****************************/
/* Public method definition */
/****************************/

void fill_pids_information(int size, PID_INFO *pids) {
    /* Total of chars to store the line read. */
    const int total_line = 120;

    for (int i = 0; i < size; i++) {
        /* Open the /pro/[pid]/status */
        FILE *proc = open_proc_folder(pids[i].p_id);   

        /* Reserve memory dynamic to store the line */
        char *line = calloc(total_line, sizeof(line));

        /* fgets read the file line by line and stop when is NULL */
        for (int j = 0; fgets(line, total_line, proc) != NULL; j++) {
            /* Tile_size is to know the titles' size. For example: Name: */
            /* Info_size is to know the size of relevand information. For example: code */
            int title_size = total_char(line, line[0], 10);
            int info_size = total_char(line, 9, 10);

            /* Separate the title size dynamic */
            char *title = malloc(title_size * sizeof(char));

            /* Conditions to store information in pids struct */
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

            /* Deallocates the title's memory space */
            free(title);
        }

        /* Closes the file to open the next one */
        fclose(proc);
    }
}

void liberate_pids_memory(PID_INFO *pids, int number_pids) {
    /* The loop deallocates datas' pids memory */    
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

    /* Deallocates the pids memory space */
    free(pids);
}

unsigned short validate_pid(char *pid) {
    /* If a number that conforms the PID is not a valid number, an error is shown */
    for (int i = 0; pid[i] != '\0'; i++) {
        if (pid[i] < 48 || pid[i] > 57) {
            printf("Error: %s is an invalid PID.\n", pid);
            exit(1);
        }
    }

    return 1;
}