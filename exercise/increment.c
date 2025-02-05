#include <stdio.h>

int increment(int x)
{
  if (x == 0) {
    return 1;
  } else {
    if (x % 2 == 1) return 2 * increment(x / 2);
    else return x + 1;
  }
}

int main() {
  int x = 5;
  printf("%d", increment(x));
  return 0;
}