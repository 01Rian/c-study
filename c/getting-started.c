#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  double A[5];

  for (size_t i = 0; i < 5; i++)
  {
    double x;
    printf("Give a number: ");
    scanf("%le", &x);
    A[i] = x;
  }
  for (size_t i = 0; i < 5; i++)
  {
    printf("Element %zu is %g, \tits square is %g\n", i, A[i], A[i]*A[i]);
  }
  
  return EXIT_SUCCESS;
}
