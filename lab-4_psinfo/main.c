#include <stdio.h>

#include "headers/pid.h"
#include "headers/fileio.h"


/* Analize the arguments */
void cli(int, char *[]);

/* Main code */
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s -<options> arguments", argv[0]);
        printf("<options>\n r: Create a report.\n l: List PID.");
        exit(1);
    } else 
        cli(argc, argv);


    PID_INFO a[3];
    a[0].p_id = "123";
    a[1].p_id = "444";
    a[2].p_id = "666";

    create_file(3, a);


    return 0;
}


void cli(int argc, char *args[]) {
    /* Read the arguments */
    /* These vars are to validate if special command has found */
    int command_pos = -1;
    unsigned short command = 00;
    unsigned short report = 0;
    unsigned short list = 0;

    for (int i = 1; i < argc; i++) {
        char ch;

        /* This is to know when has been detected a space. While is reading. */
        if (command == 01) 
            command_pos = i;

        for (int j = 0; (ch = args[i][j]) != '\0'; j++) {

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
                    } else {
                        error = 1;
                    }
                } else if (command_pos != -1) {
                    error = 1;
                } 

                /* When a error has been detected above this if show the problem and stop the execution. */
                if (error == 1) {
                    printf("Usage error: You must specificate the <options>.\n r: Create a report.\n l: List PID.\n");
                    exit(1);
                }

                //printf("command: %d\n", command);
                //printf("report: %d\n", report);
                //printf("list: %d\n", list);
            }

            /* When the dash is detected the state ofcommand change to "reading". But if the state of command
             * is "has been read" show a message to the user.*/
            if (ch == 45 && command == 00) {
                command = 01;
            } else if (ch == 45 && command == 11) {
                printf("The commands has been read before. \nContinuing the execution.");
            } 
        }
    }
}
