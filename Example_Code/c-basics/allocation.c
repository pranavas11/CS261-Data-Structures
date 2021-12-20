#include <stdlib.h>
#include <stdio.h>

struct student {
  char* name;
  int id;
  float gpa;
};

int main(int argc, char const *argv[]) {

  int* n_ptr = malloc(sizeof(int));
  *n_ptr = 16;
  printf("== *n_ptr: %d\n", *n_ptr);

  float* flarray = malloc(128 * sizeof(float));
  int i;
  for (i = 0; i < 128; i++) {
    flarray[i] = i * 0.25;
  }

  struct student* s = malloc(sizeof(struct student));
  // (*s).name = "Luke Skywalker";
  s->name = malloc(64 * sizeof(char));
  s->id = 933111111;
  s->gpa = 3.9;
  // s[0].name = "Luke Skywalker";

  struct student* students = malloc(3 * sizeof(struct student));
  students[0].name = "Leia Organa";
  students[0].id = 933222222;
  students[0].gpa = 4.0;

  struct student** student_ptrs = malloc(3 * sizeof(struct student*));
  for (i = 0; i < 3; i++) {
    student_ptrs[i] = malloc(sizeof(struct student));
    student_ptrs[i]->name = malloc(64 * sizeof(char));
  }
  student_ptrs[0]->name = "Han Solo";

  void** data = malloc(4 * sizeof(void*));
  data[0] = s;

  free(n_ptr);
  free(flarray);
  free(s->name);
  free(s);

  for (i = 0; i < 3; i++) {
    free(student_ptrs[i]->name);
    free(student_ptrs[i]);
  }
  free(student_ptrs);

  return 0;
}
