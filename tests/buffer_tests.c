#include "fliki.h"
#include "global.h"
#include "buffer.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>



Test(buffer_test_suite, fliki_buffer_file1_empty_test) {
  // 1,5d0
  // hunk 1
  // HUNK_TYPE hunk_type = HUNK_DELETE_TYPE;
  FILE *file = fopen("rsrc/file1_empty.diff", "r");
  // read hunk
  HUNK hunk;
  // 41 in two bytes little endian is 

  char buffer_model[] = {
    // < This is file1.
    // < This line does not appear in file2.
    // < This line is in common between file1 and file2.
    // < Here is another line that they have in common.
    // < This line also does not appear in file2.
    0x0f, 0x00, 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'f', 'i', 'l', 'e', '1', '.', '\n',
    0x24, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',
    0x30, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'i', 's', ' ', 'i', 'n', ' ', 'c', 'o', 'm', 'm', 'o', 'n', ' ', 'b', 'e', 't', 'w', 'e', 'e', 'n', ' ', 'f', 'i', 'l', 'e', '1', ' ', 'a', 'n', 'd', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',
    0x2f, 0x00,'H', 'e', 'r', 'e', ' ', 'i', 's', ' ', 'a', 'n', 'o', 't', 'h', 'e', 'r', ' ', 'l', 'i', 'n', 'e', ' ', 't', 'h', 'a', 't', ' ', 't', 'h', 'e', 'y', ' ', 'h', 'a', 'v', 'e', ' ', 'i', 'n', ' ', 'c', 'o', 'm', 'm', 'o', 'n', '.', '\n',
    0x29, 0x00,'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'a', 'l', 's', 'o', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.','\n',0,0
  }; // 192 chars in array
  char arr1[] = {};

  hunk_next(&hunk, file);
  // call hunk_getc before hunk_next
  char a;
  while (a!= EOS) a=hunk_getc(&hunk, file);
  // is deletion buffer equal to buffer_model?
  // printf("Expected:Returned \n");
  // for (int i=0; i<25;i++) printf("%d:%d,",buffer_model[i],hunk_deletions_buffer[i]);

  for (int i=0; i<194;i++) {
    cr_assert_eq(buffer_model[i],hunk_deletions_buffer[i], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", i,buffer_model[i],buffer_model[i],hunk_deletions_buffer[i], hunk_deletions_buffer[i]);
  }

}

Test(buffer_test_suite, fliki_buffer_empty_file1_test) {
  // 0a1,5
  // hunk 1
  FILE *file = fopen("rsrc/empty_file1.diff", "r");
  // read hunk
  HUNK hunk;
  // 41 in two bytes little endian is 

  char buffer_model[] = {
    // < This is file1.
    // < This line does not appear in file2.
    // < This line is in common between file1 and file2.
    // < Here is another line that they have in common.
    // < This line also does not appear in file2.
    0x0f, 0x00, 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'f', 'i', 'l', 'e', '1', '.', '\n',
    0x24, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',
    0x30, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'i', 's', ' ', 'i', 'n', ' ', 'c', 'o', 'm', 'm', 'o', 'n', ' ', 'b', 'e', 't', 'w', 'e', 'e', 'n', ' ', 'f', 'i', 'l', 'e', '1', ' ', 'a', 'n', 'd', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',
    0x2f, 0x00,'H', 'e', 'r', 'e', ' ', 'i', 's', ' ', 'a', 'n', 'o', 't', 'h', 'e', 'r', ' ', 'l', 'i', 'n', 'e', ' ', 't', 'h', 'a', 't', ' ', 't', 'h', 'e', 'y', ' ', 'h', 'a', 'v', 'e', ' ', 'i', 'n', ' ', 'c', 'o', 'm', 'm', 'o', 'n', '.', '\n',
    0x29, 0x00,'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'a', 'l', 's', 'o', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.','\n',0,0
  }; // 192 chars in array

  hunk_next(&hunk, file);
  // call hunk_getc before hunk_next
  char a;
  while (a!= EOS) a=hunk_getc(&hunk, file);
  // is deletion buffer equal to buffer_model?
  // for (int i=0; i<15;i++) printf("%d,",hunk_additions_buffer[i]);

  for (int i=0; i<194;i++) {
    cr_assert_eq(buffer_model[i],hunk_additions_buffer[i], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", i,buffer_model[i],buffer_model[i],hunk_additions_buffer[i], hunk_additions_buffer[i]);
  }
}

Test(buffer_test_suite, fliki_buffer_file1_file2_test) {
  // 1,2c1
  // hunk 1
  FILE *file = fopen("rsrc/file1_file2.diff", "r");
  // read hunk
  HUNK hunk;
  char buffer_model_del[] = {
    // < This is file1.
    // < This line does not appear in file2.
    // ---
    // > This is file2.
    0x0f, 0x00, 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'f', 'i', 'l', 'e', '1', '.', '\n',
    0x24, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',0,0
  }; // 41 chars in array
  char buffer_model_add[] = {
    0x0f, 0x00, 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',0,0
  }; // 15 chars in array
  hunk_next(&hunk, file);
  // call hunk_getc before hunk_next
  char a,b;
  while (a != EOS) a=hunk_getc(&hunk, file);

  while (b != EOS) b=hunk_getc(&hunk, file);
  // is deletion buffer equal to buffer_model?

  for (int i=0; i<43;i++) {
    cr_assert_eq(buffer_model_del[i],hunk_deletions_buffer[i], "Deletions Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", i, buffer_model_del[i],buffer_model_del[i],hunk_deletions_buffer[i], hunk_deletions_buffer[i]);
  }
  for (int i=0; i<18;i++) {
    cr_assert_eq(buffer_model_add[i],hunk_additions_buffer[i], "Additions Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", i, buffer_model_add[i], buffer_model_add[i], hunk_additions_buffer[i], hunk_additions_buffer[i]);
  }
  hunk_next(&hunk, file);
  for (int i=0; i<HUNK_MAX;i++) {
    cr_assert_eq(0,hunk_additions_buffer[i], "Additions Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", i, 0, 0, hunk_additions_buffer[i], hunk_additions_buffer[i]);
    cr_assert_eq(0,hunk_deletions_buffer[i], "Deletions Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", i, 0,0,hunk_deletions_buffer[i], hunk_deletions_buffer[i]);
  }

  char buffer2_model_add[] = {
    0x24, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '1', '.', '\n',0,0
  }; // 36 chars in array
  char c,d;
  while (c != EOS){ c=hunk_getc(&hunk, file);}//;printf("%d,",c);}
  // printf("\n\n");
  
  // printf("Expected:Returned \n");
  // for (int i=0; i<25;i++) printf("%d:%d, ",buffer2_model_add[i], hunk_additions_buffer[i]);
  // printf(" \n");

  for (int i=0; i<38;i++) {
    cr_assert_eq(buffer2_model_add[i],hunk_additions_buffer[i], "Additions Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", i, buffer2_model_add[i], buffer2_model_add[i], hunk_additions_buffer[i], hunk_additions_buffer[i]);
  }
  hunk_next(&hunk, file);
  char buffer2_model_del[] = {
    41, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'a', 'l', 's', 'o', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',0,0,0,0
  }; // 36 chars in array
  while (d != EOS){ d=hunk_getc(&hunk, file);}//;printf("%d,",c);}

  for (int i=0; i<45;i++) {
    cr_assert_eq(buffer2_model_del[i],hunk_deletions_buffer[i], "Deletions Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", i, buffer2_model_del[i],buffer2_model_del[i],hunk_deletions_buffer[i], hunk_deletions_buffer[i]);
  }
}

// Test(buffer_test_suite, fliki_buffer_additions_truncate_test) {
//   // 0a1,5
//   // hunk 1
//   FILE *file = fopen("rsrc/empty_file1.diff", "r");
//   // read hunk
//   HUNK hunk;
//   char buffer_model[] = {
//     // < This is file1.
//     // < This line does not appear in file2.
//     // < This line is in common between file1 and file2.
//     // < Here is another line that they have in common.
//     // < This line also does not appear in file2.
//     0x0f, 0x00, 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'f', 'i', 'l', 'e', '1', '.', '\n'
//     // 0x24, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',
//     // 0x30, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'i', 's', ' ', 'i', 'n', ' ', 'c', 'o', 'm', 'm', 'o', 'n', ' ', 'b', 'e', 't', 'w', 'e', 'e', 'n', ' ', 'f', 'i', 'l', 'e', '1', ' ', 'a', 'n', 'd', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',
//     // 0x2f, 0x00,'H', 'e', 'r', 'e', ' ', 'i', 's', ' ', 'a', 'n', 'o', 't', 'h', 'e', 'r', ' ', 'l', 'i', 'n', 'e', ' ', 't', 'h', 'a', 't', ' ', 't', 'h', 'e', 'y', ' ', 'h', 'a', 'v', 'e', ' ', 'i', 'n', ' ', 'c', 'o', 'm', 'm', 'o', 'n', '.', '\n',
//     // 0x29, 0x00,'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'a', 'l', 's', 'o', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.','\n'
//   }; // 192 chars in array

//   hunk_next(&hunk, file);
//   adjust_additions_index(500);
//   // call hunk_getc before hunk_next
//   char a;
//   // while (a!= EOS) a=hunk_getc(&hunk, file);
//   // is deletion buffer equal to buffer_model?
//   for (int i=0; i<10;i++) hunk_getc(&hunk, file);
//   cr_assert_eq(buffer_model[-1],hunk_additions_buffer[-1], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -1,buffer_model[-1],buffer_model[-1],hunk_additions_buffer[-1], hunk_additions_buffer[-1]);
//   cr_assert_eq(buffer_model[-2],hunk_additions_buffer[-2], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -2,buffer_model[-2],buffer_model[-2],hunk_additions_buffer[-2], hunk_additions_buffer[-2]);
//   hunk_getc(&hunk, file); // the buffer is now full. Should Truncate
//   cr_assert_eq(0,hunk_additions_buffer[-1], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -1,0,0,hunk_additions_buffer[-1], hunk_additions_buffer[-1]);
//   cr_assert_eq(0,hunk_additions_buffer[-2], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -2,0,0,hunk_additions_buffer[-2], hunk_additions_buffer[-2]);
// }

// Test(buffer_test_suite, fliki_buffer_deletions_truncate_test) {
//   // 1,5d0
//   // hunk 1
//   FILE *file = fopen("rsrc/file1_empty.diff", "r");
//   // read hunk
//   HUNK hunk;
//   char buffer_model[] = {
//     0x0f, 0x00, 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'f', 'i', 'l', 'e', '1', '.', '\n'
//     // 0x24, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',
//     // 0x30, 0x00, 'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'i', 's', ' ', 'i', 'n', ' ', 'c', 'o', 'm', 'm', 'o', 'n', ' ', 'b', 'e', 't', 'w', 'e', 'e', 'n', ' ', 'f', 'i', 'l', 'e', '1', ' ', 'a', 'n', 'd', ' ', 'f', 'i', 'l', 'e', '2', '.', '\n',
//     // 0x2f, 0x00,'H', 'e', 'r', 'e', ' ', 'i', 's', ' ', 'a', 'n', 'o', 't', 'h', 'e', 'r', ' ', 'l', 'i', 'n', 'e', ' ', 't', 'h', 'a', 't', ' ', 't', 'h', 'e', 'y', ' ', 'h', 'a', 'v', 'e', ' ', 'i', 'n', ' ', 'c', 'o', 'm', 'm', 'o', 'n', '.', '\n',
//     // 0x29, 0x00,'T', 'h', 'i', 's', ' ', 'l', 'i', 'n', 'e', ' ', 'a', 'l', 's', 'o', ' ', 'd', 'o', 'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', ' ', 'f', 'i', 'l', 'e', '2', '.','\n'
//   }; // 192 chars in array

//   hunk_next(&hunk, file);
//   adjust_deletions_index(500);
//   // call hunk_getc before hunk_next
//   for (int i=0; i<10;i++) hunk_getc(&hunk, file);
//   cr_assert_eq(buffer_model[-1],hunk_deletions_buffer[-1], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -1,buffer_model[-1],buffer_model[-1],hunk_deletions_buffer[-1], hunk_deletions_buffer[-1]);
//   cr_assert_eq(buffer_model[-2],hunk_deletions_buffer[-2], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -2,buffer_model[-2],buffer_model[-2],hunk_deletions_buffer[-2], hunk_deletions_buffer[-2]);
//   hunk_getc(&hunk, file); // the buffer is now full. Should Truncate
//   cr_assert_eq(0,hunk_deletions_buffer[-1], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -1,0,0,hunk_deletions_buffer[-1], hunk_deletions_buffer[-1]);
//   cr_assert_eq(0,hunk_deletions_buffer[-2], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -2,0,0,hunk_deletions_buffer[-2], hunk_deletions_buffer[-2]);
// }

Test(buffer_test_suite, fliki_buffer_additions_truncate_test2) {
  // 0a1,600
  // hunk 1
  FILE *file = fopen("rsrc/hunk_max.diff", "r");
  // read hunk
  HUNK hunk;
  char buffer_model[] = {
    'i','n','d','i' // last chars in buffer
  }; 
  hunk_next(&hunk, file);
  // call hunk_getc before hunk_next
  for (int i=0; i<510;i++) hunk_getc(&hunk, file);
  // printf("%d, %d", buffer_model[-2], buffer_model[-1]);
  // cr_assert_eq(buffer_model[-1],hunk_deletions_buffer[-1], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -1,buffer_model[-1],buffer_model[-1],hunk_deletions_buffer[-1], hunk_deletions_buffer[-1]);
  // cr_assert_eq(buffer_model[-2],hunk_deletions_buffer[-2], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -2,buffer_model[-2],buffer_model[-2],hunk_deletions_buffer[-2], hunk_deletions_buffer[-2]);
  hunk_getc(&hunk, file); // the buffer is now full. Should Truncate
  cr_assert_eq(0,hunk_deletions_buffer[-1], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -1,0,0,hunk_deletions_buffer[-1], hunk_deletions_buffer[-1]);
  cr_assert_eq(0,hunk_deletions_buffer[-2], "Buffer check failed at element %d -- Expected: %c (%d) | Got: %c (%d)", -2,0,0,hunk_deletions_buffer[-2], hunk_deletions_buffer[-2]);
}
