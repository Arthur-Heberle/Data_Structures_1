#include "list.h"

typedef struct node {
  int data;
  struct node *next;
} Node, List;
int sum (List *l){
    if(l!=NULL)
      return l->data + sum(l->next);
    return 0;
}

int size (List *l){
  if(l!=NULL)
    return 1 + size(l->next);
  return 0;
}

int in (List *l, int k){
  if(l!=NULL){
    if(l->data == k)
      return TRUE;
    return in(l->next, k);
  }
  return FALSE;
}

int position (List *l, int k){
  if(l!=NULL){
    if(l->data == k) return 0;
    else{
      int pos = position(l->next,k);
      if(pos == -1) return -1;
      return 1 + pos;
    }
  }else return -1;
}

List* merge (List *A, List *B){
  if(A == NULL && B == NULL) return NULL;
  if(A == NULL) return B;
  if(B == NULL) return A;

  if(A->data <= B->data){
    A->next = merge(A->next, B);
    return A;
  }
  B->next = merge(A, B->next);
  return B;
}

void destroy (List *l){
  if(l!=NULL){
    destroy(l->next);
    free(l);
  }
}

int max (List *l){
  if(l!=NULL){
    int m = max(l->next);
    if(l->data >= m) return l->data;
    return m;
  }
  return INT_MIN;
}

List* removek (List *l, int k){
  if(l!=NULL){
    if(l->data == k){
      List* t = l->next;
      free(l);
      return t;
    }
    l->next = removek(l->next,k);
  }
  return l;
}

List* remove_all (List *l, int k){
  if(l!=NULL){
    if(l->data == k){
      List* t = l->next;
      free(l);
      t = remove_all(t, k);
      return t;
    }
    l->next = remove_all(l->next,k);
  }
  return l;
}

List* insert_sort (List *l, int k){

  if(l!=NULL){
    if(l->data >= k){

      List* n = (List*) malloc(sizeof(List));
      n->data = k;
      n->next = l;
      return n;
    }
    l->next = insert_sort(l->next, k);
    return l;
  }
  List* n = (List*) malloc(sizeof(List));
  n->data = k;
  n->next = NULL;
  return n;
}

List* copy (List *A){
  if(A!=NULL){
    List* B = (List*) malloc(sizeof(List));
    B->data = A->data;
    B->next = copy(A->next);
    return B;
  }
  return NULL;
}

int similar (List *A, List *B){
  if(A!=NULL && B!=NULL){
    if(A->data != B->data) return FALSE;
    return similar(A->next, B->next);
  }
  if(A == NULL && B == NULL) return TRUE;
  else return FALSE;
}

List* intersection (List *A, List *B){
  if(A == NULL || B == NULL) return NULL;
  if(in(B,A->data)){
    List* n = (List*) malloc(sizeof(List));
    n->data = A->data;
    n->next = intersection(A->next, B);
    return n;
  }
  return intersection(A->next, B);
}

void print_reverse (List *l){
  if (l != NULL) {
    print_reverse(l->next);
    printf("%d ", l->data);
  }
}
