#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "fliki.h"
#include "funcs.h"
#include "global.h"
#include "buffer.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

int main(int argc, char** argv) {
  if (validargs(argc, argv) == -1) {
    // printf("exit failure");
    USAGE(*argv, EXIT_FAILURE);
  }
  if (global_options == HELP_OPTION) {
    USAGE(*argv, EXIT_SUCCESS);
  }
  debug("diff_filename: %s", diff_filename);
  FILE* file = open_file(diff_filename);
  if (file == NULL) return EXIT_FAILURE;
  HUNK hunk;
  
  int if_fail = patch(stdin, stdout, file);
  fclose(file);

  if (if_fail == -1) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
