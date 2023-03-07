#include <criterion/criterion.h>
#include <criterion/logging.h>

#include "buffer.h"
#include "fliki.h"
#include "global.h"

Test(patch_suite, fliki_clone_file) {

  FILE* in = fopen("rsrc/file2", "r");
  FILE* diff = fopen("rsrc/empty", "r");
  FILE* out = fopen("test_output/clone.out", "w");

  patch(in, out, diff);

  fclose(in);
  fclose(diff);
  fclose(out);

  char *cmp = "cmp test_output/clone.out rsrc/file2";

  int return_code = WEXITSTATUS(system(cmp));
  cr_assert_eq(return_code, EXIT_SUCCESS,
               "Program output did not match reference output.");
}