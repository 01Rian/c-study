#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct circular
{
  size_t start;
  size_t len;
  size_t max_len;
  double* tab;  
};

struct circular* circular_init(struct circular* c, size_t max_len)
{
    if (!c) return NULL;

    if (!max_len) {
        c->start = 0;
        c->len = 0;
        c->max_len = 0;
        c->tab = NULL;
        return c;
    }

    c->start = 0;
    c->len = 0;
    c->max_len = max_len;
    c->tab = malloc(sizeof(double[max_len]));
    
    if (!c->tab) {
        c->max_len = 0;
    }

    return c;
}

void circular_destroy(struct circular* c)
{
  if (c) {
    free(c->tab);
    circular_init(c, 0);
  }
}

static size_t circular_getpos(struct circular* c, size_t pos)
{
  pos += c->start;
  pos %= c->max_len;
  return pos;
}

double* circular_element(struct circular* c, size_t pos)
{
  if (!c || pos >= c->max_len)
    return NULL;
    
  pos = circular_getpos(c, pos);
  return &c->tab[pos];
}

struct circular* circular_resize(struct circular* c, size_t new_len)
{
  if (!c || c->len > new_len)
    return NULL;
  
  if (new_len == c->max_len)
    return c;

  size_t ostart = circular_getpos(c, 0);
  double* ntab = realloc(c->tab, sizeof(double) * new_len);
  if (!ntab)
    return NULL;

  // Reorganiza os dados apenas se necessário quando aumentar o tamanho
  if (new_len > c->max_len && ostart + c->len > c->max_len) {
    size_t ulen = c->max_len - ostart;
    size_t llen = c->len - ulen;
    
    // Escolhe o método mais eficiente de reorganização
    if (llen <= (new_len - c->max_len)) {
      memcpy(ntab + c->max_len, ntab, llen * sizeof(double));
    } else {
      size_t nstart = new_len - ulen;
      memmove(ntab + nstart, ntab + ostart, ulen * sizeof(double));
      ostart = nstart;
    }
  }

  c->tab = ntab;
  c->max_len = new_len;
  c->start = ostart;
  return c;
}

int circular_push(struct circular* c, double value) {
    if (!c || c->len >= c->max_len) return 0;
    
    size_t pos = circular_getpos(c, c->len);
    c->tab[pos] = value;
    c->len++;
    return 1;
}

int circular_pop(struct circular* c, double* value) {
    if (!c || c->len == 0) return 0;
    
    if (value) *value = c->tab[c->start];
    c->start = (c->start + 1) % c->max_len;
    c->len--;
    return 1;
}

int circular_is_full(struct circular* c) {
    return c && c->len >= c->max_len;
}

int circular_is_empty(struct circular* c) {
    return !c || c->len == 0;
}

int main() {
    // Inicializa o buffer circular com tamanho 5
    struct circular buffer;
    circular_init(&buffer, 5);

    printf("Testando o buffer circular:\n\n");

    // Testando inserção
    printf("Inserindo elementos:\n");
    double valores[] = {1.5, 2.7, 3.14, 4.2, 5.0};
    for (int i = 0; i < 5; i++) {
        if (circular_push(&buffer, valores[i])) {
            printf("Inserido: %.2f\n", valores[i]);
        }
    }

    // Verificando se está cheio
    printf("\nBuffer está cheio? %s\n", circular_is_full(&buffer) ? "Sim" : "Não");

    // Testando remoção
    printf("\nRemovendo elementos:\n");
    double valor;
    for (int i = 0; i < 3; i++) {
        if (circular_pop(&buffer, &valor)) {
            printf("Removido: %.2f\n", valor);
        }
    }

    // Verificando se está vazio
    printf("\nBuffer está vazio? %s\n", circular_is_empty(&buffer) ? "Sim" : "Não");

    // Inserindo mais elementos após remoção
    printf("\nInserindo mais elementos:\n");
    double novos_valores[] = {6.6, 7.7, 8.8};
    for (int i = 0; i < 3; i++) {
        if (circular_push(&buffer, novos_valores[i])) {
            printf("Inserido: %.2f\n", novos_valores[i]);
        }
    }

    // Limpando a memória
    circular_destroy(&buffer);
    return 0;
}