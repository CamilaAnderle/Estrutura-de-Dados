#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct processo {
  char nome[31];
  int pid;
  int time;
  int tempoFinal;
} processo;

typedef struct queue_t {
  size_t front;
  size_t back;
  size_t size;
  size_t capacity;
  processo *queue;
} queue_t;

void queue_initialize(queue_t **q) {
  (*q) = malloc(sizeof(queue_t));
  (*q)->front = 0;
  (*q)->back = 3;
  (*q)->size = 0;
  (*q)->capacity = 4;
  (*q)->queue = malloc(sizeof(processo) * 4);
}

void queue_delete(queue_t **q) {
  free((*q)->queue);
  free(*q);
  *q = NULL;
}

void queue_insere_elemento(queue_t *q, processo data) {
  if (q->size == q->capacity) {
    size_t old_capacity = q->capacity;
    q->capacity *= 2;
    q->queue = realloc(q->queue, sizeof(processo) * q->capacity);
    if (q->front > q->back) {
      for (size_t i = q->front; i < old_capacity; i++) {
        q->queue[i + old_capacity] = q->queue[i];
      }
      q->front = q->front + old_capacity;
    }
  }
  q->back++;
  if (q->back == q->capacity)
    q->back = 0;
  q->queue[q->back] = data;
  q->size++;
}

void queue_remove_elemento(queue_t *q) {
  assert(q->size > 0);
  if (q->size == q->capacity / 4 && q->capacity > 4) {
    size_t new_capacity = q->capacity / 2;
    if (q->front <= q->back) {
      for (size_t i = q->front, j = 0; i <= q->back; i++, j++) {
        q->queue[j] = q->queue[i];
      }
    } else {
      size_t front_len = q->capacity - q->front;
      for (int i = q->back; i >= 0; i--) {
        q->queue[i + front_len] = q->queue[i];
      }
      for (size_t i = q->front, j = 0; i < q->capacity; i++, j++) {
        q->queue[j] = q->queue[i];
      }
    }
    q->front = 0;
    q->back = q->size - 1;
    q->capacity = new_capacity;
    q->queue = realloc(q->queue, q->capacity * sizeof(processo));
  }
  q->front++;
  q->size--;
  if (q->front == q->capacity)
    q->front = 0;
}

processo queue_front(queue_t *q) {
  assert(q->front < q->capacity);
  return q->queue[q->front];
}

size_t queue_size(queue_t *q) { return q->size; }

bool queue_vazia(queue_t *q) { return queue_size(q) == 0; }

int main(void) {
  int n, quantum;
  scanf("%d %d", &n, &quantum);

  queue_t *fila;
  queue_initialize(&fila);

  queue_t *resultado;
  queue_initialize(&resultado);

  processo processos[n];

  for (int i = 0; i < n; i++) {
    scanf("%s %d %d", processos[i].nome, &processos[i].pid, &processos[i].time);
    queue_insere_elemento(fila, processos[i]);
  }
  int tempo = 0;
  while (queue_vazia(fila) == false) {
    processo atual = queue_front(fila);
    if (atual.time > quantum) {
      atual.time -= quantum;
      // atual.tempoFinal += quantum * queue_size(fila);
      tempo += quantum;
      queue_remove_elemento(fila);
      queue_insere_elemento(fila, atual);
    } else {
      atual.tempoFinal = atual.time + tempo;
      tempo += atual.time;
      atual.time = 0;
      queue_insere_elemento(resultado, atual);
      queue_remove_elemento(fila);
    }
  }
  while (queue_vazia(resultado) == false) {
    printf("%s %d %d ms \n", queue_front(resultado).nome,
           queue_front(resultado).pid, queue_front(resultado).tempoFinal);
    queue_remove_elemento(resultado);
  }
}
