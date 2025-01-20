#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int p, int q, int r)
{
  int n1 = q - p + 1;
  int n2 = r - p;

  int L[n1]; 
  int M[n2];

  for (size_t i = 0; i < n1; i++)
  {
    L[i] = array[p + i];
  }
  for (size_t j = 0; j < n2; j++)
  {
    M[j] = array[q + 1 + j];
  }
  
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  while (i < n1 && j < n2)
  {
    if (L[i] <= M[j])
    {
      array[k] = L[i];
      i++;
    }
    else
    {
      array[k] = M[j];
      j++;
    }
    k++;
  }
  
  while (i < n1)
  {
    array[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    array[k] = M[j];
    j++;
    k++;
  }
}

void merge_sort(int array[], int l, int r)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;

    merge_sort(array, l, m);
    merge_sort(array, m + 1, r);

    merge(array, l, m, r);
  }
}

void print_array(int array[], int size)
{
  for (size_t i = 0; i < size; i++)
  {
    printf("%d ", array[i]);
  }
  printf("\n");
}

int main(void)
{
  int array[] = {12, 11, 13, 5, 6, 7};
  int size = sizeof(array) / sizeof(array[0]);

  merge_sort(array, 0, size - 1);

  printf("Sorted array: \n");
  print_array(array, size);
  return EXIT_SUCCESS;
}