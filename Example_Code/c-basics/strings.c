#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  char* string = malloc(64 * sizeof(char));
  string[0] = 'c';
  string[1] = 'a';
  string[2] = 't';
  string[3] = '\0';

  const char* name = "Luke Skywalker";
  // name[1] = 'i';

  int n = strlen(name);
  char* copy = malloc((n + 1) * sizeof(char));
  strncpy(copy, name, n + 1);

  return 0;
}
