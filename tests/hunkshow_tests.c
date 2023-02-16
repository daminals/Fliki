#include "fliki.h"
#include "global.h"
#include "buffer.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>


Test(hunkshow_suite, fliki_hunk_show_empty_file1_test) {
  // 0a1,5
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/empty_file1.diff", "r");
  FILE *testread = fopen("rsrc/empty_file1.diff", "r");
  FILE *testwrite = fopen("test_output/hunkshow_empty_file1.out", "w");
  // define an array of strings
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  // read hunk
  for (int i=0;i<500;i++) hunk_getc(&hunk, file);
  fclose(file);
  hunk_show(&hunk, testwrite);
  fclose(testwrite);
  FILE *confirm_read = fopen("test_output/hunkshow_empty_file1.out", "r");
  // hunk show should print the same chars as empty_file1.diff
  int i=0;
  while(!feof(testread)) {
    char c = fgetc(testread);
    char d = fgetc(confirm_read);
    cr_assert_eq(c, d, "hunk_show() failed to print the same chars as the diff file. Error at location: %d, '%c' (%d) != '%c' (%d)", i,c, c, d, d);
    i++;
  }
  fclose(testread);
  fclose(confirm_read);
}

Test(hunkshow_suite, fliki_hunk_show_file1_empty_test) {
  // 1,5d0
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/file1_empty.diff", "r");
  FILE *testread = fopen("rsrc/file1_empty.diff", "r");
  FILE *testwrite = fopen("test_output/hunkshow_file1_empty.out", "w");
  // define an array of strings
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  // read hunk
  for (int i=0;i<500;i++) hunk_getc(&hunk, file);
  fclose(file);
  hunk_show(&hunk, testwrite);
  fclose(testwrite);
  FILE *confirm_read = fopen("test_output/hunkshow_file1_empty.out", "r");
  // hunk show should print the same chars as empty_file1.diff
  while(!feof(testread)) {
    char c = fgetc(testread);
    char d = fgetc(confirm_read);
    cr_assert_eq(c, d, "hunk_show() failed to print the same chars as the diff file. Error at char %c (%d) and %c (%d)", c, c, d, d);
  }
  fclose(testread);
  fclose(confirm_read);
}

Test(hunkshow_suite, fliki_hunk_show_hunk_max_test) {
  // 0a1,600
  // hunk 1
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/hunk_max.diff", "r");
  FILE *testread = fopen("rsrc/hunk_max.diff", "r");
  FILE *testwrite = fopen("test_output/hunkshow_hunk_max.out", "w");
  // define an array of strings
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  // read hunk
  for (int i=0;i<600;i++) hunk_getc(&hunk, file);
  fclose(file);
  hunk_show(&hunk, testwrite);
  fclose(testwrite);
  FILE *confirm_read = fopen("test_output/hunkshow_hunk_max.out", "r");
  // hunk show should print the same chars as empty_file1.diff
  int i=0;
  while(i<HUNK_MAX+6) { // plus 7 due to header, -1 due to hunk_max limit
    char c = fgetc(testread);
    char d = fgetc(confirm_read);
    cr_assert_eq(c, d, "hunk_show() failed to print the same chars as the diff file. Error at location: %d, '%c' (%d) != '%c' (%d)", i,c, c, d, d);
    i++;
    // printf("%c", c);
  }
  // printf("\n\n\n\n\n");
  // for (int k=490;k<HUNK_MAX;k++) printf("%c(%d), ", hunk_additions_buffer[k],hunk_additions_buffer[k]);
  // loop three times
  for (int j=0;j<3;j++) {
    char d = fgetc(confirm_read);
    cr_assert_eq('.', d, "hunk_show() failed to print the same chars as the diff file. Error at location: %d, '%c' (%d) != '%c' (%d)", j+i,'.', '.', d, d);
  }
  i+=3;
  char d = fgetc(confirm_read);
  cr_assert_eq('\n', d, "hunk_show() failed to print the same chars as the diff file. Error at location: %d, '%c' (%d) != '%c' (%d)", i++,'newline', 'newline', d, d);
  d = fgetc(confirm_read);
  cr_assert_eq(EOF, d, "hunk_show() failed to print the same chars as the diff file. Error at location: %d, '%c' (%d) != '%c' (%d)", i++,'EOF', 'EOF', d, d);

  fclose(testread);
  fclose(confirm_read);
}

Test(hunkshow_suite, fliki_hunk_show_hunk_max2_test) {
  // 0a1,53
  // hunk 1
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/hunk_max2.diff", "r");
  FILE *testread = fopen("rsrc/hunk_max2.diff", "r");
  FILE *testwrite = fopen("test_output/hunkshow_hunk_max2.out", "w");
  // file ends at exactly '\n', preventing truncation (e.g. hunk_addition_buffer[511] == '\n')
  // define an array of strings
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  // read hunk
  for (int i=0;i<600;i++) hunk_getc(&hunk, file);
  fclose(file);
  hunk_show(&hunk, testwrite);
  fclose(testwrite);
  FILE *confirm_read = fopen("test_output/hunkshow_hunk_max2.out", "r");
  
  // printf("\n\n\n\n\n");
  // for (int k=490;k<HUNK_MAX;k++) printf("%c(%d), ", hunk_additions_buffer[k],hunk_additions_buffer[k]);

  // hunk show should print the same chars as empty_file1.diff
  int i=0;
  while(i<HUNK_MAX+5) { // plus 7 due to header, -1 due to hunk_max limit
    char c = fgetc(testread);
    char d = fgetc(confirm_read);
    cr_assert_eq(c, d, "hunk_show() failed to print the same chars as the diff file. Error at location: %d, '%c' (%d) != '%c' (%d)", i,c, c, d, d);
    i++;
    // printf("%c", c);
  }
  // loop three times
  for (int j=0;j<3;j++) {
    char d = fgetc(confirm_read);
    cr_assert_eq('.', d, "hunk_show() failed to print the same chars as the diff file. Error at location: %d, '%c' (%d) != '%c' (%d)", j+i,'.', '.', d, d);
  }
  i+=3;
  char d = fgetc(confirm_read);
  cr_assert_eq('\n', d, "hunk_show() failed to print the same chars as the diff file. Error at location: %d, '%c' (%d) != '%c' (%d)", i++,'newline', 'newline', d, d);
  d = fgetc(confirm_read);
  cr_assert_eq(EOF, d, "hunk_show() failed to print the same chars as the diff file. Error at location: %d, '%c' (%d) != '%c' (%d)", i++,'EOF', 'EOF', d, d);

  fclose(testread);
  fclose(confirm_read);
}