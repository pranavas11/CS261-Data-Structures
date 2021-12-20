#include <stdio.h>

void times_2(int* n) {
  *n = *n * 2;
}

int main(int argc, char const *argv[]) {
  int n = 16;
  int* n_ptr = &n;

  printf("== n: %d\n", n);
  printf("== &n: %p\n", &n);
  printf("== n_ptr: %p\n", n_ptr);
  printf("== *n_ptr: %d\n", *n_ptr);
  printf("== &n_ptr: %p\n", &n_ptr);

  *n_ptr = 32;
  printf("\n== n: %d\n", n);
  printf("== &n: %p\n", &n);
  printf("== n_ptr: %p\n", n_ptr);
  printf("== *n_ptr: %d\n", *n_ptr);
  printf("== &n_ptr: %p\n", &n_ptr);

  times_2(&n);
  printf("\n== n: %d\n", n);

  void* v_ptr = &n;
  printf("\n== v_ptr: %p\n", v_ptr);
  printf("== (int*)v_ptr: %p\n", (int*)v_ptr);
  // printf("== *v_ptr: %d\n", *v_ptr);
  printf("== *(int*)v_ptr: %d\n", *(int*)v_ptr);

  int* n_ptr2 = v_ptr;
  printf("== *n_ptr2: %d\n", *n_ptr2);

  float pi = 3.1415;
  v_ptr = &pi;
  n_ptr2 = v_ptr;
  printf("\n== v_ptr: %p\n", v_ptr);
  printf("== &pi: %p\n", &pi);
  printf("== *n_ptr2: %d\n", *n_ptr2);

  return 0;
}
