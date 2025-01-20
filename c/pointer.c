#include <stdio.h>
#include <stdlib.h>

void double_swap(double* x, double* y)
{
  double temp = *x;
  *x = *y;
  *y = temp;
}

double sum(size_t len, double const* value)
{
  double result = 0.0;
  for (size_t i = 0; i < len; ++i) {
    result += *(value + i); // The two expressions A[i] and *(A+i) are equivalent.
  }
  return result;
}
int main(int argc, char const *argv[])
{
  double x = 5.0;
  double y = 10.0;

  double_swap(&x, &y);
  printf("x = %.2f, y = %.2f\n", x, y);

  double values[] = {5.0, 1.0, 2.0, 3.0, 4.0};
  int len = sizeof(values) / sizeof(values[0]);
  printf("sum = %.2f\n", sum(len, values));

  return EXIT_SUCCESS;
}
