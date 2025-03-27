#include "stack.h"


void elimina_par(Stack* s){
	int val;
	Stack* aux = create(s->size);
	while(!empty(s)){
		val = pop(s);
		if(val % 2)
			push(aux,val);
	}
	while(!empty(aux)){
		push(s,pop(aux));
	}

	destroy(aux);
}


int main () {
  int tam = 6;
  Stack *s = create (tam);
  srand(time(NULL));
  int i,k;
  for (i = 0; i < tam; i++) {
    push (s, rand()%10);
  }
  print (s);
  
  elimina_par(s);
  print(s);
  destroy (s);
}
