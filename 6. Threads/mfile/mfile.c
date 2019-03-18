#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "mfile.h"

/* Total of digits of the number, including sign */
#define DIGITS 5



extern int errno;   // Defined by errno library

/***************************************/
/*********  PRIVATE METHODS ************/
/***************************************/





/***************************************/
/**********  PUBLIC METHODS ************/
/***************************************/

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
void getFileData(FILE **filename, int **vector, int size) {
    char number[DIGITS];
    int counter = 0;

    int *mvector = malloc(sizeof(int) * size);  // Memory separation to vector.

    rewind(*filename);  // Restart file stream, positioning to the begin.

    while(fgets(number, sizeof(number), *filename) != NULL){    // Fgets read line by line.
        printf("%s\n", number);

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
    int total = 1;  // Cut 1 iteration by EOF, that's reason to starts at 1.

    rewind(*filename);  // Restart file stream, positioning to the begin.

    while((ch = getw(*filename)) != EOF) {  // Reads only ONE letter line by line.
        total++;
    }

    printf("Total lines: %d\n", total);

    return total;
}