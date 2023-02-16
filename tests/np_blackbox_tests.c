#include <criterion/criterion.h>
#include <criterion/logging.h>

#include "buffer.h"
#include "fliki.h"
#include "global.h"

Test(blackbox_np, fliki_file2_file3np_blackbox) {
  char *cmd =
      "bin/fliki -n rsrc/file2_file3.diff < rsrc/file2 > "
      "test_output/blackbox_file2_file3np.out";
  // char *cmp = "cmp test_output/blackbox_file2_file3.out rsrc/file3";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);

  FILE *fp = fopen("test_output/blackbox_file2_file3np.out", "r");
  int c = fgetc(fp);
  cr_assert_eq(-1, c, "Program output did not match expected output.");
  fclose(fp);
}

Test(blackbox_np, fliki_file3_file2np_blackbox) {
  char *cmd =
      "bin/fliki -n rsrc/file3_file2.diff < rsrc/file3 > "
      "test_output/blackbox_file3_file2np.out";
  // char *cmp = "cmp test_output/blackbox_file3_file2np.out rsrc/file2";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);
  FILE *fp = fopen("test_output/blackbox_file3_file2np.out", "r");
  int c = fgetc(fp);
  cr_assert_eq(-1, c, "Program output did not match expected output.");
  fclose(fp);
}

Test(blackbox_np, fliki_empty_file1np_blackbox) {
  char *cmd =
      "bin/fliki -n rsrc/empty_file1.diff < rsrc/empty > "
      "test_output/blackbox_empty_file1np.out";
  // char *cmp = "cmp test_output/blackbox_empty_file1.out rsrc/file1";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);
  FILE *fp = fopen("test_output/blackbox_empty_file1np.out", "r");
  int c = fgetc(fp);
  cr_assert_eq(-1, c, "Program output did not match expected output.");
  fclose(fp);
}
Test(blackbox_np, fliki_file1_emptynp_blackbox) {
  char *cmd =
      "bin/fliki -n rsrc/file1_empty.diff < rsrc/file1 > "
      "test_output/blackbox_file1_emptynp.out";
  char *cmp = "cmp test_output/blackbox_file1_empty.out rsrc/empty";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);
  FILE *fp = fopen("test_output/blackbox_file1_emptynp.out", "r");
  int c = fgetc(fp);
  cr_assert_eq(-1, c, "Program output did not match expected output.");
  fclose(fp);
}

Test(blackbox_np, fliki_file2_file1np_blackbox) {
  char *cmd =
      "bin/fliki -n rsrc/file2_file1.diff < rsrc/file2 > "
      "test_output/blackbox_file2_file1np.out";

  int return_code = WEXITSTATUS(system(cmd));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program exited with 0x%x instead of EXIT_SUCCESS", return_code);

  FILE *fp = fopen("test_output/blackbox_file2_file1np.out", "r");
  int c = fgetc(fp);
  cr_assert_eq(-1, c, "Program output did not match expected output.");
  fclose(fp);
}