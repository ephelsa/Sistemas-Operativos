#define INPUT 300
#define BIN_SIZE 20

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include "parser.h"
#include "commands.h"

/* Method declaration */
void instruction(char *);

/* Main method */
int main(int argc, char **argv) {

    /* True loop */
    while (1) {
        /* An original name */
        printf("udea-prompt> ");

        /* Reading data dynamically */
        char *input = malloc(INPUT * sizeof(char));
        fgets(input, INPUT, stdin);

        /* This if avoid a Segmentation fault for newline value */
        if (input[0] != 10)          
            instruction(input);

        /* Free memory and clear the stdin buffer */
        free(input);
        fflush(stdin);
    }

    return 0;
}

/* Method definition */
void instruction(char *input) {
    char **items;
    int item_size = 0;
    int background = 0;

    item_size = separaItems(input, &items, &background);

    /* If background is enabled, create a child process */
    if (background == 1) {
        pid_t pid = fork();

        if (pid != 0) {
            printf("Proceso hijo: %d \n", pid);
        }
    }

    /* Internal */
    if (strcmp(items[0], "udea-pwd") == 0) 
        udea_pwd();
    else if (strcmp(items[0], "udea-cd") == 0)
        udea_cd(items[1]);
    else if (strcmp(items[0], "udea-echo") == 0)
        udea_echo(item_size, items);
    else if (strcmp(items[0], "udea-clr") == 0)
        udea_clr();
    else if (strcmp(items[0], "udea-time") == 0)
        udea_time();
    else if (strcmp(items[0], "udea-exit") == 0)
        udea_exit();

    /* External */
    else {
        int child = fork();

        if (child == 0) {
            /* External terminal commands */
            char path[20] = "/bin/";
            /* Args to pass via execv */
            char *args[item_size];

            /* Concatenation */
            strcat(path, items[0]);

            /* For an item_size, we'r separating memory denamically */
            /* Also, is filled with the args. */
            for (int i = 0; i <= item_size; i++) {
                args[i] = malloc((item_size + 1) * sizeof(char));
                args[i] = items[i];
            }
            /* Last argument is NULL */
            args[item_size + 1] = NULL;

            /* If response is equal to -1, an error has been ocurred. */
            int response = execv(path, args);

            /* Handling the error */
            if (response == -1) {
                printf("Comando invalido. \n\nIntente de nuevo o utilice los comandos internos.\n");
                /* Stop the waits */
                exit(0);
            } else {
                /* Free memory */
                for (int i = 0; i < item_size; i++)
                    free(args[i]);
            }
        } else {
            /* Waiting.. */
            wait(&child);
        }
    }
}