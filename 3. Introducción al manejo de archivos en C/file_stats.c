#include "file_stats.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Method definition
*/
FILE * get_file(char *filename) {
  FILE *file = fopen(filename, "r");

  /* To check the file opened */
  if (file == NULL) {
    printf("%s is an invalid file...\n", filename);

    exit(1);
  }

  return file;
}

void stats_file(STATS *st) {
  FILE *output_file;
  
  char full_filename[80]; 
  char *stats_name = "_stats";
  char *filename = st->filename;
  char ch = 1;
  int counter = 0;

  /* Change the name */
  for (int i = 0; ch != '\0'; i++) {
    ch = filename[i];

    if (ch == '.') {
      char ch1 = 1;

      for (int j = 0; ch1 != '\0'; j++) {
        ch1 = stats_name[j];
        full_filename[i + j] = ch1;
        counter = j;
      }
    }
    full_filename[i + counter] = ch;
  }

  printf("Obteniendo estadisticas...\n - %s ---> generando reporte %s\n", filename, full_filename);

  /* Write in the new file */
  output_file = fopen(full_filename, "wa");

  /* Statistics in the file */
  fprintf(output_file, "chars: %d\n", st->chars);
  fprintf(output_file, "words: %d\n", st->words);
  fprintf(output_file, "lines: %d\n", st->lines);
  fprintf(output_file, "whitespaces: %d\n", st->whitespaces);
  fprintf(output_file, "uppercase: %d\n", st->uppercases);
  fprintf(output_file, "lowercase: %d\n", st->lowercases);
  fprintf(output_file, "digits: %d\n", st->numbers);

  /* Close the file */
  fclose(output_file);

  printf("Estadisticas culminadas");
}

/* Get the total of chars */
void total_chars(STATS *st) {
  FILE *filename = get_file(st->filename);
  int total = 0;
  char ch;

  while((ch = getc(filename)) != EOF)
    total++;

  st->chars = total;

  fclose(filename);
}

/* Get the total of lines */
void total_lines(STATS *st) {
  FILE *filename = get_file(st->filename);
  int total = 1;
  char ch;

  while((ch = getc(filename)) != EOF) {

    if (ch == '\n')
      total++;
  }

  st->lines = total;

  fclose(filename);
}

/* Get the total of words */
void total_words(STATS *st) {
  FILE *filename = get_file(st->filename);
  int total = 0, letter = 0;
  char ch;

  /* Words between spaces */
  while((ch = getc(filename)) != EOF) {
    if (ch == '\n' || ch == ' ' || ch == '\t') {
      if (letter > 0)
        total++;
      letter = 0;
    } else { letter++; }
  }

  /* To read the last word if the file didn't end with any whitespace */
  if (letter > 0) 
    total++;

  st->words = total;

  fclose(filename);
}

/* Get the total of whitespaces: tabs, spaces and line jump's */
void total_whitespaces(STATS *st) {
  FILE *filename = get_file(st->filename);
  int total = 0;
  char ch;

  while((ch = getc(filename)) != EOF) {
    if (ch == '\n' || ch == ' ' || ch == '\t')
      total++;
  }

  st->whitespaces = total;

  fclose(filename);
}

/* Get the total of uppercase words: ASCII */
void total_uppercases(STATS *st) {
  FILE *filename = get_file(st->filename);
  int total = 0;
  char ch;

  while((ch = getc(filename)) != EOF) {
    if (ch >= 65 && ch <= 90)
      total++;
  }

  st->uppercases = total;

  fclose(filename);
}

/* Get the total of lowercase words: ASCII */
void total_lowercases(STATS *st) {
  FILE *filename = get_file(st->filename);
  int total = 0;
  char ch;

  while((ch = getc(filename)) != EOF) {
    if (ch >= 97 && ch <= 122)
      total++;
  }

  st->lowercases = total;

  fclose(filename);
}

/* Get the total of numbers: ASCII */
void total_numbers(STATS *st) {
  FILE *filename = get_file(st->filename);
  int total = 0;
  char ch;

  while((ch = getc(filename)) != EOF) {
    if (ch >= 48 && ch <= 57)
      total++;
  }

  st->numbers = total;

  fclose(filename);
}