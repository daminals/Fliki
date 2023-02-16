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
  // printf("exit success, %ld", global_options);
  // TO BE IMPLEMENTED
  // do stdin part now
  debug("diff_filename: %s", diff_filename);
  FILE* file = open_file(diff_filename);
  if (file == NULL) return EXIT_FAILURE;
  HUNK hunk;
  
  // FILE* out = fopen("test.out", "w");
//   hunk_next(&hunk, file);
//   char a=hunk_getc(&hunk,file);
//   // while ((a=hunk_getc(&hunk, file))!=EOS) {
//   //   printf("%c",a);
//   // } printf("\n hunk next run %d", did_hunk_next_run);
//   // while ((a=hunk_getc(&hunk, file))!=EOS) {
//   //   printf("%c",a);
//   // } printf("\n hunk next run %d", did_hunk_next_run);
// hunk_show(&hunk, stdout);  
//   printf("%d,%d%c%d,%d\n", hunk.old_start,hunk.old_end,set_hunk_type_char(&hunk),hunk.new_start,hunk.new_end);
//   if (hunk_next(&hunk, file)==ERR) {printf("ERROR");hunk_show(&hunk, stdout);}
//   printf("%d,%d%c%d,%d\n", hunk.old_start,hunk.old_end,set_hunk_type_char(&hunk),hunk.new_start,hunk.new_end);
//   if (hunk_next(&hunk, file)==ERR) {printf("ERROR");hunk_show(&hunk, stdout);}
//   printf("%d,%d%c%d,%d\n", hunk.old_start,hunk.old_end,set_hunk_type_char(&hunk),hunk.new_start,hunk.new_end);



  // for (int i = 0; i < 200; i++) hunk_getc(&hunk, file);
  // hunk_show(&hunk, stdout);
  // for (int i = 0; i < 100; i++) hunk_getc(&hunk, file);
  int if_fail = patch(stdin, stdout, file);
  fclose(file);

  if (if_fail == -1) return EXIT_FAILURE;
  return EXIT_SUCCESS;



  // hunk_next(&hunk, file);
  // // adjust_additions_index(500);
  // debug("hunk.type: %d", hunk.type);
  // int c;
  // // int twice = 0;
  // for (int i = 0; i < 600; i++) {
  //   c = hunk_getc(&hunk, file);
  //   if (c == ERR) {
  //     error("returned error");
  //     break;
  //   } else if (c == EOF) {
  //     debug("returned EOF");
  //     break;
  //   } else if (c == EOS) {
  //     info("returned EOS");
  //     break;
  //     // twice++;
  //   } else
  //     debug("returned %c (%d)\n", c, c);
  // }
  // hunk_show(&hunk, stdout);
  // hunk_next(&hunk, file);
  // for (int i = 0; i < 200; i++) hunk_getc(&hunk, file);
  // hunk_show(&hunk, stdout);
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */
