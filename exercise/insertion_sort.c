#include <stdio.h>
#include <stdlib.h>

typedef int item;

void insertion_sort(item s[], int n)
{
  int i, j;
  item chave;

  for (i = 1; i < n; i++)
  {
    chave = s[i];
    j = i - 1;

    while (j >= 0 && s[j] > chave)
    {
      s[j + 1] = s[j];
      j--;
    }
    s[j + 1] = chave;
  }
}

int main()
{
  item s[] = {3, 2, 1, 4, 5};
  
  printf("Array original: ");
  for (int i = 0; i < 5; i++)
  {
    printf("%d ", s[i]);
  }
  
  insertion_sort(s, 5);
  
  printf("\nArray ordenado: ");
  for (int i = 0; i < 5; i++)
  {
    printf("%d ", s[i]);
  }
  printf("\n");
  
  return EXIT_SUCCESS;
}
