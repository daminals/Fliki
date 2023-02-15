#include <stdio.h>

// #include "fliki.h"

extern FILE *open_file(char *filename);
extern int strLen(char *str1);
extern int strEqlz(char *str1, char *str2);
char set_hunk_type_char(HUNK *hp);
extern int did_hunk_next_run;