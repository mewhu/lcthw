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

  // following two declarations are not legal, we should change to use strcpy() / strdup()
  /*
    C is a very low level language. The statement:
        char str[] = another_str;
    doesn't make sense to C. It is not possible to assign an entire array, to another in C. 
    You have to copy letter by letter, either manually or using the strcpy() function. In 
    the above statement, the initializer does not know the length of the another_str array 
    variable. If you hard code the string instead of putting another_str, then it will work.

    Some other languages might allow to do such things... but you can't expect a manual car
    to switch gears automatically. You are in charge of it.
   */
  /* Another aspect :
   * when we wrote like
   *     char chars_1[] = something;
   * what we want to do is initializing an array, which needs a new memory location
   * so directly use the expression like
   *     char_ptr(address) 
   * as a rvalue, makes no sense to C.
   */
  //char chars_1[] = char_ptr;
  //char chars_2[] = *char_ptr;
  //printf("chars_1[] : %s\n", chars_1);
  //printf("chars_2[] : %s\n", chars_2);
}


/*
valgrind would complain line#11 : Conditional jump or move depends on uninitialised value(s)
--> line#11 wants to read a string, but valgrind may think that char_arr_not_string had not completed the initialization of a StringVariable
*/
