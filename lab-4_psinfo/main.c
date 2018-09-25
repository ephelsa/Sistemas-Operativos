#include <stdio.h>

#include "headers/pid.h"
#include "headers/fileio.h"

/* Analize the arguments.- */
void cli(int, char *[], PID_INFO *);

/* This var is to know the total of PID admitted. */
int number_pid = 0;

/* Main code */
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s -<options> [pid's]\n", argv[0]);
        printf("<options>\n r: Create a report.\n l: List PID.\n");
        exit(1);
    } else {
        PID_INFO pids[2];
        pids[0].p_id = "2";
        cli(argc, argv, pids);

        printf("PID: %s\n", pids[0].p_id);
    }



    return 0;
}


void cli(int argc, char *args[], PID_INFO *pids) {
    /* Read the arguments */
    /* These vars are to validate if special command has found */
    int command_pos = -1;
    unsigned short command = 00;    // Values 00 before read the dash pos, 01 reading commands, 11 dash detected or not.
    unsigned short report = 0;  // Values 0 and 1.
    unsigned short list = 0;    // Values 0 and 1.

    /* To know the number of PIDs */
    number_pid = argc - 1;

    /* To know when the pids size has been allocated in memory. Values between 0 and 1. */
    unsigned short pid_allocated = 0;

    for (int i = 1; i < argc; i++) {

        /* First if: To no iterate char by char if the command has been read. */
        /* The else contains the PIDs */
        if (command != 11) {
            /* To read char by char */
            char ch;

            /* If only has been written "./filename -" have to show an error message. */
            int total_j = 0;

            /* This is to know when has been detected a space. While is reading. */
            if (command == 01) 
                command_pos = i;

            for (int j = 0; (ch = args[i][j]) != '\0'; j++) {

                total_j = j;

                /* If at the next iteration hasn't been read the dash is because the args don't have 
                 * options.
                 * */
                if (j == 1 && command == 00) {
                    command = 11;
                    i = 0;

                    break;
                }

                /* If command reading has beem started */
                if (command == 01) {
                    /* If an error is found, this var will be 1 */
                    unsigned short error = 0;                

                    /* If the ch is equal to a cli's option the var associated to the option will be true. */
                    /* The *1 else if is when a diferent char is detected, validate errors in the option and if
                    * is the end of the options.
                    * 
                    * The last else if is when detect a void dash.*/
                    if (ch == 108 && command_pos == -1) {
                        list = 1;
                    } else if (ch == 114 && command_pos == -1) {
                        report = 1;
                    } else if (report == 1 || list == 1) {  // *1
                        if (command_pos != -1) {
                            command = 11;
                            number_pid--;
                            break;
                        } else {
                            error = 1;
                        }
                    } else if (command_pos != -1) {
                        error = 1;
                    } else {
                        error = 1;
                    }

                    /* When a error has been detected above this if show the problem and stop the execution. */
                    if (error == 1) {
                        printf("Usage error: You must specificate the <options>.\n r: Create a report.\n l: List PID.\n");
                        exit(1);
                    }

                    //printf("char: %c\n", ch);
                    //printf("report: %d\n", report);
                    //printf("list: %d\n", list);
                    //printf("command: %d\n", command);
                }

                /* When the dash is detected the state ofcommand change to "reading". But if 
                * the state of command is "has been read" show a message to the user.*/
                if (ch == 45 && command == 00) {
                    command = 01;
                } else if (ch == 45 && command == 11) {
                    printf("The commands has been read before. \nContinuing the execution.");
                } 
            }

            /* If has been detected "./filename -" an error is shown. */
            if (total_j = 1 && argc == 2) {
                printf("Usage: %s -<options> [pid's]\n", args[0]);
                printf("<options>\n r: Create a report.\n l: List PID.\n");
                exit(1);
            }
        } else {
            // Document this
            unsigned short a = validate_pid(args[i]);

            if (pid_allocated == 0) {
                pids = calloc(number_pid, sizeof(PID_INFO));

                if (pids == NULL) {
                    printf("Error: Allocating PIDS in memory didn't work.\n");
                    exit(1);
                } else {
                    pid_allocated = 1;
                }
            } 
            
            if (pid_allocated == 1 && a == 1) {
                if ((argc - number_pid) == 1) {
                    pids[number_pid - i].p_id = args[i];

                    printf("W op %s\n", pids[number_pid - i].p_id);
                } else {
                    pids[number_pid - (i - 1)].p_id = args[i];     
                    printf("Op %s\n", pids[number_pid - (i - 1)].p_id);
                }
            }
        }
    }

    printf("PID'S numbers: %d\n", number_pid);
}
