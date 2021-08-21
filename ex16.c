#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

struct Person *create_person(char *name, int age, int height, int weight){
  struct Person *who = malloc(sizeof(struct Person));
  assert(who != NULL);

  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void destroy_person(struct Person *who) {
  assert(who != NULL);
  
  free(who->name);
  free(who);
}

void print_person(struct Person *who) {
  printf("the name : %s", who->name);
  printf("\tage : %d\n", who->age);
}

void print_person2(struct Person person) {
  printf("the name : %s", person.name);
  printf("\tage : %d\n", person.age);
}

int main(int argc, char *argv[]) {
  struct Person *joe = create_person("Joe Alex", 20, 64, 140);
  print_person(joe);
  joe->age += 20;
  print_person(joe);
  destroy_person(joe);

  struct Person mew;
  mew.name = "mew.hu";
  mew.age = 32;
  print_person2(mew);

  return 0;
}
