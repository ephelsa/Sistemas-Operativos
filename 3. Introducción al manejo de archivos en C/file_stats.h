#ifndef FILE_STATS_H_
#define FILE_STATS_H_

#include <stdio.h>
/**
 * This struct have all statistics from the doc.
*/
typedef struct stats{
  char *filename;
  int chars;
  int lines;
  int words;
  int whitespaces;
  int uppercases;
  int lowercases;
  int numbers;
} STATS;


/**
 * Method declaration
*/
/* This method is to open the file. Because we are gettin' an error with the next methods
 * for example, when we read the chars and next read the lines, we obtain zero in the last, so
 * the error is solved open and close the file.
 */
FILE * get_file(char *);

/**
 * This method is to generate the output
*/
void stats_file(STATS *);

/**
 * Calculate the statistics
*/
void total_chars(STATS *);
void total_lines(STATS *);
void total_words(STATS *);
void total_whitespaces(STATS *);
void total_uppercases(STATS *);
void total_lowercases(STATS *);
void total_numbers(STATS *);

#endif