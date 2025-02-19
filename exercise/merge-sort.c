#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int inicio_array, int meio_array, int fim_array)
{
  int tamanho_esquerda = meio_array - inicio_array + 1;
  int tamanho_direita = fim_array - inicio_array;

  int sub_array_esquerda[tamanho_esquerda]; 
  int sub_array_direita[tamanho_direita];

  for (size_t i = 0; i < tamanho_esquerda; i++)
  {
    sub_array_esquerda[i] = array[inicio_array + i];
  }
  for (size_t j = 0; j < tamanho_direita; j++)
  {
    sub_array_direita[j] = array[meio_array + 1 + j];
  }
  
  int posicao_esquerda, posicao_direita, posicao_array;
  posicao_esquerda = 0;
  posicao_direita = 0;
  posicao_array = inicio_array;

  while (posicao_esquerda < tamanho_esquerda && posicao_direita < tamanho_direita)
  {
    if (sub_array_esquerda[posicao_esquerda] <= sub_array_direita[posicao_direita])
    {
      array[posicao_array] = sub_array_esquerda[posicao_esquerda];
      posicao_esquerda++;
    }
    else
    {
      array[posicao_array] = sub_array_direita[posicao_direita];
      posicao_direita++;
    }
    posicao_array++;
  }
  
  while (posicao_esquerda < tamanho_esquerda)
  {
    array[posicao_array] = sub_array_esquerda[posicao_esquerda];
    posicao_esquerda++;
    posicao_array++;
  }

  while (posicao_direita < tamanho_direita)
  {
    array[posicao_array] = sub_array_direita[posicao_direita];
    posicao_direita++;
    posicao_array++;
  }
}

void merge_sort(int array[], int inicio, int fim)
{
  if (inicio < fim)
  {
    int meio = inicio + (fim - inicio) / 2;

    merge_sort(array, inicio, meio);
    merge_sort(array, meio + 1, fim);

    merge(array, inicio, meio, fim);
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