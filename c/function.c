#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

size_t gcd(size_t a, size_t b)
{
  assert(a <= b);
  if (!a) return b;
  size_t rem = b % a;
  return gcd(rem, a);
}

size_t fibCacheRec(size_t n, size_t cache[n])
{
  if (!cache[n - 1]) {
    cache[n - 1] = fibCacheRec(n - 1, cache) + fibCacheRec(n - 2, cache);
  }
  return cache[n - 1];
}

size_t fibCache(size_t n)
{
  if (n + 1 <= 3) return 1;

  size_t cache[n];

  cache[0] = 1, cache[1] = 1;
  for (size_t i = 2; i < n; ++i) {
    cache[i] = 0;
  }
  return fibCacheRec(n, cache);
}

int main(void)
{
  size_t a = 26;
  size_t b = 72;
  size_t result = gcd(a, b);
  printf("The greatest common divisor of %zu and %zu is %zu\n", a, b, result);
    
  return EXIT_SUCCESS;
}
