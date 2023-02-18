#include <stdlib.h>

#include "debug.h"
#include "fliki.h"
#include "global.h"
#include "funcs.h"

/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the
 * program, returning 0 if validation succeeds and -1 if validation fails.
 * Upon successful return, the various options that were specified will be
 * encoded in the global variable 'global_options', where it will be
 * accessible elsewhere in the program.  For details of the required
 * encoding, see the assignment handout.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 0 if validation succeeds and -1 if validation fails.
 * @modifies global variable "global_options" to contain an encoded
 * representation of the selected program options.
 * @modifies global variable "diff_filename" to point to the name of the file
 * containing the diffs to be used.
 */

// declare a function before you can define it lol
char *get_arr_char(char **arr, int i) { return *(arr + i); }
static int is_file(char *str1);

int validargs(int argc, char **argv) {
  // print every argument in argv
  // int j = 0;
  // while (j<argc) {
  //   printf("%d: %s\n", j, get_arr_char(argv, j));
  //   j++;
  // }

  // checks if there are no arguments. if there are none, return failure
  if (argc == 1) {
    // printf("no arguments: %d", argc);
    return -1;  // exit failure
  }

  // if (argc == 2) {
  //   if (is_file(get_arr_char(argv, argc - 1))) {  // last argument
  //     return 0;
  //   } else {
  //     return -1;
  //   }
  // }

  // checks if -h exists. if it does, return success
  if (strEqlz(get_arr_char(argv, 1), "-h")) {
    // printf("%s: this worked and says a lot about society\n",
    // get_arr_char(argv,1));
    global_options = global_options | HELP_OPTION;
    return 0;  // exit success
  }

  int i = 1;
  while (i < argc - 1) {
    // printf("\n %s ",get_arr_char(argv, i));
    if (strEqlz(get_arr_char(argv, i), "-n") == 1) {
      global_options = global_options | NO_PATCH_OPTION;
      // printf("-n: %ld", global_options);
    } else if (strEqlz(get_arr_char(argv, i), "-q") == 1) {
      global_options = global_options | QUIET_OPTION;
      // printf("-q: %ld",global_options);
    } else if (strEqlz(get_arr_char(argv, i), "-h") == 1) {
      if (i != 1) {
        // fprintf(stderr, "-h should be the first argument");
        // printf("help option is not first argument: %s", get_arr_char(argv, i));
        return -1;  // exit failure
      }
    } else {
      // printf("option that doesn't exist: %s; ", get_arr_char(argv, i));
      return -1;  // exit failure
      // option that doesn't exist
    }
    i++;
  }
  // printf("%ld", global_options);

  // if -h doesn't exist, check if the last argument is a file then open the file
  if (!is_file(get_arr_char(argv, argc - 1))) {  // last argument
    // printf("last argument is not a file: %s", get_arr_char(argv, argc-1));
    return -1;
  } else {
    // printf("last argument is a file: %s", get_arr_char(argv, argc-1));
    diff_filename = get_arr_char(argv, argc - 1);
  }

  // if no global options are set, return failure
  // if (global_options == 0) {
  //   // printf("no global options set: %ld\n", global_options);
  //   return -1;
  // }

  // abort();
  return 0;
}

int strEqlz(char *str1, char *str2) {
  if (strLen(str1) > strLen(str2)) {
    // printf("different lengths");
    return 0;
  }
  int i = 0;
  while (*(str1 + i) == *(str2 + i) && *(str1 + i) != '\0') {
    // printf("%d:%c\n", i,*(str1 + i));
    i++;
  }
  if (i != strLen(str1)) {
    return 0;
  }
  return 1;
}

int strLen(char *str1) {
  int i = 0;
  while (*(str1 + i) != '\0') {
    i++;
  }
  return i;
}

static int is_file(char *filename) {
  // a file is anything that doesn't start with a dash i guess
  return *(filename + 0) != '-';
  // FILE *file;
  // if ((file = fopen(filename, "r"))) {
  //   fclose(file);
  //   return 1;
  // }
  // return 0;
}