#include <stdio.h>
int main() {
  char *char_ptr = "test";
  printf("sizeof char_ptr: %ld\n", sizeof(char_ptr));

  char char_array[5] = {'t', 'e', 's', 't'};
  printf("sizeof char_array : %ld\n", sizeof(char_array));

  char char_arr_not_string[4] = {'a', 'b', 'c', 'd'};
  printf("char_arr_not_string[3]: %c\n", char_arr_not_string[3]);
  printf("char_arr_not_string: %s\n", char_arr_not_string);

  int numbers[4] = {0};
  char char_arr2[4] = {'a', 'b', 'c'};
  printf("numbers : %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);
  printf("char_arr2 : %c %c %c %c\n", char_arr2[0], char_arr2[1], char_arr2[2], char_arr2[3]);

  numbers[3] = 'Z';
  printf("numbers : %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);

  char chars8[8] = {'\0'};
  chars8[2] = 2;
  printf("is chars8 able to be looked as an int? : %d\n", *(int *)chars8);
}
/*
valgrind would complain line#11 : Conditional jump or move depends on uninitialised value(s)
--> line#11 wants a string parsing, but valgrind may think that char_arr_not_string had not completed the initialization of a StringVariable
*/
