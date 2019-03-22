#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "mfile.h"

/* Total of digits of the number, including sign */
#define DIGITS  8

/* Defined by errno library. There is stored errno code by FILE. */
extern int errno;   // Defined by errno library


/** This method open the file, doin' validation.
 * 
 *  @params the name of the file to open.
 *  @params read, write, read and write, trunc, etc.. man fopen
 * 
 *  @return Pointer to the file opened.
**/
FILE *openFile(char *filename, char *parameter) {
    FILE *mfile = fopen(filename, parameter);

    if (mfile == NULL) {
        perror("File error");   // This show the error from errno library.

        exit(EXIT_FAILURE);     // Portable solution. Better than 1.
    } else {
        return mfile;
    }
}

/** Close an opened file.
 * 
 *  @params pointer to the file.
**/
void closeFile(FILE **file) {
    fclose(*file);
    *file = NULL;
}

/** Read the file and export the numbers to a vector.
 * 
 *  @params pointer to the file.
 *  @params pointer to the vector to save numbers.
 *  @params size of vector, is used to reserve memory.
 * 
*/
void getFileData(FILE **filename, double **vector, int size) {
    char number[DIGITS];
    int counter = 0;

    double *mvector = calloc(sizeof(double*), size);  // Memory separation to vector.

    rewind(*filename);  // Restart file stream, positioning to the begin.

    while(fgets(number, sizeof(number), *filename) != NULL){    // Fgets read line by line.
        mvector[counter] = atoi(number);    // Convert the char* to int.

        counter++;
    }

    *vector = mvector;  // Set the vector's pointer pointing to mvector.
}

/** Used to know the number of lines in file.
 * 
 *  @params Pointer to the file whose number of lines wants be known.
 *  @return Total lines in file.
*/
int getFileLines(FILE **filename) {
    char ch;
    int total = 0;  // At the end of the file MUST have a \n.

    rewind(*filename);  // Restart file stream, positioning to the begin.

    while(!feof(*filename)) {  // End signal.
        if ((ch = fgetc(*filename)) == '\n')    // Read line by line counting.
            total++;
    }

    return total;
}