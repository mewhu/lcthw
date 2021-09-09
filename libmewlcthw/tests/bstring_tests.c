#include "minunit.h"
#include <string.h>
#include <lcthw/bstrlib.h>

int check_string_consistent(char *a1, char *b1, int strlen)
{
  int i = 0;
  for(i=0; i < strlen; i++) {
    check((*a1)==(*b1), "The character at index:%d is not matched! (bstr->data[%d]:cstr[%d])=(%c:%c)",i,i,i,a1[i],b1[i]);
  }
  return 1;
error:
  return 0;
}

char *test_bfromcstr()
{
  char *cstr = "Mew.Hu";
  size_t cstr_len = strlen(cstr);
  bstring bstr = bfromcstr(cstr);
  mu_assert(bstr != NULL, "bstring init allocation failed.");
  mu_assert(bstr->slen == (int)cstr_len, "bstring->data has wrong size.");
  mu_assert(check_string_consistent((char *)bstr->data, cstr, cstr_len)==1, "bstring is not equal to cstr.");
  return NULL;
}

char *all_tests() {
  mu_suite_start();
  mu_run_test(test_bfromcstr);
  return NULL;
}

RUN_TESTS(all_tests);
