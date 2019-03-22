#ifndef __M_FILE__
#define __M_FILE__

#include <stdlib.h>

FILE *openFile(char *filename, char *parameter);
void closeFile(FILE **file);

void getFileData(FILE **filename, double **vector, int size);
int getFileLines(FILE **filename);

#endif 