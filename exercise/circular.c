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
  if (c) {
    if (max_len) {
      *c = (struct circular) {
        .max_len = max_len,
        .tab = malloc(sizeof(double[max_len])),
      };

      if (!c->tab) {
        c->max_len = 0;
      }
    } else {
      *c = (struct circular) { 0 };
    }
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
  double* ret = 0;
  if (c) {
    if (pos < c->max_len) {
      pos = circular_getpos(c, pos);
      ret = &c->tab[pos];
    }
  }
  return ret;
}

struct circular* circular_resize(struct circular* c, size_t new_len)
{
  if (c) {
    size_t len = c->len;
    if (len > new_len) return 0;
    size_t old_len = c->max_len;

    if (new_len != old_len) {
      size_t ostart = circular_getpos(c, 0);
      size_t nstart = ostart;
      double* otab = c->tab;
      double* ntab;

      if (new_len > old_len) {
        ntab = realloc(c->tab, sizeof(double[new_len]));
        if (!ntab) return 0;
        if (ostart + len > old_len) {
          size_t ulen = old_len - ostart;
          size_t llen = len - ulen;
          if (llen <= (new_len - old_len)) {
            memcpy(ntab + old_len, otab, llen*sizeof(double));
          } else {
            nstart = new_len - ulen;
            memmove(ntab + nstart, ntab + ostart, ulen*sizeof(double));
          }
        }
      }
      
      *c = (struct circular) {
        .max_len = new_len,
        .start = nstart,
        .len = len,
        .tab = ntab,
      };
    }
  }
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