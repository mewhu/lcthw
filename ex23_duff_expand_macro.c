#include <stdio.h>
#include <stdlib.h>

#define duff(n) case n: *to++ = *src++;
#define expand7duff(n) \
    duff(n-1) \
    duff(n-2) \
    duff(n-3) \
    duff(n-4) \
    duff(n-5) \
    duff(n-6) \
    duff(n-7)

int main() {
  int *to = malloc(sizeof(int) * 10);
  int *to_orig = to;
  int int_array[10] = {1,2,3,4,5,6,7,8,9,10};
  int *src = int_array;
  for(int j = 0; j < 10; j++) {
    printf("src[%d] : %d\n", j, src[j]);
  }
  src = int_array;
  int n = 10 / 8;
  switch(10 % 8) {
    case 0: do { *to++ = *src++ ;
    expand7duff(8)
    } while ( n-- > 0 );
  }
  for(int i = 0; i < 10; i++) {
    printf("to_orig[%d] : %d\n", i, to_orig[i]);
  }
  return 0;
}
