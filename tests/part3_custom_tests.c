#include <criterion/criterion.h>
#include <criterion/logging.h>

#include "fliki.h"
#include "funcs.h"
#include "global.h"

static char *progname = "bin/fliki";

Test(basecode_suite, fliki_hunk_next_file1_file2_test) {
  // 1,2c1
  // hunk 1
  int hunk_old_start = 1;
  int hunk_old_end = 2;
  HUNK_TYPE hunk_type = HUNK_CHANGE_TYPE;
  int hunk_new_start = 1;
  int hunk_new_end = 1;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/file1_file2.diff", "r");
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  fclose(file);
  // check hunk
  cr_assert_eq(hunk.old_start, hunk_old_start,
               "Invalid hunk.old_start.  Got: %d | Expected: %d",
               hunk.old_start, hunk_old_start);
  cr_assert_eq(hunk.old_end, hunk_old_end,
               "Invalid hunk.old_end.  Got: %d | Expected: %d", hunk.old_end,
               hunk_old_end);
  cr_assert_eq(hunk.type, hunk_type,
               "Invalid hunk.type.  Got: %d | Expected: %d", hunk.type,
               hunk_type);
  cr_assert_eq(hunk.new_start, hunk_new_start,
               "Invalid hunk.new_start.  Got: %d | Expected: %d",
               hunk.new_start, hunk_new_start);
  cr_assert_eq(hunk.new_end, hunk_new_end,
               "Invalid hunk.new_end.  Got: %d | Expected: %d", hunk.new_end,
               hunk_new_end);
}

// Test(basecode_suite, fliki_hunk_next_file1_file2_middleLine_test) {
//   // 3a3
//   // hunk 2
//   int hunk_old_start = 3;
//   int hunk_old_end = 3;
//   HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
//   int hunk_new_start = 3;
//   int hunk_new_end = 3;
//   // open file rsrc/file1_file2.diff
//   FILE *file = fopen("rsrc/file1_file2.diff", "r");
//   // loop thru to middle of line
//   for (int i = 0; i < 12; i++)  // middle of nowhere in the line
//     fgetc(file);

//   // read hunk
//   HUNK hunk;
//   hunk_next(&hunk, file);
//   fclose(file);
//   // check hunk
//   cr_assert_eq(hunk.old_start, hunk_old_start,
//                "Invalid hunk.old_start.  Got: %d | Expected: %d",
//                hunk.old_start, hunk_old_start);
//   cr_assert_eq(hunk.old_end, hunk_old_end,
//                "Invalid hunk.old_end.  Got: %d | Expected: %d", hunk.old_end,
//                hunk_old_end);
//   cr_assert_eq(hunk.type, hunk_type,
//                "Invalid hunk.type.  Got: %d | Expected: %d", hunk.type,
//                hunk_type);
//   cr_assert_eq(hunk.new_start, hunk_new_start,
//                "Invalid hunk.new_start.  Got: %d | Expected: %d",
//                hunk.new_start, hunk_new_start);
//   cr_assert_eq(hunk.new_end, hunk_new_end,
//                "Invalid hunk.new_end.  Got: %d | Expected: %d", hunk.new_end,
//                hunk_new_end);
// }

Test(basecode_suite, fliki_hunk_next_file1_file2_twice_test) {
  // 3a3
  // hunk 2
  int hunk_old_start = 3;
  int hunk_old_end = 3;
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  int hunk_new_start = 3;
  int hunk_new_end = 3;
  int local_hunk_serial = 2;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/file1_file2.diff", "r");
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  hunk_next(&hunk, file);  // read next hunk serial
  fclose(file);
  // check hunk
  cr_assert_eq(hunk.old_start, hunk_old_start,
               "Invalid hunk.old_start.  Got: %d | Expected: %d",
               hunk.old_start, hunk_old_start);
  cr_assert_eq(hunk.old_end, hunk_old_end,
               "Invalid hunk.old_end.  Got: %d | Expected: %d", hunk.old_end,
               hunk_old_end);
  cr_assert_eq(hunk.type, hunk_type,
               "Invalid hunk.type.  Got: %d | Expected: %d", hunk.type,
               hunk_type);
  cr_assert_eq(hunk.new_start, hunk_new_start,
               "Invalid hunk.new_start.  Got: %d | Expected: %d",
               hunk.new_start, hunk_new_start);
  cr_assert_eq(hunk.new_end, hunk_new_end,
               "Invalid hunk.new_end.  Got: %d | Expected: %d", hunk.new_end,
               hunk_new_end);
  cr_assert_eq(hunk.serial, local_hunk_serial,
               "Invalid hunk.serial.  Got: %d | Expected: %d", hunk.serial,
               local_hunk_serial);
}

Test(basecode_suite, fliki_hunk_next_empty_file1_test) {
  // 0a1,5
  // hunk 1
  int hunk_old_start = 0;
  int hunk_old_end = 0;
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  int hunk_new_start = 1;
  int hunk_new_end = 5;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/empty_file1.diff", "r");
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  fclose(file);
  // check hunk
  cr_assert_eq(hunk.old_start, hunk_old_start,
               "Invalid hunk.old_start.  Got: %d | Expected: %d",
               hunk.old_start, hunk_old_start);
  cr_assert_eq(hunk.old_end, hunk_old_end,
               "Invalid hunk.old_end.  Got: %d | Expected: %d", hunk.old_end,
               hunk_old_end);
  cr_assert_eq(hunk.type, hunk_type,
               "Invalid hunk.type.  Got: %d | Expected: %d", hunk.type,
               hunk_type);
  cr_assert_eq(hunk.new_start, hunk_new_start,
               "Invalid hunk.new_start.  Got: %d | Expected: %d",
               hunk.new_start, hunk_new_start);
  cr_assert_eq(hunk.new_end, hunk_new_end,
               "Invalid hunk.new_end.  Got: %d | Expected: %d", hunk.new_end,
               hunk_new_end);
}

Test(basecode_suite, fliki_hunk_next_file1_empty_test) {
  // 1,5d0
  // hunk 1
  int hunk_old_start = 1;
  int hunk_old_end = 5;
  HUNK_TYPE hunk_type = HUNK_DELETE_TYPE;
  int hunk_new_start = 0;
  int hunk_new_end = 0;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/file1_empty.diff", "r");
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  fclose(file);
  // check hunk
  cr_assert_eq(hunk.old_start, hunk_old_start,
               "Invalid hunk.old_start.  Got: %d | Expected: %d",
               hunk.old_start, hunk_old_start);
  cr_assert_eq(hunk.old_end, hunk_old_end,
               "Invalid hunk.old_end.  Got: %d | Expected: %d", hunk.old_end,
               hunk_old_end);
  cr_assert_eq(hunk.type, hunk_type,
               "Invalid hunk.type.  Got: %d | Expected: %d", hunk.type,
               hunk_type);
  cr_assert_eq(hunk.new_start, hunk_new_start,
               "Invalid hunk.new_start.  Got: %d | Expected: %d",
               hunk.new_start, hunk_new_start);
  cr_assert_eq(hunk.new_end, hunk_new_end,
               "Invalid hunk.new_end.  Got: %d | Expected: %d", hunk.new_end,
               hunk_new_end);
}

Test(basecode_suite, fliki_hunk_getc_file1_empty_test) {
  // 1,5d0
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_DELETE_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/file1_empty.diff", "r");
  // FILE *file2 = fopen("rsrc/file1_empty.diff", "r");
  // char c = fgetc(file2);
  // while (!(c == '\n')) c = fgetc(file2);
  // define an array of strings
  char *lines[] = {"This is file1.\n", "This line does not appear in file2.\n",
                   "This line is in common between file1 and file2.\n",
                   "Here is another line that they have in common.\n",
                   "This line also does not appear in file2.\n"};

  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  cr_assert_eq(hunk.type, hunk_type,
               "Invalid hunk.type.  Got: %d | Expected: %d", hunk.type,
               hunk_type);
  // read hunk
  // line 1 of hunk
  // repeat for 5 lines
  for (int i = 0; i < 5; i++) {
    // loop through the characters in lines
    for (int j = 0; j < strLen(lines[i]); j++) {
      char c = lines[i][j];
      char a = hunk_getc(&hunk, file);
      cr_assert_eq(c, a, "Invalid hunk_getc. Got: %c | Expected: %c", a, c);
    }
  }
  char check_eof = hunk_getc(&hunk, file);
  cr_assert_eq(EOS, check_eof, "File is complete. Got: %d | Expected: EOS(-3)", check_eof);
  fclose(file);
  // check hunk
}

Test(basecode_suite, fliki_hunk_getc_empty_file1_test) {
  // 1,5d0
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/empty_file1.diff", "r");
  // define an array of strings
  char *lines[] = {"This is file1.\n", "This line does not appear in file2.\n",
                   "This line is in common between file1 and file2.\n",
                   "Here is another line that they have in common.\n",
                   "This line also does not appear in file2.\n"};
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  cr_assert_eq(hunk.type, hunk_type,
               "Invalid hunk.type.  Got: %d | Expected: %d", hunk.type,
               hunk_type);
  // read hunk
  // line 1 of hunk
  // repeat for 5 lines
  for (int i = 0; i < 5; i++) {
    // loop through the characters in lines
    for (int j = 0; j < strLen(lines[i]); j++) {
      char c = lines[i][j];
      char a = hunk_getc(&hunk, file);
      cr_assert_eq(c, a, "Invalid hunk_getc. Got: %c | Expected: %c", a, c);
    }
  }
  char check_eof = hunk_getc(&hunk, file);
  cr_assert_eq(EOS, check_eof, "File is complete. Got: %d | Expected: EOS(-3)", check_eof);
  fclose(file);
  // check hunk
}


Test(basecode_suite, fliki_hunk_getc_file1_file2_test) {
  // 1,2c1
  // 3a3
  // 5d4
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_DELETE_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/file1_file2.diff", "r");
  // define an array of strings
  char *hunk1_lines_section1[] = {"This is file1.\n",
                         "This line does not appear in file2.\n",};
  char *hunk1_lines_section2[] = {"This is file2.\n"};
  char *hunk2_lines[] = {"This line does not appear in file1.\n"};
  char *hunk3_lines[] = {"This line also does not appear in file2.\n"};

  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
    // hunk_show(&hunk,stdout);
  // read hunk
  // line 1 of hunk
  // repeat for 5 lines
  // length of the array

  for (int i = 0; i < 2; i++) {
    // loop through the characters in lines
    for (int j = 0; j < strLen(hunk1_lines_section1[i]); j++) {
      char c = hunk1_lines_section1[i][j];
      char a = hunk_getc(&hunk, file);
      cr_assert_eq(c, a,
                   "Invalid hunk_getc. Error occured at hunk1:line-%d:char-%d. "
                   "Got: %c | Expected: %c",
                   i, j, a, c);
    }
  }
  char check_eof = hunk_getc(&hunk, file);
  cr_assert_eq(EOS, check_eof, "Hunk is complete. Got: %c | Expected: EOF", check_eof);
  for (int i = 0; i < 1; i++) {
    // loop through the characters in lines
    for (int j = 0; j < strLen(hunk1_lines_section2[i]); j++) {
      char c = hunk1_lines_section2[i][j];
      char a = hunk_getc(&hunk, file);
      cr_assert_eq(c, a,
                   "Invalid hunk_getc. Error occured at hunk1:line-%d:char-%d. "
                   "Got: %c | Expected: %c",
                   i, j, a, c);
    }
  }

  check_eof = hunk_getc(&hunk, file);
  cr_assert_eq(EOS, check_eof, "Hunk is complete. Got: %c | Expected: EOF", check_eof);
  hunk_next(&hunk, file);
    // hunk_show(&hunk,stdout);

  // char checkc;
  for (int i = 0; i < 1 ; i++) {
    // loop through the characters in lines
    for (int j = 0; j < strLen(hunk2_lines[i]); j++) {
      char c = hunk2_lines[i][j];
      // checkc=c;
      char a = hunk_getc(&hunk, file);
      cr_assert_eq(c, a, "Invalid hunk_getc. Error occured at hunk2:line-%d:char-%d. Got: %c | Expected: %c",i,j, a, c);
    }
  }
  // printf("c before next hunk_next: %c,%d\n",checkc,checkc);

  hunk_next(&hunk, file);
    // hunk_show(&hunk,stdout);

  for (int i = 0; i < 1 ; i++) {
    // loop through the characters in lines
    for (int j = 0; j < strLen(hunk3_lines[i]); j++) {
      char c = hunk3_lines[i][j];
      char a = hunk_getc(&hunk, file);
      cr_assert_eq(c, a, "Invalid hunk_getc. Error occured at hunk3:line-%d:char-%d. Got: %c(%d) | Expected: %c",i,j, a, c,c);
      // printf("%c", a);
    }
  }
  check_eof = hunk_getc(&hunk, file);
  cr_assert_eq(EOS, check_eof, "File is complete. Got: %d | Expected: EOS(-3)", check_eof);

  fclose(file);
  // check hunk
}

Test(basecode_suite, fliki_hunk_getc_file1_file2_error_test) {
  // 1,2c1
  // 3a3
  // 5d4
  // hunk 2

  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/file1_file2.diff", "r");
  // define an array of strings
  char *hunk2_lines[] = {"This line does not appear in file1.\n"};

  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file); // skip change hunk too much work
  hunk_next(&hunk, file);
  // read hunk
  // line 1 of hunk
  // repeat for 5 lines
  // length of the array
  for (int i = 0; i < 1; i++) {
    // loop through the characters in lines
    for (int j = 0; j < strLen(hunk2_lines[i]); j++) {
      char c = hunk2_lines[i][j];
      char a = hunk_getc(&hunk, file);
      // printf("%c", a);
      cr_assert_eq(c, a,
                   "Invalid hunk_getc. Error occured at hunk1:line-%d:char-%d. "
                   "Got: %c | Expected: %c",
                   i, j, a, c);
    }
  }
  char check_eof = hunk_getc(&hunk, file);
  cr_assert_eq(EOS, check_eof, "Hunk is complete. Got: %d | Expected: EOS(-3)", check_eof);
  check_eof = hunk_getc(&hunk, file);
  // printf("%d",hunk_getc(&hunk, file));

  cr_assert_eq(ERR, check_eof, "Hunk is complete. Got: %d | Expected: ERR(-2)", check_eof);
  check_eof = hunk_getc(&hunk, file);
  cr_assert_eq(ERR, check_eof, "Hunk is complete. Got: %d | Expected: ERR(-2)", check_eof);
  check_eof = hunk_getc(&hunk, file);
  cr_assert_eq(ERR, check_eof, "Hunk is complete. Got: %d | Expected: ERR(-2)", check_eof);

  fclose(file);
  // check hunk
}

Test(basecode_suite, fliki_hunk_getc_b4_hunk_next_test) {
  // 1,5d0
  // hunk 1
  // HUNK_TYPE hunk_type = HUNK_DELETE_TYPE;
  FILE *file = fopen("rsrc/file1_empty.diff", "r");
  // read hunk
  HUNK hunk;
  // hunk_next(&hunk, file);
  // call hunk_getc before hunk_next
  char a = hunk_getc(&hunk, file);
  cr_assert_eq(ERR, a, "Invalid hunk_getc. Got: %c | Expected: %c", a, ERR);
  // should throw err
}

Test(basecode_suite, fliki_hunk_next_EOF_test) {
  // 1,5d0
  // hunk 1
  // HUNK_TYPE hunk_type = HUNK_DELETE_TYPE;
  FILE *file = fopen("rsrc/file1_empty.diff", "r");
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  int should_be_eof_lol = hunk_next(&hunk, file);
  // call hunk_getc before hunk_next
  // char a = hunk_getc(&hunk, file);
  cr_assert_eq(EOF, should_be_eof_lol, "Invalid hunk_getc. Got: %d | Expected: %d", should_be_eof_lol, EOF);
  // should throw err
}