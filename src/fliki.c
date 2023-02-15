#include "fliki.h"

#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "debug.h"
#include "funcs.h"
#include "global.h"

/*
All defined global variables:
  1. static int current_line_nums: count the number of new lines as you iterate
through hunk
  2. static int track_change_type: track whether change type is on delete or
append. 0 is delete, 1 is append
  3. static int newline_prev: tracks whether previous char is newline
  4. static int global_hunk_serial: current hunk serial
  5. int hunk_getc_EOSERR: tracks whether hunk_getc has reached end of hunk
  6. int return_error: whether hunk_getc should return ERR or not
  7. int symantic_err: symantic error
*/

// time to define some sexy global variables
/*
 * Count the number of new lines as you iterate through hunk
 */
static int current_line_nums = 0;
/*
 * Track whether change type is on delete or append. 0 is delete, 1 is append
 */
static int track_change_type = 0;
/*
  * tracks whether previous char is newline
  1: previous char is newline
  0: previous char is not newline
*/
static int newline_prev = 0;
/*
 * if hunk has EOS multiple times, return ERR
 */
static int hunk_getc_EOSERR = 0;
/*
 * Current Hunk
 */
int global_hunk_serial = 0;
/*
 * Whether hunk_getc should return ERR or not
 * 0: no
 * 1: yes
 */
int return_error = 0;
/*
 * symantic error
 * 0: no
 * 1: yes
 */
int symantic_err = 0;
/*
 * previous char for context if hunk_next is called after hunk_getc
 */
int did_hunk_next_run = 1;

// read a character of a file print it and then read the next
// char until the end of the file
static int read_file(FILE *file) {
  char c;
  while ((c = fgetc(file)) != EOF) {
    printf("%c", c);
  }
  return 0;
}

// open a file from a file name
FILE *open_file(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    // printf("file is null");
    return NULL;
  }
  // read_file(file);
  return file;
}

static int get_num(FILE *file, int start) {
  int num = start - '0';
  char c = fgetc(file);
  while (c >= '0' && c <= '9') {
    num = (num * 10) + (c - '0');
    // debug("%d",num);
    c = fgetc(file);
    // debug("c=%c",c);
  }
  // c = fgetc(file);  // next char when done counting
  ungetc(c, file);
  return num;
}

static char get_hunk_range(HUNK *hp, FILE *in, char c, int old_range) {
  if (!(c >= '0' && c <= '9')) return ERR;  // bad format
  // read the hunk header
  int start_int = get_num(in, c);
  // debug("start_int: %d", start_int);

  c = fgetc(in);  // undo ungetc, update c to current item

  // debug("is c comma?: %c", c);
  // complete the start_int
  // if (c >= '0' && c <= '9') {
  //   // if multiple digits, continue counting
  //   start_int = get_num(in, start_int);
  //   debug("start_int: %d", start_int);
  //   c = fgetc(in);
  // } else
  if (c == EOF) return ERR;
  if (old_range == 1) {
    hp->old_start = start_int;
  } else {
    // debug("new_start: %d", start_int);
    hp->new_start = start_int;
  }

  // continue reading the header
  // get end int
  // debug("after start_int c: %c", c);
  if (c == ',') {
    int end_int;
    c = fgetc(in);
    // debug("after comma c: %c", c);
    if (c >= '0' && c <= '9') {
      end_int = get_num(in, c);
      c = fgetc(in);
      // debug("after end_int c: %c", c);
    } else {
      hp->type = -1;
      return ERR;  // makes no sense
    }
    // continue if necessary
    // if (!(c == '\n' || c == EOF)) {
    //   if (c >= '0' && c <= '9') {
    //     end_int = get_num(in, end_int);
    //   } else
    // if (c == '\n' || c == EOF)
    //     return ERR;
    // }
    if (old_range == 1) {
      hp->old_end = end_int;
    } else {
      hp->new_end = end_int;
    }
    // end comma
  } else {
    if (old_range == 1) {
      hp->old_end = hp->old_start;
    } else {
      hp->new_end = hp->new_start;
    }
  }
  // debug("after hunk range c: %c", c);
  return c;
}

static int set_hunk_type(char c) {
  switch (c) {
    case 'c':
      return HUNK_CHANGE_TYPE;
      break;

    case 'a':
      return HUNK_APPEND_TYPE;
      break;

    case 'd':
      return HUNK_DELETE_TYPE;
      break;

    default:
      return -1;
      break;
  }
  return 0;
}
/*
 * initialize variables for hunk_next
 * resets current_line_nums, track_change_type, hunk_getc_EOSERR and
 * zero_out_buffer for use in hunk_next (and hunk_getc implicitly)
 */
static int hunk_next_reset() {
  // first line in the hunk
  current_line_nums = 0;
  // change type is always delete initially, switches to append later
  track_change_type = 0;
  // if hunk has EOS multiple time, return ERR
  // hunk can only have EOS once
  hunk_getc_EOSERR = 0;
  zero_out_buffer();  // restore buffer to all 0's
  return 0;
}

/**
 * @brief Get the header of the next hunk in a diff file.
 * @details This function advances to the beginning of the next hunk
 * in a diff file, reads and parses the header line of the hunk,
 * and initializes a HUNK structure with the result.
 *
 * @param hp  Pointer to a HUNK structure provided by the caller.
 * Information about the next hunk will be stored in this structure.
 * @param in  Input stream from which hunks are being read.
 * @return 0  if the next hunk was successfully located and parsed,
 * EOF if end-of-file was encountered or there was an error reading
 * from the input stream, or ERR if the data in the input stream
 * could not be properly interpreted as a hunk.
 */

int hunk_next(HUNK *hp, FILE *in) {
  // TO BE IMPLEMENTED
  // jump to next hunk header

  // if hunk is initialized, skip to next hunk

  // while (start_char == '>' || start_char == '<' || start_char == '-') {
  // actually should check if theres a newline

  // while (!(start_char >= '0' && start_char <= '9')) {
  //   // loop until find a newline, then check if number
  //   while ((c = fgetc(in)) != '\n') {
  //     if (c == EOF) return EOF;
  //   }
  //   c = fgetc(in);  // first char in a line
  //   // debug("c is %c in start char loop", c);
  //   start_char = c;
  // }

  // printf("hunk run:%d\n\n",did_hunk_next_run);
  char c;
  while (did_hunk_next_run == 0) {
    // printf("shawty loopin she going bananas");
    if ((c=hunk_getc(hp, in)) == ERR) 
      return ERR;
  }
  did_hunk_next_run = 0;
  // reset hunk
  global_hunk_serial++;
  hp->serial = global_hunk_serial;
  hunk_next_reset();

  c = fgetc(in); // first char in section

  if (c == EOF) {
    return EOF;
  }

  // char start_char = c;

  // broken hunk_getc version. fix if u have time
  // if (did_hunk_next_run != 0) {  // causing error with >
  //   debug("in start char loop");
  //   // while ((c = fgetc(in)) != '\n') {
  //   //   if (c == EOF) return EOF;
  //   // }
  //   // c = fgetc(in);  // first char in a line
  //   // start_char = c;
  //   while (c != EOS && c != ERR) {
  //     c = hunk_getc(hp, in);
  //   }
  //   if (c==ERR) return ERR;
  //   // c = hunk_getc(hp, in);
  //   info("c is %c(%d) - first EOS", c,c);
  //   if (hp->type == HUNK_CHANGE_TYPE) {
  //     c = hunk_getc(hp, in);
  //     while (c != EOS && c != ERR) {
  //       c = hunk_getc(hp, in);
  //     }
  //     if (c==ERR) return ERR;
  //     info("c is %c(%d) - second EOS", c,c);
  //   }
  //   // if (c == ERR) return ERR;
  //   error("c is %d", c);
  //   did_hunk_next_run = 0;
  //   return hunk_next(hp, in);
  // } else {
  //   c = fgetc(in);
  //   error("fresh char c is %d", c);
  // }
  // did_hunk_next_run = 1;
  // info("c is %c after prev_char", c);
  // if (c == EOF) {
  //   return EOF;
  // }
  // end broken hunkgetc version of this code

  // this is the start of the header signature
  // if c is a digit, then it is the start of the hunk header
  // this section will get the old start and old end of the hunk
  // debug("in hunk range, c is %c", c);
  c = get_hunk_range(hp, in, c, 1);
  // debug("finished hunk range 1. c is %c btw", c);

  // continue reading the header
  // after end_int, there should be a,c,d
  hp->type =
      set_hunk_type(c);  // if hunk is invalid set type to -1 and return err
  if (!(c == 'c' || c == 'a' || c == 'd')) {
    // debug("c is %c", c);
    // if single line_num, start=end, set hunk type
    return ERR;  // bad format
  }
  // debug("processed char and hunk type");

  // continue reading the header
  // get new start int
  c = fgetc(in);
  // debug("c after registering hunk type is %c", c);
  c = get_hunk_range(hp, in, c, 0);
  // debug("finished hunk range 2. header sig should be done. c is %c btw", c);
  newline_prev = 1;
  return 0;
}

/*
 interprets new lines in hunks
*/
int hunk_read_newline(char c, char check, int expected_line_nums, FILE *in,
                      HUNK *hp) {
  debug(
      "hunk read newline: c=%c (%d), check=%c, expected_line_nums=%d, "
      "current_line_nums=%d, hunk type=%d",
      c, c, check, expected_line_nums, current_line_nums, hp->type);

  // if c is number
  // debug("made it here, c is %d", c);
  if (c == EOF || (c >= '0' && c <= '9')) {
    // debug("expected line nums is %d, current line nums is %d",
    //       expected_line_nums, current_line_nums);
    if (expected_line_nums + 1 == current_line_nums) {
      // go back one character in file pointer
      warn("c has been ungot to %c", c);
      ungetc(c, in);
      newline_prev = 1;  // reset newline prev
      // debug("post eof c is %c", c);
      // if this is new line after end of hunk, then return EOS
      // and go back one to preserve header
      hunk_getc_EOSERR++;
      did_hunk_next_run = 1;
      if (hunk_getc_EOSERR == 1) return EOS;
      return ERR;
    }
  }

  if (!(c == check)) {
    return_error = 1;
    return ERR;
  }

  if (expected_line_nums < current_line_nums) {
    // if eof is next line, return eos
    return_error = 1;
    return ERR;
  }

  // current_line_nums++; // increment line nums before first char
  if ((c = fgetc(in)) != ' ') {
    return_error = 1;
    return ERR;
  }
  c = fgetc(in);
  return c;
}

/*
  consider if c is newline. Otherwise handle regularly
*/
int hunk_consider_newline(char c, FILE *in, HUNK *hp, int expected_line_nums,
                          int if_dash) {
  /*
    if_dash = 1 if c is a <
    if_dash = 0 if c is a >
    plays role in determining if newline is valid
  */
  char check;
  if (if_dash == 1) {
    check = '<';
  } else {
    check = '>';
  }

  if (c == '\n') {
    newline_prev = 1;
    current_line_nums++;
    // if ((expected_line_nums < current_line_nums) &&
    // (((hp->type==HUNK_CHANGE_TYPE) && (track_change_type==1)) ||
    // (hp->type!=HUNK_CHANGE_TYPE)) ) return ERR;
    return c;
  }

  // debug("current line nums is %d, expected is %d", current_line_nums,
  //       expected_line_nums);

  if (newline_prev == 1) {
    newline_prev = 0;
    // debug("new line slay");
    // c = fgetc(in); // first char in a line
    // check if changing from addition to deletion
    if (current_line_nums == 0) current_line_nums++;
    if (if_dash == 1) {
      if (c == '-') {
        if (expected_line_nums != current_line_nums - 1) {
          return_error = 1;
          symantic_err = 1;
          return ERR;
        }
        // must be 2 more '-' chars and a newline using for loop
        for (int i = 0; i < 2; i++) {
          if ((c = fgetc(in)) != '-') {
            return_error = 1;
            return ERR;
          }
        }
        if ((c = fgetc(in)) != '\n') {
          return_error = 1;
          return ERR;
        }
        // change to addition mode
        track_change_type = 1;
        current_line_nums = 0;
        newline_prev = 1;
        return EOS; // this is for change hunks
        // return hunk_getc(hp, in);
      } else {
        // if ((expected_line_nums < current_line_nums)) return ERR;
        // if its not a dashed line and line num crossed threshold, return ERR
        return hunk_read_newline(c, check, expected_line_nums, in, hp);
      }
    } else {
      return hunk_read_newline(c, check, expected_line_nums, in, hp);
    }
  } else {
    // lines start at 1
    if ((expected_line_nums < current_line_nums)) {
      return_error = 1;
      symantic_err = 1;
      return ERR;
    }
    // if line crosses acceptable threshold, return ERR only if not in change
    // mode change mode needs additional checks (like is it switching from
    // deletion to addition)
  }
  // regular char, return c
  return c;
}
/*
 * hunk_getc switch function
 * execute switch case for append and delete
 */
static char hunk_switchc(HUNK *hp, FILE *in, char c,
                         int switch_addition_deletion_type) {
  int expected_line_nums;
  // debug("switch_addition_deletion_type is %d",
  // switch_addition_deletion_type); debug("c is %c", c); should return char if
  // normal char, else handle it
  switch (switch_addition_deletion_type) {
    case 2:  // deletion mode
      expected_line_nums = hp->old_end - hp->old_start + 1;
      // moved to function
      return hunk_consider_newline(c, in, hp, expected_line_nums, 1);
      break;

    case 1:  // addition mode
      expected_line_nums = hp->new_end - hp->new_start + 1;
      return hunk_consider_newline(c, in, hp, expected_line_nums, 0);
      break;

    default:
      return ERR;
  }
}

/**
 * @brief  Get the next character from the data portion of the hunk.
 * @details  This function gets the next character from the data
 * portion of a hunk.  The data portion of a hunk consists of one
 * or both of a deletions section and an additions section,
 * depending on the hunk type (delete, append, or change).
 * Within each section is a series of lines that begin either with
 * the character sequence "< " (for deletions), or "> " (for additions).
 * For a change hunk, which has both a deletions section and an
 * additions section, the two sections are separated by a single
 * line containing the three-character sequence "---".
 * This function returns only characters that are actually part of
 * the lines to be deleted or added; characters from the special
 * sequences "< ", "> ", and "---\n" are not returned.
 * @param hdr  Data structure containing the header of the current
 * hunk.
 *
 * @param in  The stream from which hunks are being read.
 * @return  A character that is the next character in the current
 * line of the deletions section or additions section, unless the
 * end of the section has been reached, in which case the special
 * value EOS is returned.  If the hunk is ill-formed; for example,
 * if it contains a line that is not terminated by a newline character,
 * or if end-of-file is reached in the middle of the hunk, or a hunk
 * of change type is missing an additions section, then the special
 * value ERR (error) is returned.  The value ERR will also be returned
 * if this function is called after the current hunk has been completely
 * read, unless an intervening call to hunk_next() has been made to
 * advance to the next hunk in the input.  Once ERR has been returned,
 * then further calls to this function will continue to return ERR,
 * until a successful call to call to hunk_next() has successfully
 * advanced to the next hunk.
 */
int hunk_getc(HUNK *hp, FILE *in) {
  // what type of hunk is this?
  if (return_error == 1) return ERR;

  char c = fgetc(in);  // next character in file
  int switch_addition_deletion_type = hp->type;
  // deletion mode is first for change type
  if (switch_addition_deletion_type == 3) {
    // debug("change type hunk, track_change_type is %d", track_change_type);
    switch_addition_deletion_type = 2;
    if (track_change_type == 1) switch_addition_deletion_type = 1;
  }
  int hunk_return = hunk_switchc(hp, in, c, switch_addition_deletion_type);
  if (hunk_return == EOS || hunk_return == EOF || hunk_return == ERR)
    return hunk_return;
  // buffer functionality
  switch (switch_addition_deletion_type) {
    case 1:  // addition mode
      add_to_addition_buffer(hunk_return);
      break;
    case 2:  // deletion mode
      add_to_deletion_buffer(hunk_return);
      break;
    default:
      return ERR;
  }
  // did_hunk_next_run = 1;
  return hunk_return;
}

/*
 * export hunk buffers
 */
int export_hunk_buffer(char *buffer, char check, FILE *out) {
  // fprintf(out, "%s", hunk_additions_buffer);
  int j = 2;
  // array index start at 2
  char c;
  int int_in_buffer = get_int_from_buffer(buffer, 0);  // int_in_buffer = 15
  // fprintf(out,"this is int_in_buffer: %d, j=%d\n",int_in_buffer,j);
  // print out buffer in the style of diff file
  while (int_in_buffer != 0) {
    // fprintf(out, "\n\nj=%d\n", j);
    // fprintf(out,"int_in_buffer: %d\n", int_in_buffer);
    fprintf(out, "%c ", check);

    for (int i = 0; i < int_in_buffer; i++) {
      c = get_arr(buffer, j);
      // if (c=='\0') break;
      fprintf(out, "%c", c);
      j++;
    }
    if (j == HUNK_MAX - 2 && get_arr(buffer, j + 1) == '\0') {
      fprintf(out, "...\n");
      break;
    }
    int_in_buffer = get_int_from_buffer(buffer, j);  // int_in_buffer = 36
    j += 2;
  }
  return 0;
}
/*
 * set hunk type char
 */
char set_hunk_type_char(HUNK *hp) {
  switch (hp->type) {
    case 1:
      return 'a';
      break;
    case 2:
      return 'd';
      break;
    case 3:
      return 'c';
      break;
    default:
      return -1;
      break;
  }
}

/**
 * @brief  Print a hunk to an output stream.
 * @details  This function prints a representation of a hunk to a
 * specified output stream.  The printed representation will always
 * have an initial line that specifies the type of the hunk and
 * the line numbers in the "old" and "new" versions of the file,
 * in the same format as it would appear in a traditional diff file.
 * The printed representation may also include portions of the
 * lines to be deleted and/or inserted by this hunk, to the extent
 * that they are available.  This information is defined to be
 * available if the hunk is the current hunk, which has been completely
 * read, and a call to hunk_next() has not yet been made to advance
 * to the next hunk.  In this case, the lines to be printed will
 * be those that have been stored in the hunk_deletions_buffer
 * and hunk_additions_buffer array.  If there is no current hunk,
 * or the current hunk has not yet been completely read, then no
 * deletions or additions information will be printed.
 * If the lines stored in the hunk_deletions_buffer or
 * hunk_additions_buffer array were truncated due to there having
 * been more data than would fit in the buffer, then this function
 * will print an elipsis "..." followed by a single newline character
 * after any such truncated lines, as an indication that truncation
 * has occurred.
 *
 * @param hp  Data structure giving the header information about the
 * hunk to be printed.
 * @param out  Output stream to which the hunk should be printed.
 */

void hunk_show(HUNK *hp, FILE *out) {
  // print the hunk header
  char hunk_type_char = set_hunk_type_char(hp);
  if (hunk_type_char == -1) return;

  if (hp->old_start == hp->old_end) {
    fprintf(out, "%d", hp->old_start);
  } else {
    fprintf(out, "%d,%d", hp->old_start, hp->old_end);
  }
  fprintf(out, "%c", hunk_type_char);
  if (hp->new_start == hp->new_end) {
    fprintf(out, "%d", hp->new_start);
  } else {
    fprintf(out, "%d,%d", hp->new_start, hp->new_end);
  }
  fprintf(out, "\n");
  // print all chars in respective buffer
  if (hp->type == 1) {
    // for (int i = 0; i < HUNK_MAX; i++) {
    // fprintf(out, "(%d)%d, ", i,get_arr(hunk_additions_buffer, i));
    // } fprintf(out, "\n");
    export_hunk_buffer(hunk_additions_buffer, '>', out);

  } else if (hp->type == 2) {
    export_hunk_buffer(hunk_deletions_buffer, '<', out);
  } else if (hp->type == 3) {
    // for (int k=0;k<100;k++) fprintf(out, "%d, ",
    // get_arr(hunk_deletions_buffer,k));

    export_hunk_buffer(hunk_deletions_buffer, '<', out);
    fprintf(out, "---\n");
    export_hunk_buffer(hunk_additions_buffer, '>', out);
  }
}

int biggest_line_num;  // what is the biggest line number so far. don't be lower
int output_file_num;   // for additions, starts at line preceding addition
int input_file_num;    // first affected line
char hunk_char;        // current character read with hunk_getc
char input_char;       // current character read with fgetc

/*
 * patch function to interpret an append hunk
 */
static int patch_append_func(HUNK hunk, FILE *in, FILE *out, FILE *diff,
                             int skip_skip) {
  if (skip_skip == 0) {
    while (hunk.new_start != output_file_num) {
      debug("made it here, input_file_num: %d, output_file_num: %d",
            input_file_num, output_file_num);
      if (input_char == EOF && hunk.old_start) {
        if (!(global_options & 4))
          fprintf(stderr,
                  "Error: Symantic error in diff file, hunk %d start line is "
                  "larger than input file",
                  hunk.serial);
        return -1;
      }
      // debug("writing %c to output file", input_char);
      if (!(global_options & 2)) fputc(input_char, out);
      if (input_char == '\n') {
        input_file_num++;
        output_file_num++;
      }
      input_char = fgetc(in);
    }
  }
  while (hunk_char != EOS && hunk_char != ERR) {
    if (symantic_err) {
      if (!(global_options & 4))
        fprintf(stderr,
                "Error: Symantic error in diff file, hunk %d start line is "
                "larger than input file",
                hunk.serial);
      return -1;
    }
    if (hunk_char == ERR) {
      if (!(global_options & 4))
        fprintf(stderr, "Error: Syntax error in hunk %d", hunk.serial);
      return -1;
    }
    if (!(global_options & 2)) fputc(hunk_char, out);
    if (hunk_char == '\n') {
      output_file_num++;
    }
    hunk_char = hunk_getc(&hunk, diff);
  }
  return 0;
}
/*
 * patch function to interpret an delete hunk
 */
static int patch_delete_func(HUNK hunk, FILE *in, FILE *out, FILE *diff) {
  while (hunk.old_start != input_file_num) {
    // debug("made it here, input_file_num: %d", input_file_num);
    if (input_char == EOF) {
      // error("Failed at Delete Hunk");
      if (!(global_options & 4))
        fprintf(stderr,
                "Error: Symantic error in diff file, hunk %d start line is "
                "larger than input file",
                hunk.serial);
      return -1;
    }
    // debug("writing %c to output file", input_char);
    if (!(global_options & 2)) fputc(input_char, out);
    if (input_char == '\n') {
      input_file_num++;
      output_file_num++;
    }
    input_char = fgetc(in);
  }
  // actual delete stuff
  while (hunk_char != EOS && hunk_char != ERR) {
    if (symantic_err) {
      if (!(global_options & 4))
        fprintf(stderr,
                "Error: Symantic error in diff file, hunk %d start line is "
                "larger than input file",
                hunk.serial);
      return -1;
    }
    if (hunk_char == ERR) {
      if (!(global_options & 4))
        fprintf(stderr, "Error: Syntax error in hunk %d", hunk.serial);
      return -1;
    }
    if (hunk_char == '\n') {
      input_file_num++;
    }
    hunk_char = hunk_getc(&hunk, diff);
    input_char = fgetc(in);
  }
  return 0;
}

/**
 * @brief  Patch a file as specified by a diff.
 * @details  This function reads a diff file from an input stream
 * and uses the information in it to transform a source file, read on
 * another input stream into a target file, which is written to an
 * output stream.  The transformation is performed "on-the-fly"
 * as the input is read, without storing either it or the diff file
 * in memory, and errors are reported as soon as they are detected.
 * This mode of operation implies that in general when an error is
 * detected, some amount of output might already have been produced.
 * In case of a fatal error, processing may terminate prematurely,
 * having produced only a truncated version of the result.
 * In case the diff file is empty, then the output should be an
 * unchanged copy of the input.
 *
 * This function checks for the following kinds of errors: ill-formed
 * diff file, failure of lines being deleted from the input to match
 * the corresponding deletion lines in the diff file, failure of the
 * line numbers specified in each "hunk" of the diff to match the line
 * numbers in the old and new versions of the file, and input/output
 * errors while reading the input or writing the output.  When any
 * error is detected, a report of the error is printed to stderr.
 * The error message will consist of a single line of text that describes
 * what went wrong, possibly followed by a representation of the current
 * hunk from the diff file, if the error pertains to that hunk or its
 * application to the input file.  If the "quiet mode" program option
 * has been specified, then the printing of error messages will be
 * suppressed.  This function returns immediately after issuing an
 * error report.
 *
 * The meaning of the old and new line numbers in a diff file is slightly
 * confusing. The starting line number in the "old" file is the number
 * of the first affected line in case of a deletion or change hunk,
 * but it is the number of the line *preceding* the addition in case of
 * an addition hunk. The starting line number in the "new" file is
 * the number of the first affected line in case of an addition or change
 * hunk, but it is the number of the line *preceding* the deletion in
 * case of a deletion hunk.
 *
 * @param in  Input stream from which the file to be patched is read.
 * @param out Output stream to which the patched file is to be written.
 * @param diff  Input stream from which the diff file is to be read.
 * @return 0 in case processing completes without any errors, and -1
 * if there were errors.  If no error is reported, then it is guaranteed
 * that the output is complete and correct.  If an error is reported,
 * then the output may be incomplete or incorrect.
 */

int patch(FILE *in, FILE *out, FILE *diff) {
  // TO BE IMPLEMENTED
  // read diff file
  HUNK hunk;
  int contin = hunk_next(&hunk, diff);

  // if (global_options & 2) {  // -n:  no output. silence stdout
  // }
  // if (global_options & 4) {  // -q: quiet mode. silence stderr
  // }

  hunk_char = hunk_getc(&hunk, diff);
  input_char = fgetc(in);
  if (contin == ERR) {
    if (!(global_options & 4))
      fprintf(stderr, "Error: hunk_next threw error in hunk 0");
    return -1;
  }
  biggest_line_num = hunk.old_start;
  output_file_num = 1;  // for additions, starts at line preceding addition
  input_file_num = 1;   // first affected line
  // if (hunk.old_start>0)input_file_num++;
  while (contin != EOF) {
    if (hunk.old_start < biggest_line_num) {
      if (!(global_options & 4))
        fprintf(stderr,
                "Error: Symantic error in diff file, hunk %d start line is "
                "smaller than previous hunks",
                hunk.serial);
      return -1;
    } else
      biggest_line_num = hunk.old_start;

    if (hunk_char == EOS) hunk_char = hunk_getc(&hunk, diff);  // no eos

    warn(
        "catch up to biggest_line_num: %d. input_file_num: %d. "
        "output_file_num: %d",
        biggest_line_num, input_file_num, output_file_num);
    // while (delete_count > 0) {
    //   char input_char = fgetc(in);
    //   if (input_char == EOF) {
    //     fprintf(stderr,
    //             "Error: Symantic error in diff file, hunk %d start line is "
    //             "larger than input file",
    //             hunk.serial);
    //     return -1;
    //   }
    //   // if (input_char == '\n') {
    //   //   input_file_num++;
    //   // }
    //   delete_count--;
    // }
    // warn("%c == %c", hunk_char, input_char);
    // if they are the same character even if wrong place does not be correct
    // while (hunk.old_start != input_file_num && input_file_num !=
    // output_file_num) {
    // }

    switch (hunk.type) {
      case HUNK_APPEND_TYPE:
        if (patch_append_func(hunk, in, out, diff, 0) == -1) return -1;
        break;
      case HUNK_DELETE_TYPE:
        if (patch_delete_func(hunk, in, out, diff) == -1) return -1;
        break;
      case HUNK_CHANGE_TYPE:
        // delete
        if (patch_delete_func(hunk, in, out, diff) == -1) return -1;
        hunk_char = hunk_getc(&hunk, diff);  // no eos allowed
        if (patch_append_func(hunk, in, out, diff, 1) == -1) return -1;
        break;
      default:
        if (!(global_options & 4))
          fprintf(stderr, "Error: Unknown hunk type in hunk %d", hunk.serial);
        return -1;
    }
    debug("biggest_line_num: %d, input_file_num: %d, output_file_num: %d",
          biggest_line_num, input_file_num, output_file_num);

    contin = hunk_next(&hunk, diff);
  }

  return 0;
}
