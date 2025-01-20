#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *count_sheeps(unsigned n)
{
  size_t total_length = 0;

  for (size_t i = 1; i <= n; ++i) {
    total_length += snprintf(NULL, 0, "%zu sheep...", i);
  }

  char* result = calloc(total_length, sizeof(char));
  if (!result) return NULL;

  char buffer[total_length];

  for (size_t i = 1; i <= n; ++i) {
    snprintf(buffer, sizeof(buffer), "%zu sheep...", i);
    strcat(result, buffer);
  }

  return result;
}

int main(void)
{
  unsigned n = 4;
  char *result = count_sheeps(n);
  if (result) {
    printf("%s\n", result); 
    free(result);
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
