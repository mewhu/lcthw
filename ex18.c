#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
  if(errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }
  exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);

int *bubble_sort(int *numbers, int count, compare_cb cmp) {
  int *target_result = malloc(count * sizeof(int));
  if(!target_result)  die("malloc error on target_result");
  memcpy(target_result, numbers, (count * sizeof(int)));

  int i, j, temp = 0;
  for(i = 0; i < count; i++) {
    for(j = 0; j < count - 1; j++) {
      if(cmp(target_result[j], target_result[j+1]) > 0) {
        temp = target_result[j];
        target_result[j] = target_result[j+1];
        target_result[j+1] = temp;
      }
    }
  }

  return target_result;
}

int small_to_large(int a, int b) {
  return (a - b);
}

int large_to_small(int a, int b) {
  return (b - a);
}

int strange_order(int a, int b) {
  if(a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

void test_sorting(int *numbers, int count, compare_cb cmp) {
  int *sorted = bubble_sort(numbers, count, cmp);
  if(!sorted) die("Failed to sort as requested.");

  int i = 0;
  for(i = 0; i < count; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
  
  free(sorted);
}

int main(int argc, char *argv[]) {
  if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

  int i = 0;
  int count = argc - 1;
  int *numbers = malloc(count* sizeof(int));

  for(i = 0; i < count; i++) {
    numbers[i] = atoi(argv[i+1]);
  }
  test_sorting(numbers, count, small_to_large);
  test_sorting(numbers, count, large_to_small);
  test_sorting(numbers, count, strange_order);

  free(numbers);
  return 0;
}
