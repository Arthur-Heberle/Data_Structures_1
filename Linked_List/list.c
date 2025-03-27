#include "list.h"

/* */
List* insert_back (List *l, int k) {
  if (l == NULL) {
    l = (Node*)malloc(sizeof(Node));
    l->data = k;
    l->next = NULL;
  }
  else {
    l->next = insert_back (l->next, k);
  }
  return l;
}

/* */
List* removek (List *l, int k) {
  
  if(l->data == k) return l->next;
  
  List* t;
  for(t = l; t->next->data != k && t->next != NULL ; t = t->next);
  if(t == NULL) return l;
  List* tmp = t->next;
  t->next = t->next->next;
  free(tmp);
  return l;
}

/* */
void print (List* l) {
  if (l != NULL) {
    printf("%d ", l->data);
    print (l->next);      
  }
}

/* */
void destroy (List *l) {
  /*Terminar*/	
}

