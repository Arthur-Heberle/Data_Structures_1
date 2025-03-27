/********************
 *     List.h
 ********************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ERROR -INT_MAX

/*Structure*/
typedef struct node {
  int data;
  struct node *next;
  struct node *prev;
} List;

/*Interface:*/
List* create ();
List* insert_front (List *l, int elem);
List* insert_back (List *l, int elem);
void print (List *l);
void destroy (List *l);
List* search (List *l, int k);

/********************
 *     List.c
 ********************/
List* create () {
  return NULL;
}

List* insert_front (List *l, int elem) {
  List *node = (List *)malloc(sizeof(List));
  node->data = elem;
  node->next = l;
  node->prev = NULL;
  if (l != NULL)
    l->prev = node;
  return node;
}

List* search (List *l, int elem) {
  if (l != NULL) {
    List *t = l;
    while (t != NULL) {
      if (t->data == elem)
        return t;
      t = t->next;
    }
  }
  return NULL;
}

void print (List *l) {
  List *t, *last;
  printf ("List (front-to-back): {");
  for (t = l; t != NULL; t = t->next) {
    if (t->next != NULL)
       printf ("%d, ", t->data);
    else
       printf ("%d", t->data);
    last = t;
  }
  printf("}\n");
  printf ("List (back-to-front): {");
  for (t = last; t != NULL; t = t->prev) {
    if (t->prev != NULL)
       printf ("%d, ", t->data);
    else
       printf ("%d", t->data);
  }
  printf("}\n");
}

void destroy (List *l) {
  if (l != NULL) {
    List *t = l->next;
    free (l);
    l = t;
  }
}

/*---------------------------------*/
/**
                Funcoes

/*---------------------------------*/

List* insert_back (List *l, int elem) {
  List* node = (List*) malloc(sizeof(List));
  node->data = elem;
  node->prev = NULL;
  node->next = NULL;
  if(l == NULL) return node;
  List* t;
  for(t = l; t->next!=NULL; t= t->next);
  node->prev = t;
  t->next = node;
  return l;
}

int is_circular (List *l){
    List* t = l;
    int val = l->data;
    for(t=l->next; t!=l; t = t->next)
        if(t==NULL) return 0;
    for(t=l->prev; t!=l; t = t->prev)
        if(t==NULL) return 0;
    return 1;
}

List* replicate (List *l, int k) {

    List* t = l;

    while(t!=NULL){

        for(int i = 0; i < k-1; i++){
            List* node = (List*) malloc(sizeof(List));
            node->data = t->data;
            node->next = t->next;
            node->prev = t;
            if(t->next!=NULL) t->next->prev = node;
            t->next = node;
            t = t->next;
        }
        t = t->next;
    }
    return l;
}

void crivo (int n) {
  List *l = create ();
  for (int i = 2; i <= n; i++)
    l = insert_back(l, i);
  List* start = l;

  for(l; l->data*l->data < n; l = l->next){
    for(List* t = l->next; t != NULL; t = t->next){
        if(!(t->data%l->data)) {
            t->prev->next = t->next;
            if(t->next!=NULL)
              t->next->prev = t->prev;
            List* tmp = t;
            t = t->prev;
            free(tmp);
        }
    }
  }
  print (start);
  destroy (start);
}


