#include "headers/fileio.h"

/******************************/
/* Private method declaration */
/******************************/

char *create_full_name(int, char *[]);
void write_file(char *, PID_INFO *, int);


/*****************************/
/* Private method definition */
/*****************************/

char *create_full_name(int argc, char *argv[]) {
    size_t names_len[argc];
    size_t full_name_len = 0;

    char *full_name;
    
    /* Calculate the lenght of each argv and adding the value to the full_name_len */
    for (int i = 0; i < argc; i++) {
        names_len[i] = strlen(argv[i]);
        full_name_len = full_name_len + names_len[i];
    }

    /* Separate memory space */
    full_name = malloc(full_name_len);

    /* full name positions */
    int counter = 0;

    /* Write the full name */
    for (int i = 0; i < argc; i++) {
        for (int j = 0; j < names_len[i]; j++) {
            full_name[counter] = argv[i][j];
            
            counter++;
        }
    } 

    return full_name;
}

void write_file(char *fileName, PID_INFO *pids, int number_pid) {

    /* The file creation */
    FILE *outFile = fopen(fileName, "wa");

    /* Validate if the file is valid */
    if (outFile == NULL) {
        printf("Error to open %s, invalid file...\n", fileName);

        exit(1);
    }

    for (int i = 0; i < number_pid; i++) {
        fprintf(outFile, "\nPID: %s\n", pids[i].p_id);
        fprintf(outFile, "Nombre del proceso: %s\n", pids[i].name);
        fprintf(outFile, "Estado: %s\n", pids[i].state);
        fprintf(outFile, "Tamaño total en memoria: %s\n", pids[i].vmSize);
        fprintf(outFile, "\tTamaño de la memoria en la región TEXT: %s\n", pids[i].vmExe);
        fprintf(outFile, "\tTamaño de la memoria en la región DATA: %s\n", pids[i].vmData);
        fprintf(outFile, "\tTamaño de la memoria en la región STACK: %s\n", pids[i].vmStk);
        fprintf(outFile, "\tNúmero de cambios de contexto realizados (voluntarios - no voluntarios): %s - %s\n", pids[i].voluntary_ctxt_switches, pids[i].novoluntary_ctxt_switches);
    }

    /* To close the file */
    fclose(outFile);

    printf("Archivo de salida generado: %s\n", fileName);
}

/****************************/
/* Public method definition */
/****************************/

FILE *open_proc_folder(char *p_id) {
    /* The array contains the full path separated */
    char *path[3] = {"/proc/", p_id, "/status"};
    char *full_path = create_full_name(3, path);

    /* Open the file to read */
    FILE *inFile;
    inFile = fopen(full_path, "r");

    /* Validate if the file is valid */
    if (inFile == NULL) {
        printf("Error to open %s, invalid file...\n", full_path);

        exit(1);
    }

    return inFile;
}

void create_file(int pid_array_size, PID_INFO *pids) {
    /* 1 (psinfo-report-) + pid_array_size (1029, 1204) + pid_array_size - 1 (dashes) = pid_array_size * 2 */
    int full_name_len = (pid_array_size * 2) + 1;
    char **name = calloc(full_name_len, sizeof(char *));

    /* first name */
    name[0] = "psinfo-report-";

    /* to complement the full name */
    int pos = pid_array_size - 1;
    for (int i = 1; i < full_name_len; i++) {
        /* if is completed, the last char* space in the array contains the extension */
        if ((i + 1) == full_name_len) {
            name[i] = ".info";
            continue;
        }

        /* To add the dash */
        if ((i % 2) == 0) {
            name[i] = "-";
            pos--;
            continue;
        }

        /* To add the pid number */
        name[i] = pids[pos].p_id;
    }


    char *filename = create_full_name(full_name_len, name); 
    write_file(filename, pids, pid_array_size);

    /* To deallocate block of memory */
    free(name);
    free(filename);
}