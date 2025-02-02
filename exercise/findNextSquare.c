#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long int findNextSquare(long int sq)
{
  long int root = sqrt(sq);
  if (root * root == sq)
  {
    return (root + 1) * (root + 1);
  }
  return -1;
}

int main(void)
{
  long int sq = 121;
  long int nextSquare = findNextSquare(sq);
  printf("%ld\n", nextSquare);
  return EXIT_SUCCESS;
}