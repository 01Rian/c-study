#include <stdio.h>
#include <stdlib.h>

void swap_double(double a[static 2])
{
  double temp = a[0];
  a[0] = a[1];
  a[1] = temp;
}

int main(int argc, char const *argv[])
{
  double A[2] = {1.0, 2.0};
  swap_double(A);
  printf("A[0] = %g, A[1] = %g\n", A[0], A[1]);\

  return EXIT_SUCCESS;
}
