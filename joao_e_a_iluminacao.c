#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node_t {
  char nome[31];            /*Dado da lista*/
  struct list_node_t *next; /*ponteiro para o próximo elemento*/
} list_node_t;

typedef struct list_t {
  list_node_t *head; /*Cabeca da Lista*/
  list_node_t *tail; /*Cauda da Lista*/
  size_t size;       /*tamanho da lista*/
} list_t;

size_t list_size(list_t *l) { return l->size; }

bool list_empty(list_t *l) { return list_size(l) == 0 ? 1 : 0; }

/** Deleta o nó de uma lista **/
static void list_delete_node(list_node_t *n) {
  /** Libera o nó **/
  free(n);
}

/** Remove a cabeça da lista **/
void list_remove_head(list_t *l) {
  /** Debug apenas: aborta o programa caso a remoção da cabeça seja sobre
   * uma lista vazia **/
  assert(!list_empty(l));
  /** O nó a ser removido recebe a cabeça **/
  list_node_t *aux = l->head;
  /** Se a lista tem um elemento, após a remoção a cauda deve ser NULL **/
  if (list_size(l) == 1) {
    l->tail = NULL;
  }
  /** A cabeça passa para o próximo elemento **/
  l->head = l->head->next;
  /** Deleta-se a cabeça **/
  list_delete_node(aux);
  /** O tamanho da lista é decrementado **/
  l->size--;
}

/** Remove a cauda da lista **/
void list_remove_tail(list_t *l) {
  /** Debug apenas,aborta o programa caso a função seja chamada para uma
   * lista vazia **/
  assert(list_size(l) > 0);
  /** O nó a ser removido recebe a cauda **/
  list_node_t *to_be_removed = l->tail;
  /** Se a lista tem tamanho 1, a cauda e a cabeça apontam para NULL
   * após a remoção **/
  if (list_size(l) == 1) {
    l->head = NULL;
    l->tail = NULL;
  }
  /** Caso contrário, a lista tem mais de um elemento. Deve-se iterar sobre
   * a lista até o penúltimo elemento **/
  else {
    /** Itera-se sobre a lista a partir da cabeça até o penúltimo elemento
     **/
    list_node_t *aux = l->head;
    while (aux->next != l->tail) {
      aux = aux->next;
    }
    /** O campo next do penúltimo elemento agora aponta para NULL **/
    aux->next = NULL;
    /** O penúltimo elemento passa a ser a cauda **/
    l->tail = aux;
  }
  /** Remove-se a cauda antiga **/
  list_delete_node(to_be_removed);
  /** O tamanho da lista é decrementado **/
  l->size--;
}

/** Remove o elemento da posi¸c~ao i da lista **/
void list_remove(list_t *l, size_t i) {
  /** Debug apenas, aborta o programa se a remo¸c~ao estiver sendo feita
   * em uma lista vazia ou em uma posi¸c~ao inexistente da lista **/
  assert(!list_empty(l) && i < list_size(l));
  /** Se a lista tem tamanho 1, ou a remo¸c~ao ´e do primeiro elemento,
  equivale a eliminar a cabe¸ca
  **/
  if (list_size(l) == 1 || i == 0) {
    list_remove_head(l);
  }
  /** Se i==list_size(l)-1, a remo¸c~ao ´e na cauda **/
  else if (i == list_size(l) - 1) {
    list_remove_tail(l);
  }
  /** O n´o a ser removido encontra-se no meio da lista e a lista
 possuir mais que um elemento **/
  else {
    /** N´o a ser removido **/
    list_node_t *node;
    /** Devemos percorrer at´e o i-1-´esimo elemento a partir
     * da cabe¸ca **/
    list_node_t *aux = l->head;
    size_t k;
    /** Itera-se at´e o elemento imediatamente interior ao elemento i **/
    for (k = 0; k < i - 1; k++) {
      aux = aux->next;
    }
    /** N´o a ser removido passa a ser o i-´esimo elemento **/
    node = aux->next;
    /** O anterior ao n´o a ser removido aponta para o elemento
     * que vem ap´os o n´o a ser removido **/
    aux->next = node->next;
    /** Deleta o n´o atribuido anteriormente **/
    list_delete_node(node);
    /** Decrementa o tamanho da lista **/
    l->size--;
  }
}

static list_node_t *list_new_node(char nome[]) {
  /** aloca espaco para novo no **/
  list_node_t *new_node = malloc(sizeof(list_node_t));
  /** Constroi o novo dado atraves da funcao construtora **/
  strcpy(new_node->nome, nome);
  /** Atribui o ponteiro para o proximo como NULL **/
  new_node->next = NULL;
  /** Retorna o no alocado **/
  return new_node;
}

void list_initialize(list_t **l) {
  /** Aloca espaco para a estrutura lista **/
  (*l) = malloc(sizeof(list_t));
  /** Cabeca aponta para NULL**/
  (*l)->head = NULL;
  /** Cauda aponta para NULL**/
  (*l)->tail = NULL;
  /** Tamanho de uma lista recem inicializada e 0 **/
  (*l)->size = 0;
}

void list_append(list_t *l, char nome[]) {
  /** Cria o novo no ao chamar list_new_node **/
  list_node_t *new_node = list_new_node(nome);
  /** Se a lista esta vazia, a cabeca deve apontar para o no recem criado **/
  if (list_empty(l)) {
    l->head = new_node;
  }
  /** Caso contrario, a lista possui uma cauda e ela deve estabelecer
   * uma ligacao o elemento recem criado **/
  else {
    l->tail->next = new_node;
  }
  /** A cauda e atualizada para apontar para o elemento recem criado **/
  l->tail = new_node;
  /** O tamanho da lista e incrementado **/
  l->size++;
}

void leitura(list_t *l, int n) {
  char nome[31];
  for (int i = 0; i < n; i++) {
    scanf("%s", nome);
    list_append(l, nome);
  }
}

void imprime_lista(list_t *l) {
  for (list_node_t *aux = l->head; aux != NULL; aux = aux->next) {
    printf("%s->", aux->nome);
  }
  printf("NULL\n");
}

void saida(list_t *l, int x) {
  // imprime_lista(l);
  int indice = 0;
  while (list_size(l) > 1) {
    // printf("começando de %d\n", indice);
    if (indice == list_size(l)) {
      indice = 0;
    }
    for (int i = 0; i < x - 1; i++) {
      indice++;
      if (indice == list_size(l)) {
        indice = 0;
      }
    }
    // printf("terminando em %d\n", indice);
    list_remove(l, indice);
    // imprime_lista(l);
  }
  printf("%s\n", l->head->nome);
}

int main() {
  int n, x;
  scanf("%d %d", &n, &x);
  list_t *l;
  list_initialize(&l);
  leitura(l, n);
  saida(l, x);
  return 0;
}
