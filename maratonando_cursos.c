#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct cursos {
	int quant_semanas;
	int quant_conhecimento;
} cursos;

typedef struct priority_queue_t {
	cursos *pqueue;
	size_t size;
	size_t capacity;
} priority_queue_t;


size_t priority_queue_size(priority_queue_t *pq) { return pq->size; }

bool priority_queue_empty(priority_queue_t *pq) {
	return priority_queue_size(pq) == 0;
}

static void
priority_queue_heapify_reestrutura_quando_insere(priority_queue_t *pq,
																								 size_t i) {
	size_t p;
	for (p = (i - 1) / 2; i != 0; i = p, p = (p - 1) / 2) {
		if (pq->pqueue[p].quant_conhecimento >= pq->pqueue[i].quant_conhecimento) {
			break;
		}
		cursos aux = pq->pqueue[i];
		pq->pqueue[i] = pq->pqueue[p];
		pq->pqueue[p] = aux;
	}
}

static void
priority_queue_heapify_reestrutura_quando_remove(priority_queue_t *pq,
																								 size_t i) {
	size_t l, r;
	size_t largest = i;
	while (i < pq->size) {
		i = largest;
		l = 2 * i + 1;
		r = 2 * i + 2;
		if (l < pq->size && pq->pqueue[i].quant_conhecimento < pq->pqueue[l].quant_conhecimento) {
			largest = l;
		}
		if (r < pq->size && pq->pqueue[largest].quant_conhecimento < pq->pqueue[r].quant_conhecimento) {
			largest = r;
		}
		if (largest == i) {
			break;
		}
		cursos aux = pq->pqueue[i];
		pq->pqueue[i] = pq->pqueue[largest];
		pq->pqueue[largest] = aux;
	}
}

void priority_queue_initialize(priority_queue_t **pq) {
	(*pq) = malloc(sizeof(priority_queue_t));
	(*pq)->size = 0;
	(*pq)->capacity = 4;
	(*pq)->pqueue = malloc(sizeof(cursos) * (*pq)->capacity);
}

void priority_queue_delete(priority_queue_t **pq) {
	free((*pq)->pqueue);
	free(*pq);
	(*pq) = NULL;
}

void priority_queue_insere_elemento(priority_queue_t *pq, cursos data) {
	if (pq->size == pq->capacity) {
		pq->capacity *= 2;
		pq->pqueue = realloc(pq->pqueue, sizeof(cursos) * pq->capacity);
	}
	pq->pqueue[pq->size] = data;
	priority_queue_heapify_reestrutura_quando_insere(pq, pq->size);
	pq->size++;
}

void priority_queue_remove_elemento(priority_queue_t *pq) {
	assert(!priority_queue_empty(pq));
	if (pq->size == pq->capacity / 4 && pq->capacity > 4) {
		pq->capacity /= 2;
		pq->pqueue = realloc(pq->pqueue, sizeof(cursos) * pq->capacity);
	}
	pq->size--;
	if (!priority_queue_empty(pq)) {
		pq->pqueue[0] = pq->pqueue[pq->size];
		priority_queue_heapify_reestrutura_quando_remove(pq, 0);
	}
}

cursos priority_queue_acessa_elemento_maior_prioridade(priority_queue_t *pq) {
	assert(!priority_queue_empty(pq));
	return pq->pqueue[0];
}

int main() {
	int n_curos, semanas;
	scanf("%d %d", &n_curos, &semanas);

	priority_queue_t *pq;
	priority_queue_initialize(&pq);

	cursos curso;
	for(int i = 0; i < n_curos; i++){
		scanf("%d %d", &curso.quant_semanas, &curso.quant_conhecimento);
		priority_queue_insere_elemento(pq, curso);
	}

	int semana[semanas];
	for(int i = 0;i < semanas; i++){
		semana[i] =  0;
	}
	
	int numero_semanas = 0;
	int conhecimento = 0;
	
	while(priority_queue_empty(pq) == false){
			int semanas_do_curso = priority_queue_acessa_elemento_maior_prioridade(pq).quant_semanas;
			if(semana[semanas_do_curso-1] == 0){
				semana[semanas_do_curso-1] = 1;
				conhecimento+= priority_queue_acessa_elemento_maior_prioridade(pq).quant_conhecimento;
			}
			else {
				int i = semanas_do_curso-1;
				while(semana[i] == 1 && i >= 0){
					i--;
				}
				if(i >= 0){
					semana[i] = 1;
					conhecimento+= priority_queue_acessa_elemento_maior_prioridade(pq).quant_conhecimento;
				}
			}
			priority_queue_remove_elemento(pq);
		}
	

	printf("%d\n", conhecimento);
	return 0;
}
