#include <criterion/criterion.h>
#include <criterion/logging.h>

#include "buffer.h"
#include "fliki.h"
#include "global.h"

Test(blackbox, fliki_file2_file3_blackbox) {
  char *cmd =
      "bin/fliki rsrc/file2_file3.diff < rsrc/file2 > "
      "test_output/blackbox_file2_file3.out";
  char *cmp = "cmp test_output/blackbox_file2_file3.out rsrc/file3";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);
  return_code = WEXITSTATUS(system(cmp));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program output did not match reference output.");
}

Test(blackbox, fliki_file3_file2_blackbox) {
  char *cmd =
      "bin/fliki rsrc/file3_file2.diff < rsrc/file3 > "
      "test_output/blackbox_file3_file2.out";
  char *cmp = "cmp test_output/blackbox_file3_file2.out rsrc/file2";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);
  return_code = WEXITSTATUS(system(cmp));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program output did not match reference output.");
}
Test(blackbox, fliki_does_not_exist_blackbox) {
  char *cmd =
      "bin/fliki rsrc/does_not_exist.diff < rsrc/empty > "
      "test_output/blackbox_does_not_exist.out";
  // char *cmp = "cmp test_output/blackbox_empty_file1.out rsrc/file1";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_FAILURE,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);
  // return_code = WEXITSTATUS(system(cmp));
  // cr_assert_eq(return_code, EXIT_SUCCESS,
  //              "Program output did not match reference output.");
}

Test(blackbox, fliki_empty_file1_blackbox) {
  char *cmd =
      "bin/fliki rsrc/empty_file1.diff < rsrc/empty > "
      "test_output/blackbox_empty_file1.out";
  char *cmp = "cmp test_output/blackbox_empty_file1.out rsrc/file1";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);
  return_code = WEXITSTATUS(system(cmp));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program output did not match reference output.");
}
Test(blackbox, fliki_file1_empty_blackbox) {
  char *cmd =
      "bin/fliki rsrc/file1_empty.diff < rsrc/file1 > "
      "test_output/blackbox_file1_empty.out";
  char *cmp = "cmp test_output/blackbox_file1_empty.out rsrc/empty";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);
  return_code = WEXITSTATUS(system(cmp));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program output did not match reference output.");
}
Test(blackbox, fliki_file2_file1_blackbox) {
  char *cmd =
      "bin/fliki rsrc/file2_file1.diff < rsrc/file2 > "
      "test_output/blackbox_file2_file1.out";
  char *cmp = "cmp test_output/blackbox_file2_file1.out rsrc/file1";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);
  return_code = WEXITSTATUS(system(cmp));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program output did not match reference output.");
}

Test(blackbox, fliki_bad_input_blackbox) {
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

Test(blackbox, fliki_bad_inputq_blackbox) {
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