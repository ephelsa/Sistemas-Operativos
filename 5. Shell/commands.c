#define PATH_SIZE 300

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <string.h>

#include "commands.h"
#include "parser.h"

void udea_pwd() {
    /* To separate memory dynamically */
    char *path = malloc(PATH_SIZE * sizeof(char));   
 
    if (getcwd(path, PATH_SIZE) != NULL)
        printf("Current path: \n\t%s\n\n", path);
    else 
        printf("Error with udea-pwd\n");

    /* Memory is free after show info */
    free(path);
}

void udea_cd(char *whereToGo) {
    /* Changing and verifing */    
    if (chdir(whereToGo) == 0)
        udea_pwd();
    else
        printf("Error with udea-cd\n");
}

void udea_echo(int size, char **message) {
    /* doesn't need to be explained... */
    for(int i = 1; i < size; i++)
        printf("%s ", message[i]);

    printf("\n\n");
}

void udea_clr() {
    system("clear");
}

void udea_time() {
    /* Time type*/
    time_t now;
    /* Returns the current time of the system as time_t */
    time(&now);
    /* ctime convert to local time format */
    printf("Current time: %s\n", ctime(&now));
}

void udea_exit() {
    exit(0);
}