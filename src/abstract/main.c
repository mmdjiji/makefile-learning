// main.c
// Generate random number in range 0 to 9.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int r;
  srand((unsigned)time(NULL));
  r = rand() % 10;
  printf("%d\n", r);
  return 0;
}
