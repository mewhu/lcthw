#include <stdio.h>
int main() {
  char *char_ptr = "test";
  printf("sizeof char_ptr: %ld\n", sizeof(char_ptr));

  char char_array[5] = {'t', 'e', 's', 't'};
  printf("sizeof char_array : %ld\n", sizeof(char_array));

  char char_arr_not_string[4] = {'a', 'b', 'c', 'd'};
  printf("char_arr_not_string[3]: %c\n", char_arr_not_string[3]);
  printf("char_arr_not_string: %s\n", char_arr_not_string);
}
/*
valgrind would complain line#11 : Conditional jump or move depends on uninitialised value(s)
--> line#11 wants a string parsing, but valgrind may think that char_arr_not_string had not completed the initialization of a StringVariable
*/
