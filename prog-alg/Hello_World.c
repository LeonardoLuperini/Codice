#include <stdio.h>
#include <stdbool.h>


bool prova(){
    return 5 > NULL;
}

int main() {
    printf("%i",prova()); //stampa 1
    return 0;
}