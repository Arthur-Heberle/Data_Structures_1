#include "stack.h"

void reversed_polish_notation (char *c){

  Stack *operators = create(strlen(c));
  char *sequence;
  int front = 0;

  sequence = (char*) malloc(strlen(c) * sizeof(char));

  for(int i = 0; c[i] != '\0'; i++){
      if(c[i] >= '0' && c[i] <= '9')
          sequence[front++] = c[i];
      else if(c[i] == ')')
          sequence[front++] = pop(operators);
      else if(c[i] != ' ' && c[i] != '(')
          push(operators, c[i]);
  }
  
  printf("%s", sequence);
  destroy(operators);
}

int main () {
  char *c = "( 9 + ( ( 0 + 1 ) * ( 2 * 3 ) ) )";
  reversed_polish_notation (c);
  return 0;
}
