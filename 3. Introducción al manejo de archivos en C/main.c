#include <stdio.h>
#include "file_stats.h"

/* main */
int main(int argc, char *argv[]) {

  /* Validate the args */
  if (argc != 2) {
    printf("Usage: %s <file>\n", argv[0]);

    return 1;
  }

  /* Statistics */
  STATS ans;
  ans.filename = argv[1];

  /* Method's implementations */
  total_chars(&ans);
  total_lines(&ans);
  total_words(&ans);
  total_whitespaces(&ans);
  total_uppercases(&ans);
  total_lowercases(&ans);
  total_numbers(&ans);

  stats_file(&ans);

  return 0;
}