#include <criterion/criterion.h>
#include <criterion/logging.h>

#include "fliki.h"
#include "global.h"

static char *progname = "bin/fliki";

Test(basecode_suite, validargs_no_patch_quiet_mode_test) {
    char *argv[] = {progname, "-n", "-q", "mydiffs", NULL};
    int argc = (sizeof(argv) / sizeof(char *)) - 1;
    int ret = validargs(argc, argv);
    int exp_ret = 0;
    int opt = global_options;
    int exp_opt = NO_PATCH_OPTION | QUIET_OPTION;
    cr_assert_eq(ret, exp_ret, "Invalid return for validargs.  Got: %d | Expected: %d",
		 ret, exp_ret);
    cr_assert_eq(opt, exp_opt, "Invalid options settings.  Got: 0x%x | Expected: 0x%x",
		 opt, exp_opt);
}

Test(basecode_suite, validargs_help_failure) {
    char *argv[] = {progname, "-n","-h", NULL};
    int argc = (sizeof(argv) / sizeof(char *)) - 1;
    int ret = validargs(argc, argv);
    int exp_ret = -1; // exit failure
    int opt = global_options;
    int flag = 0;
    cr_assert_eq(ret, exp_ret, "Invalid return for validargs.  Got: %d | Expected: %d",
		 ret, exp_ret);
    cr_assert_eq(opt & flag, flag, "Correct bit (0x%x) not set for -h. Got: %x",
		 flag, opt);
}

Test(basecode_suite, validargs_all_correct_test) {
    char *argv[] = {progname, "-q", "-n", "foo", NULL};
    int argc = (sizeof(argv) / sizeof(char *)) - 1;
    int exp_ret = 0;
    int ret = validargs(argc, argv);
    int opt = global_options;
    int exp_opt = NO_PATCH_OPTION | QUIET_OPTION;
    cr_assert_eq(ret, exp_ret, "Invalid return for validargs.  Got: %d | Expected: %d",
		 ret, exp_ret);
    cr_assert_eq(opt, exp_opt, "Invalid options settings.  Got: 0x%x | Expected: 0x%x",
		 opt, exp_opt);
}

Test(basecode_suite, validargs_multiple_files) {
    char *argv[] = {progname, "foo", "bar", NULL};
    int argc = (sizeof(argv) / sizeof(char *)) - 1;
    int exp_ret = -1;
    int ret = validargs(argc, argv);
    int opt = global_options;
    int exp_opt = 0;
    cr_assert_eq(ret, exp_ret, "Invalid return for validargs.  Got: %d | Expected: %d",
		 ret, exp_ret);
    cr_assert_eq(opt, exp_opt, "Invalid options settings.  Got: 0x%x | Expected: 0x%x",
		 opt, exp_opt);
}