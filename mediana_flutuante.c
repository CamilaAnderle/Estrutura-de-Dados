#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct priority_queue_t {
  int *pqueue;
  size_t size;
  size_t capacity;
} priority_queue_t;

size_t priority_queue_size_maximo(priority_queue_t *pq) { return pq->size; }

bool priority_queue_empty_maximo(priority_queue_t *pq) {
  return priority_queue_size_maximo(pq) == 0;
}

static void priority_queue_heapify_bottom_up_maximo(priority_queue_t *pq,
                                                    size_t i) {
  size_t p;
  for (p = (i - 1) / 2; i != 0; i = p, p = (p - 1) / 2) {
    if (pq->pqueue[p] >= pq->pqueue[i]) {
      break;
    }
    int aux = pq->pqueue[i];
    pq->pqueue[i] = pq->pqueue[p];
    pq->pqueue[p] = aux;
  }
}

static void priority_queue_heapify_top_down_maximo(priority_queue_t *pq,
                                                   size_t i) {
  size_t l, r;
  size_t largest = i;
  while (i < pq->size) {
    i = largest;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < pq->size && pq->pqueue[i] < pq->pqueue[l]) {
      largest = l;
    }
    if (r < pq->size && pq->pqueue[largest] < pq->pqueue[r]) {
      largest = r;
    }
    if (largest == i) {
      break;
    }
    int aux = pq->pqueue[i];
    pq->pqueue[i] = pq->pqueue[largest];
    pq->pqueue[largest] = aux;
  }
}

void priority_queue_initialize_maximo(priority_queue_t **pq) {
  (*pq) = malloc(sizeof(priority_queue_t));
  (*pq)->size = 0;
  (*pq)->capacity = 4;
  (*pq)->pqueue = malloc(sizeof(int) * (*pq)->capacity);
}

void priority_queue_delete_maximo(priority_queue_t **pq) {
  free((*pq)->pqueue);
  free(*pq);
  (*pq) = NULL;
}

void priority_queue_push_maximo(priority_queue_t *pq, int data) {
  if (pq->size == pq->capacity) {
    pq->capacity *= 2;
    pq->pqueue = realloc(pq->pqueue, sizeof(int) * pq->capacity);
  }
  pq->pqueue[pq->size] = data;
  priority_queue_heapify_bottom_up_maximo(pq, pq->size);
  pq->size++;
}

void priority_queue_pop_maximo(priority_queue_t *pq) {
  assert(!priority_queue_empty_maximo(pq));
  if (pq->size == pq->capacity / 4 && pq->capacity > 4) {
    pq->capacity /= 2;
    pq->pqueue = realloc(pq->pqueue, sizeof(int) * pq->capacity);
  }
  pq->size--;
  if (!priority_queue_empty_maximo(pq)) {
    pq->pqueue[0] = pq->pqueue[pq->size];
    priority_queue_heapify_top_down_maximo(pq, 0);
  }
}

int priority_queue_front_maximo(priority_queue_t *pq) {
  assert(!priority_queue_empty_maximo(pq));
  return pq->pqueue[0];
}

// minimo

size_t priority_queue_size_minimo(priority_queue_t *pq) { return pq->size; }
bool priority_queue_empty_minimo(priority_queue_t *pq) {
  return priority_queue_size_minimo(pq) == 0;
}
static void priority_queue_heapify_bottom_up_minimo(priority_queue_t *pq,
                                                    size_t i) {
  size_t p;
  for (p = (i - 1) / 2; i != 0; i = p, p = (p - 1) / 2) {
    if (pq->pqueue[p] < pq->pqueue[i]) {
      break;
    }
    int aux = pq->pqueue[i];
    pq->pqueue[i] = pq->pqueue[p];
    pq->pqueue[p] = aux;
  }
}

static void priority_queue_heapify_top_down_minimo(priority_queue_t *pq,
                                                   size_t i) {
  size_t l, r;
  size_t largest = i;
  while (i < pq->size) {
    i = largest;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < pq->size && pq->pqueue[i] > pq->pqueue[l]) {
      largest = l;
    }
    if (r < pq->size && pq->pqueue[largest] > pq->pqueue[r]) {
      largest = r;
    }
    if (largest == i) {
      break;
    }
    int aux = pq->pqueue[i];
    pq->pqueue[i] = pq->pqueue[largest];
    pq->pqueue[largest] = aux;
  }
}

void priority_queue_initialize_minimo(priority_queue_t **pq) {
  (*pq) = malloc(sizeof(priority_queue_t));
  (*pq)->size = 0;
  (*pq)->capacity = 4;
  (*pq)->pqueue = malloc(sizeof(int) * (*pq)->capacity);
}

void priority_queue_delete_minimo(priority_queue_t **pq) {
  free((*pq)->pqueue);
  free(*pq);
  (*pq) = NULL;
}

void priority_queue_push_minimo(priority_queue_t *pq, int data) {
  if (pq->size == pq->capacity) {
    pq->capacity *= 2;
    pq->pqueue = realloc(pq->pqueue, sizeof(int) * pq->capacity);
  }
  pq->pqueue[pq->size] = data;
  priority_queue_heapify_bottom_up_minimo(pq, pq->size);
  pq->size++;
}

void priority_queue_pop_minimo(priority_queue_t *pq) {
  assert(!priority_queue_empty_minimo(pq));
  if (pq->size == pq->capacity / 4 && pq->capacity > 4) {
    pq->capacity /= 2;
    pq->pqueue = realloc(pq->pqueue, sizeof(int) * pq->capacity);
  }
  pq->size--;
  if (!priority_queue_empty_minimo(pq)) {
    pq->pqueue[0] = pq->pqueue[pq->size];
    priority_queue_heapify_top_down_minimo(pq, 0);
  }
}

int priority_queue_front_minimo(priority_queue_t *pq) {
  assert(!priority_queue_empty_minimo(pq));
  return pq->pqueue[0];
}

int main(void) {
  int n;
  scanf("%d", &n);

  priority_queue_t *minimo;
  priority_queue_initialize_minimo(&minimo);

  priority_queue_t *maximo;
  priority_queue_initialize_maximo(&maximo);

  for (int i = 0; i < n; i++) {
    int leitura;
    scanf("%d", &leitura);

		if (priority_queue_empty_minimo(minimo) || leitura >= priority_queue_front_minimo(minimo)) {
			priority_queue_push_minimo(minimo, leitura);
		} else {
			priority_queue_push_maximo(maximo, leitura);
		}

		// Balanceia as filas
		while (priority_queue_size_minimo(minimo) > priority_queue_size_maximo(maximo)) {
			priority_queue_push_maximo(maximo, priority_queue_front_minimo(minimo));
			priority_queue_pop_minimo(minimo);
		}

		while (priority_queue_size_maximo(maximo) > priority_queue_size_minimo(minimo)) {
			priority_queue_push_minimo(minimo, priority_queue_front_maximo(maximo));
			priority_queue_pop_maximo(maximo);
		}
		
		if(i % 2 == 0){
			printf("%d\n", priority_queue_front_minimo(minimo));
		}
		else {
			printf("%d\n", priority_queue_front_maximo(maximo));
		}

	}
  return 0;
}
