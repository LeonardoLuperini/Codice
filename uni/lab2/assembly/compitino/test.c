#include<stdio.h> 
#include<stdlib.h> 

extern int myatoi(char *); 
extern int map(char ** v, int); 

int main(int argc, char **argv)  { 

  char **v = &argv[1]; 
  int  *x = malloc((argc-1)* sizeof(int)); 
  int i, res = 0; 

  for(i=0; i<argc-1; i++) 
    res += atoi(v[i])/4; // questa è l’atoi stdlib usata per verifica 

  printf("C   = %d\nASM = %d\n", res, map(v, argc-1)); 
  return 0; 
}
