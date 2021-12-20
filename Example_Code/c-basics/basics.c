#include <stdio.h>

struct student {
  char* name;
  int id;
  float gpa;
};

/*
 * A prototype for the function foo().
 */
void foo(int x);

int main(int argc, char** argv) {

  int i = 0;
  double pi = 3.1415;
  char a = 'a';

  struct student s;
  s.name = "Luke Skywalker";
  s.id = 933111111;
  s.gpa = 3.75;

  printf("== %s id: %d, gpa: %f\n", s.name, s.id, s.gpa);

  printf("\n\nHello world.\n\n");

  /*
   * Printing a floating point number with printf() using the %f placeholder.
   * The printed number will have 16 total characters, with 4 characters after
   * the decimal point, and it'll be zero-padded at the front.
   */
  printf("== pi is: %f, and i is: %d\n", pi, i);

  /*
   * Printing a single character with printf() with the %c placeholder.
   */
  printf("== a is: %c\n", a);

  /*
   * If statements look the same in C as they look in C++.
   */
  if (pi > 3) {
    printf("== pi is bigger than 3\n");
  } else if (pi > 2) {
    printf("== pi is bigger than 2\n");
  } else {
    printf("== pi is *NOT* bigger than 2\n");
  }

  /*
   * For loops also look the same in C as they look in C++.  Here, we print the
   * command line arguments with printf().  The index of the command line
   * argument being printed is an integer, so we use %d as its placeholder.
   * Each index will be allocated 8 characters in the printed string.  The
   * command line argument itself is a string (i.e. a char*), so we use %s as
   * its placeholder.
   */
  for (i = 0; i < argc; i++) {
    printf("== argv[%8d]: %s\n", i, argv[i]);
  }

  /*
   * Calling the function foo().
   */
  foo(2);
  foo(4);
  foo(8);

  /* // This is a C++ comment */

  return 0;
}


/*
 * Here's the definition of foo().
 */
void foo(int x) {
  printf("== foo() was passed this value: %d\n", x);
}
