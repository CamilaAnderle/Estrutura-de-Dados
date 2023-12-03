#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// vetor dinamico
typedef struct {
  int *v;            // vetor dinâmico
  size_t capacidade; // capacidade do vetor dinãmico
  size_t size;       // tamanho do vetor dinâmico
} vetor_dinamico_t;

void inicializa_vetor_dinamico(vetor_dinamico_t **arr) {
  (*arr) = malloc(sizeof(vetor_dinamico_t));
  (*arr)->capacidade = 4;
  (*arr)->size = 0;
  (*arr)->v = malloc(sizeof(int) * 4);
}

void dobra_capacidade_vetor_dinamico(vetor_dinamico_t *arr) {
  arr->capacidade *= 2;
  arr->v = realloc(arr->v, sizeof(int) * arr->capacidade);
}

void reduz_capacidade_vetor_dinamico(vetor_dinamico_t *arr) {
  arr->capacidade /= 2;
  arr->v = realloc(arr->v, sizeof(int) * arr->capacidade);
}

void insere_elemento_final_vetor_dinamico(vetor_dinamico_t *arr, int x) {
  if (arr->size == arr->capacidade) {
    dobra_capacidade_vetor_dinamico(arr);
  }
  arr->v[arr->size] = x;
  arr->size++;
}

void remove_elemento_final_vetor_dinamico(vetor_dinamico_t *arr) {
  if (arr->size == arr->capacidade / 4 && arr->capacidade > 4)
    reduz_capacidade_vetor_dinamico(arr);

  arr->size--;
}

void deletar_vetor_dinamico(vetor_dinamico_t **arr) {
  free((*arr)->v);
  free(*arr);
  *arr = NULL;
}

int final_vetor_dinamico(vetor_dinamico_t *arr) {
  return arr->v[arr->size - 1];
}

int inicio_vetor_dinamico(vetor_dinamico_t *arr) { return arr->v[0]; }
size_t tamanho_vetor_dinamico(vetor_dinamico_t *arr) { return arr->size; }

size_t capacidade_vetor_dinamico(vetor_dinamico_t *arr) {
  return arr->capacidade;
}

// pilha
typedef struct pilha_t {
  vetor_dinamico_t *vetor_pilha;
} pilha_t;

void inicializa_pilha(pilha_t **pilha) {
  *pilha = malloc(sizeof(pilha_t));
  inicializa_vetor_dinamico(&(*pilha)->vetor_pilha);
}

void deleta_pilha(pilha_t **pilha) {
  deletar_vetor_dinamico(&(*pilha)->vetor_pilha);
  free(*pilha);
  *pilha = NULL;
}

void insere_elemento_pilha(pilha_t *pilha, int data) {
  insere_elemento_final_vetor_dinamico(pilha->vetor_pilha, data);
}

int final_pilha(pilha_t *pilha) {
  return final_vetor_dinamico(pilha->vetor_pilha);
}

void remove_elemento_pilha(pilha_t *pilha) {
  remove_elemento_final_vetor_dinamico(pilha->vetor_pilha);
}

size_t tamanho_pilha(pilha_t *pilha) {
  return tamanho_vetor_dinamico(pilha->vetor_pilha);
}

bool testa_pilha_vazia(pilha_t *pilha) { return tamanho_pilha(pilha) == 0; }

typedef struct vetor {
  int x;
  int posicao;
} vetor;

int main(void) {
  int n;
  scanf("%d", &n);

	vetor elementos[n];
	
  pilha_t *pilha;
  inicializa_pilha(&pilha);

	pilha_t *posicoes;
	inicializa_pilha(&posicoes);

  for (int i = 0; i < n; i++) {
    scanf("%d", &elementos[i].x);
    elementos[i].posicao = i + 1;
  }

  for (int i = 0; i < n; i++) {
		if (testa_pilha_vazia(pilha)) {
			printf("0 ");
			insere_elemento_pilha(pilha, elementos[i].x);
			insere_elemento_pilha(posicoes, elementos[i].posicao);
		} else if(final_pilha(pilha) >= elementos[i].x) {
			while(tamanho_pilha(pilha) != 0 && final_pilha(pilha) >= elementos[i].x){
				remove_elemento_pilha(pilha);
				remove_elemento_pilha(posicoes);
			}
			if(testa_pilha_vazia(pilha)) printf("0 ");
			else {
				printf("%d ", final_pilha(posicoes));
			}
			insere_elemento_pilha(posicoes, elementos[i].posicao);
			insere_elemento_pilha(pilha, elementos[i].x);
		} else if(final_pilha(pilha) < elementos[i].x){
			printf("%d ", final_pilha(posicoes));
			insere_elemento_pilha(pilha, elementos[i].x);
			insere_elemento_pilha(posicoes, elementos[i].posicao);
		}
	}
  return 0;
}
