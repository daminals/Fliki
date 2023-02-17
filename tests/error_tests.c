#include <criterion/criterion.h>
#include <criterion/logging.h>

#include "fliki.h"
#include "global.h"

Test(error_suite, fliki_bad_input_blackbox) {
  char *cmd =
      "bin/fliki rsrc/file2_file1.diff < rsrc/file1 2> "
      "test_output/bad_input.out";
  // char *cmp = "cmp test_output/bad_input.out rsrc/file1";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_FAILURE,
               "Program exited with 0x%x instead of EXIT_FAILURE", return_code);

  // read stderr (was redirected into test_output/bad_input.out)
  FILE *fp = fopen("test_output/bad_input.out", "r");
  int c = fgetc(fp);

  // return_code = WEXITSTATUS(system(cmp));
  cr_assert_neq(-1, c, "Program output did not match expected output.");
  fclose(fp);
}

Test(error_suite, fliki_bad_inputq_blackbox) {
  char *cmd =
      "bin/fliki -q rsrc/file2_file1.diff < rsrc/file1 2> "
      "test_output/bad_inputq.out";
  // char *cmp = "cmp test_output/bad_input.out rsrc/file1";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_FAILURE,
               "Program exited with 0x%x instead of EXIT_FAILURE", return_code);

  // read stderr (was redirected into test_output/bad_input.out)
  FILE *fp = fopen("test_output/bad_inputq.out", "r");
  int c = fgetc(fp);

  // return_code = WEXITSTATUS(system(cmp));
  cr_assert_eq(-1, c, "Program output did not match expected output.");
  fclose(fp);
}

Test(error_suite, fliki_unexpected_eof_test) {
  // 0a1,5
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/baddiffs/eof.diff", "r");
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  int c = hunk_next(&hunk, file);
  cr_assert_eq(c, ERR, "Expected ERR, got %d", c);
  fclose(file);
  // check hunk
}

Test(error_suite, fliki_hunk_next_unexpected_eof_test) {
  // 0a1,5
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/baddiffs/eof.diff", "r");
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  int c = hunk_next(&hunk, file);
  cr_assert_eq(c, ERR, "Expected ERR, got %d", c);
  fclose(file);
  // check hunk
}

Test(error_suite, fliki_blackbox_unexpected_eof_test) {
  char *cmd =
      "bin/fliki rsrc/baddiffs/eof.diff < rsrc/empty 2> "
      "test_output/blackbox_unexpected_eof.out";
  char *cmp = "cmp test_output/blackbox_unexpected_eof.out rsrc/file1";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_FAILURE,
               "Program exited with 0x%x instead of EXIT_FAILURE", return_code);
  // return_code = WEXITSTATUS(system(cmp));
  // cr_assert_eq(return_code, EXIT_SUCCESS,
  //              "Program output did not match reference output.");
}

Test(error_suite, fliki_hunk_getc_unexpected_eof_test) {
  // 0a1,5
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/baddiffs/eof.diff", "r");
  // read hunk
  HUNK hunk;
  hunk_next(&hunk, file);
  for (int i=0; i<32; i++) {
    hunk_getc(&hunk, file);
  }
  int c = hunk_getc(&hunk, file);
  printf("c: %d",c);
  // cr_assert_eq(c, ERR, "Expected ERR, got %d", c);
  fclose(file);
  // check hunk
}


Test(error_suite, fliki_hunk_next_bad_header_append_test) {
  // 0a1,5
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/baddiffs/append_input.diff", "r");
  // read hunk
  HUNK hunk;
  int c = hunk_next(&hunk, file);
  cr_assert_eq(c, ERR, "Expected ERR, got %d", c);
  fclose(file);
  // check hunk
}

Test(error_suite, fliki_blackbox_bad_header_append_test) {
  char *cmd =
      "bin/fliki rsrc/baddiffs/append_input.diff < rsrc/empty 2> "
      "test_output/blackbox_append_input.out";
  char *cmp = "cmp test_output/blackbox_append_input.out rsrc/file1";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_FAILURE,
               "Program exited with 0x%x instead of EXIT_FAILURE", return_code);
  // return_code = WEXITSTATUS(system(cmp));
  // cr_assert_eq(return_code, EXIT_SUCCESS,
  //              "Program output did not match reference output.");
}

Test(error_suite, fliki_hunk_next_bad_header_delete_test) {
  // 0a1,5
  // hunk 1
  HUNK_TYPE hunk_type = HUNK_APPEND_TYPE;
  // open file rsrc/file1_file2.diff
  FILE *file = fopen("rsrc/baddiffs/delete_input.diff", "r");
  // read hunk
  HUNK hunk;
  int c = hunk_next(&hunk, file);
  cr_assert_eq(c, ERR, "Expected ERR, got %d", c);
  fclose(file);
  // check hunk
}

Test(error_suite, fliki_blackbox_bad_header_delete_test) {
  char *cmd =
      "bin/fliki rsrc/baddiffs/delete_input.diff < rsrc/empty 2> "
      "test_output/blackbox_delete_input.out";
  char *cmp = "cmp test_output/blackbox_delete_input.out rsrc/file1";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_FAILURE,
               "Program exited with 0x%x instead of EXIT_FAILURE", return_code);
  // return_code = WEXITSTATUS(system(cmp));
  // cr_assert_eq(return_code, EXIT_SUCCESS,
  //              "Program output did not match reference output.");
}