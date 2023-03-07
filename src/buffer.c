#include "buffer.h"

#include "debug.h"
#include "fliki.h"
#include "funcs.h"
#include "global.h"

/*
 * This is the buffer for the index of hunk deletions.
 * Stores where most recent length byte is
 */
static int deletions_index = 0;
/*
 * This is the buffer for the index of hunk additions.
 * Stores where most recent length byte is
 */
static int additions_index = 0;
/*
 * stores the number of chars in this addition section
 */
static int count_additions = 0;
/*
 * stores the number of chars in this deletion section
 */
static int count_deletions = 0;

/*
 * This function is used to set the value of an array at a given index.
 * It returns the value of the array at the given index.
 */
char set_arr(char *arr, int i, int item) { 
  // debug("setting arr{%d} to %d", i, item);
  // info("count is %d", count_additions);
  return *(arr + i) = item; 
  }

/*
 * This function is used to get the value of an array at a given index.
 * It returns the value of the array at the given index.
 */
char get_arr(char *arr, int i) { return *(arr + i); }

/*
 * This function is used to clear the hunk_deletions_buffer and
 * hunk_additions_buffer.
 */
int zero_out_buffer() {
  for (int i = 0; i < HUNK_MAX; i++) {
    set_arr(hunk_deletions_buffer, i, 0);
    set_arr(hunk_additions_buffer, i, 0);
  }
  additions_index = 0;
  deletions_index = 0;
  count_additions = 0;
  count_deletions = 0;
  return 0;
}
/*
 * converts ints to little endian 2 bytes
 */
static int convert_int_to_buffer(char *buffer, int index, int count) {
  set_arr(buffer, index, count & 0xFF);       // msb
  set_arr(buffer, index+1, (count >> 8) & 0xFF);  // lsb  
  return 0;
}
// get an integer from the buffer
int get_int_from_buffer(char *buffer, int index) {
  int count = get_arr(buffer, index) & 0xFF;
  count |= (get_arr(buffer, index+1) & 0xFF) << 8;
  return count;
}

/*
 * this function is used to add an item to the buffer
 * returns 0 on success, 1 if full and truncating, ERR on failure
 */
static int add_to_buffer(char *buffer, int index, int count, char item) {
  // implement storing an integer over two bytes little endian to additions
  // index
  // if (index + count + 2 > HUNK_MAX) return ERR;  // two is for terminating bytes
  // check last two bytes of buffer to see if they are 0, hunkmax=512
  // debug("Made it to add2buffer");


  // if (get_arr(buffer, 510) == 0 &&
  //     get_arr(buffer, 511) == 0) return 1;
  // debug("probably crashed bc initialized to 0 right");
  if (index + count + 1>HUNK_MAX) return 1;


  if (index + count + 1>=HUNK_MAX-2) {
    set_arr(buffer, HUNK_MAX-1, 0); // count is ahead 1, go back when placing item
    set_arr(buffer, HUNK_MAX-2, 0);
    // will be at 512 in following equation. -2 for end buffer, -1 for second index byte
    // if (index+count+1==HUNK_MAX) {
      // set_arr(buffer, index, count-3); 
      // error("count: %d\n", count);
      // warn("count-3: %d\n", count-3);
    // convert_int_to_buffer(buffer,index, count);
      // printf("index+1+count=%d, count-1: %d", index+1+count,count-3);
      // }
    return 1;
  };
  convert_int_to_buffer(buffer, index, count);

  // set_arr(buffer, index, count & 0xFF); // msb
  // set_arr(buffer, index+1, (count>>8) & 0xFF); // lsb
  set_arr(buffer, index + (count+1), item);
  // debug("index: %d, count: %d, item: %c (%d)", index, count, get_arr(buffer, index + (count-1)),get_arr(buffer, index + (count-1)));
  // add_terminating_bytes();
  // return 0;
  // check if we are up to the last two bytes of the buffer
  if ((index + count + 1 < HUNK_MAX-2)) {
    set_arr(buffer, index+count+2, 0); // count is ahead 1, go back when placing item
    set_arr(buffer, index+count+3, 0);
  } // we can add up to last two bytes of the buffer, however if count goes over
    // the last two bytes, we need to truncate
  return 0;
}
/*
 * This function is used to add an item to the hunk_additions_buffer.
 * returns 0 on success, 1 if full and truncating, ERR on failure
 */
int add_to_addition_buffer(char item) {
  //   buffer = hunk_additions_buffer;
  //   index=additions_index;
  //   count = ++count_additions;
  // debug("Additions buffer. Adding item: %c (%d)", item,item);
  ++count_additions;
  if (add_to_buffer(hunk_additions_buffer, additions_index, count_additions,
                    item) == ERR)
    return ERR;
  if (item == '\n' && count_additions+additions_index+3 < HUNK_MAX) {
    additions_index += count_additions+2;
    count_additions = 0;
  }
  return 0;
}
/*
 * This function is used to add an item to the hunk_deletions_buffer.
 * returns 0 on success, 1 if full and truncating, ERR on failure
 */
int add_to_deletion_buffer(char item) {
  //   buffer = hunk_deletions_buffer;
  //   index = deletions_index;
  //   count = ++count_deletions;
  // debug("Deletions buffer {index:%d} \nAdding item: %c (%d)", count_deletions,item,item);
  ++count_deletions;
  // debug("count_deletions: %d", count_deletions);
  if (add_to_buffer(hunk_deletions_buffer, deletions_index, count_deletions,
                    item) == ERR)
    return ERR;
  if (item == '\n' && count_deletions+deletions_index+3 < HUNK_MAX) {
    deletions_index += count_deletions+2;
    count_deletions = 0;
  }
  // if (deletions_index + count_deletions + 2 > HUNK_MAX) {
  // }
  // set_arr(hunk_deletions_buffer, count_deletions + deletions_index , 0);
  // set_arr(hunk_deletions_buffer, count_deletions + deletions_index + 1, 0);
  // for (int i=0;i<10;i++) debug("%c,(%d)",get_arr(hunk_deletions_buffer,i),get_arr(hunk_deletions_buffer,i));
  return 0;
}
// /*
// * THIS IS A TESTING FUNCTION. DO NOT USE IN PRODUCTION
// */ 
// int adjust_additions_index(int i) {
//   additions_index += i;
//   return 0;
// }
// /*
// * THIS IS A TESTING FUNCTION. DO NOT USE IN PRODUCTION
// */
// int adjust_deletions_index(int i) {
//   additions_index += i;
//   return 0;
// }

// /*
//  * this function will add terminating bytes to the end of the buffer
//  */
// // int add_terminating_bytes() {
// //   set_arr(hunk_additions_buffer, count_additions + additions_index + 1, 0);
// //   set_arr(hunk_additions_buffer, count_additions + additions_index + 2, 0);
// //   return 0;
// // }
