#include <stdio.h>

#include "headers/pid.h"
#include "headers/fileio.h"

/* Analize the arguments. */
void cli(int, char *[]);

/* This method extract the PIDs from the arguments */
void set_pids(int, char *[], PID_INFO *);

/* This var is to know the total of PID admitted. */
int number_pid = 0;
unsigned short report = 0;  // Values 0 and 1.
unsigned short list = 0;    // Values 0 and 1.

/* Main code */
int main(int argc, char *argv[]) {
    /* Minimun arguments */
    if (argc < 2) {
        printf("Usage: %s -<options> [pid's]\n", argv[0]);
        printf("<options>\n r: Create a report.\n l: List PID.\n");
        exit(1);
    } else 
        cli(argc, argv);

    /* After known the number of pids, is time to allocate in memory the PIDS */
    PID_INFO *pids_info = malloc(number_pid * sizeof(PID_INFO));
    
    set_pids(argc, argv, pids_info);

    fill_pids_information(number_pid, pids_info);
    
    /* If we have -l command is shown this */
    if (list == 1 && report == 0)
        printf("\n\n--- Informacion recolectada ---");

    /* If we have -r isn't show the information to the user in terminal */
    if (report == 0) {
        for (int i = 0; i < number_pid; i++) {
            printf("\nPID: %s\n", pids_info[i].p_id);
            printf("Nombre del proceso: %s\n", pids_info[i].name);
            printf("Estado: %s\n", pids_info[i].state);
            printf("Tamaño total en memoria: %s\n", pids_info[i].vmSize);
            printf("\tTamaño de la memoria en la región TEXT: %s\n", pids_info[i].vmExe);
            printf("\tTamaño de la memoria en la región DATA: %s\n", pids_info[i].vmData);
            printf("\tTamaño de la memoria en la región STACK: %s\n", pids_info[i].vmStk);
            printf("\tNúmero de cambios de contexto realizados (voluntarios - no voluntarios): %s - %s\n", pids_info[i].voluntary_ctxt_switches, pids_info[i].novoluntary_ctxt_switches);
        }
    }

    /* If we have -r command, an output file is created */
    if (report == 1)
        create_file(number_pid, pids_info);

    /* After use the information, deallocates PID information from memory */
    liberate_pids_memory(pids_info, number_pid);



    return 0;
}


void cli(int argc, char *args[]) {
    /* Read the arguments */
    /* These vars are to validate if special command has found */
    int command_pos = -1;
    unsigned short command = 00;    // Values 00 before read the dash pos, 01 reading commands, 11 dash detected or not.

    /* To know the number of PIDs */
    number_pid = argc - 1;

    for (int i = 1; i < argc; i++) {
        /* First if: To no iterate char by char if the command has been read. */
        /* The else is to end */
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

        } else {
            /* To stop the commands' reading */
            break;
        }
    }
}

void set_pids(int argc, char *argv[], PID_INFO *pids) {
    int diff = argc - number_pid;
    unsigned short have_commands = 1;
    
    /* This is to know when we have the list command */
    int condition = argc;

    /** If the difference between argc (total of arguments) - number_pid is equals to 1, it's say that 
     * we don't have <options>.
    */
    if (diff == 1) {
        have_commands = 0;

        if (number_pid > 1) {
            /* This is to take only the first PID if the user didn't write -l command */
            condition = argc - number_pid;
            number_pid = 1;
        }
    } else {
        /* This is to take only the first PID if the user didn't write -l command */
        if (list == 0 && report == 1) {
            condition = argc - (number_pid - 1);
            number_pid = 1;
        } else if (list == 0 && report == 0) {
            condition = argc - number_pid;
            number_pid = 1;
        }
    }

    /* The for's inside the statement append the PIDs inverse. */
    /* Example: ./a 123 456 789 <- input */
    /*          789 456 123 <- saved inverse */
    if (have_commands == 1) {
        for (int i = 2; i < condition; i++) {
            if (validate_pid(argv[i]) == 1)
                pids[number_pid - (i - 1)].p_id = argv[i];
        }
    } else {
        /* This is to take only the first PID if the user didn't write -l command */
        /* The else is to this example: ./a 1900 */
        if (number_pid > 1) {
            for (int i = 1; i < condition; i++) {
                if (validate_pid(argv[i]) == 1)
                    pids[number_pid - i].p_id = argv[i];
            }
        } else {
            if (validate_pid(argv[1]) == 1)
                pids[number_pid - 1].p_id = argv[1];
        }
    }
}