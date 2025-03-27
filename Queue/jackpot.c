#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ERROR -INT_MAX

typedef struct {
  int front;
  int back;
  int size;
  int *array;
} Queue;

/*Função que verifica se a fila {q} está vazia (true) ou não {false}.*/
int empty (Queue *q) {
  return (q->front == q->back);
}

/*Função que verifica se a fila {q} está cheia (true) ou não {false}.*/
int full (Queue *q) {
  return (q->front == ((q->back + 1) % q->size));
}

/*Função que cria e inicializa uma fila de tamanho {size}.*/
Queue *create (int size) {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = 0;
  q->back = 0;
  q->size = size;
  q->array = (int *)malloc(size * sizeof(int));
  return q;
}

/*Função para enfileirar {elem} na fila {q}.*/
void enqueue (Queue *q, int elem) {
  if (full(q)) {
    printf ("error: queue overflow!\n");
    exit(1);
  }
  q->array[q->back] = elem;
  q->back = (q->back + 1) % q->size;
}

/*Função para desenfileirar o primeiro elemento da fila {q}.*/
int dequeue (Queue *q) {
  if (empty(q)) {
    printf ("error: queue underflow!\n");
    exit(1);
  }
  int e = q->array[q->front];
  q->front = (q->front + 1) % q->size;
  return e;
}

/*Função que retorna mas não remove o primeiro elemento de {q}.*/
int front (Queue *q) {
  if (!empty(q))
    return q->array[q->front];
  else
    return ERROR;
}

/*Função que imprime uma fila {q}.*/
void print (Queue *q) {
  int i;
  printf("Queue: ");
  for (i = q->front; i != q->back; i = (i+1) % q->size) {
    printf ("%d ", q->array[i]);
  }
  printf("\n");
}

/*Função que desaloca as estruturas de uma fila {q}.*/
void destroy (Queue *q) {
  free (q->array);
  free (q);
}

/*Função que retorna o número de elementos alocados no array*/
int getsize (Queue *q) {
  return q->size;
}

/*Função que retorna {true} se o elemento {e} existe em {q}*/
int search (Queue *q, int e) {
  int i;
  for (i = q->front; i != q->back; i = (i+1) % q->size)
    if (q->array[i] == e)
      return 1;
  return 0;
}

void jackpot (int n, int r){

    Queue** queues = (Queue**) malloc(n * sizeof(Queue*));
    int* ganhos = (int*) malloc(r * sizeof(int));
    int elem1, elem2;


    /*---------------------------------------------*/
    /*            Inicializa os ganhos             */
    for(int i = 0; i < r; i++){
        ganhos[i] = 1;
    }

    /*---------------------------------------------*/
    /*    Cria as queues com valores aleatorios    */
    for(int i = 0; i < n;i++){
        queues[i] = create(r+1);
        for(int j = 0; j<r; j++){
            enqueue(queues[i], rand()%10);
        }
    }

    /*---------------------------------------------*/
    /* Gira um numero aleatorio de vezes cada fila */
    for(int i = 0; i < n; i++){
        int num = rand() %10;
        for(int j = 0; j < num; j++){
            enqueue(queues[i], dequeue(queues[i]));
        }
    }

    /*---------------------------------------------*/
    /*    Verifica os ganhos e imprime na tela     */
    for(int i = 0; i < r; i++){
        elem1 = queues[0]->array[queues[0]->front];

        for(int j = 0; j < n; j++){
            elem2 = dequeue(queues[j]);
            enqueue(queues[j], elem2);

            //printf("%d %d\n", elem1, elem2);
            if(elem1 != elem2){
                ganhos[i] = 0;
            }
            printf("%d ", elem2);
        }
        printf("\n");
    }

    int ganhoTotal = 0;
    for(int i = 0; i < r; i++){
        ganhoTotal+=ganhos[i];
    }
    printf("Sua pontuacao: %d\n", ganhoTotal*100);

    int jogarNov = 0;
    printf("Quer jogar novamente? 1-SIM / 0-NAO\n");
    scanf("%d",&jogarNov);
    if(jogarNov == 1)
        jackpot(n,r);


}

int main () {
  srand(time(NULL));
  int n = 3;  /*número de carretéis*/
  int r = 10; /*sequência de números em cada carretel*/
  jackpot (n, r);
}
