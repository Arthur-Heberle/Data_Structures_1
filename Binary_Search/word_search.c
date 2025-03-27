#include <string.h>
#include <math.h>
#include "utils.h"

/* */
int linear_search (char **words, int n, char *key) {
  for(int i = 0; i<n; i++){
    if(strcmp(key,words[i])==0) return i;
  }
  return NOT_FOUND;	
}

/* */
int binary_search_iterative (char **words, int n, char *key) {
  int l = 0, r = n-1;
  while(l<=r){
    int m = (l+r)/2;
    if(strcmp(words[m],key) == 0) return m;
    else if(strcmp(key,words[m]) > 0) l = m+1;
    else r = m-1;
  }
  return NOT_FOUND;
}

/* */
int binary_search_recursive (char **words, int l, int r, char *key) {
  if(l<=r){
    int m = (l+r)/2;
    int compare = strcmp(key,words[m]);
    if(!compare) return m;
    else if(compare > 0) return binary_search_recursive(words, m+1, r, key);
    else return binary_search_recursive(words, l, m-1, key);
  }
  return NOT_FOUND;
}

/* */
int get_number_of_lines (FILE *f) {
  int n = 0;
  if (f == NULL) 
    return n; 
  while (!feof(f)) {
    char c;
    fscanf(f, "%c", &c);
    if (c == '\n') 
      n++;
  }
  rewind(f);
  return (n-1);
}

/* */
int main (int argc, char *argv[]) {
  if (argc < 2) { 
    printf("run: %s [word_to_search]\n", argv[0]);
    exit(1);
  }  
  clock_t start, end;
  double elapsed_time;
  char *key = argv[1];
  FILE *f = fopen("palavras.txt", "r"); 
  int n = get_number_of_lines(f);
  char **words = (char **)malloc(n * sizeof(char *));
  int i, index;
  for (i = 0; i < n; i++) 
    words[i] = (char *)malloc(256 * sizeof(char));
  i = 0;
  while (!feof(f)) {
    fscanf(f, "%s", words[i]);     
    i++;
  }

  /*Busca linear*/
  start = clock();
  index = linear_search (words, n, key);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Running time (linear): %.2f\n", elapsed_time);
  if (index >= 0) {
    printf("Key %s, found at %d\n", key, index);
  }
  else {
    printf("Element not found.\n");
  }
 
  /*Busca binária iterativa*/
  start = clock();
  index = binary_search_iterative (words, n, key);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Running time (binary): %.2f\n", elapsed_time);
  if (index >= 0) {
    printf("Key %s, found at %d\n", key, index);
  }
  else {
    printf("Element not found.\n");
  }
  
  /*Busca binária recursiva*/
  start = clock();
  index = binary_search_recursive (words, 0, n-1, key);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Running time (binary): %.2f\n", elapsed_time);
  if (index >= 0) {
    printf("Key %s, found at %d\n", key, index);
  }
  else {
    printf("Element not found.\n");
  }
 
  /*Desalocando estruturas*/ 
  for (i = 0; i < n; i++) 
    free(words[i]);
  free(words);
  fclose(f);
  return 0;
}  
