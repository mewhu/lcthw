#include "minunit.h"
#include <lcthw/darray_algos.h>
/* Zed's version ( use double pointer in parameter ) */
/*
int testcmp(char **a, char **b)
{
  debug("(char *)a : %s", (char *)a);
  debug("(char *)b : %s", (char *)b);
  debug("(char *)*a : %s", (char *)*a);
  debug("(char *)*b : %s", (char *)*b);
  return strcmp(*a, *b);
}
*/

// [Mew version] remain "const void *" format in parameter
// [explanation] The importance is that comparison function takes
//               pointers to the elements in the original array you want to compare.
//           ==> "pointer a_ptr to the ELEMENT" is denoted as : ELEMENT *a_ptr;
//           ==> if now the ELEMENT is a string(i.e. char *), then ~
//           ==> the formula "ELEMENT *a_ptr" would be translated to ~
//           ==>               "char* *a_ptr" 
//           ==>           --> "char **a_ptr"
//           ==> so you should do the proper type cast (char **) 
//               before you dereference it inside the comparison function
int testcmp(const void *a, const void *b) {
  return strcmp( *(char **)a, *(char **)b );
}

DArray *create_words()
{
  DArray *result = DArray_create(0, 5);
  char *words[] = {"asdfasfd", "werwar", "13234", "asdfasfd", "oioj"};
  int i = 0;
  for(i = 0; i < 5; i++) {
    DArray_push(result, words[i]);
  }
  return result;
}

int is_sorted(DArray *array)
{
  int i = 0;
  for(i = 0; i < DArray_count(array) - 1; i++) {
    if(strcmp(DArray_get(array, i), DArray_get(array, i+1))> 0) {
      return 0;
    }
  }
  return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name)
{
  DArray *words = create_words();
  mu_assert(!is_sorted(words), "Words should start not sorted.");
  debug("--- Testing %s sorting algorithm", name);
  int rc = func(words, (DArray_compare)testcmp);
  mu_assert(rc == 0, "sort failed");
  mu_assert(is_sorted(words), "didn't sort it");
  DArray_destroy(words);
  return NULL;
}

char *test_qsort()
{
  return run_sort_test(DArray_qsort, "qsort");
}

char * all_tests()
{
  mu_suite_start();
  mu_run_test(test_qsort);
  return NULL;
}
RUN_TESTS(all_tests);
