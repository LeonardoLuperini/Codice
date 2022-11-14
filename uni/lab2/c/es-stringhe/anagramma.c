#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 1000

int anagrmma(unsigned char* s1, unsigned char* s2);
size_t len(unsigned char* s);

int main() {
	unsigned char s1[N], s2[N];
	
	scanf("%s", s1);
	scanf("%s", s2);

	printf("%d\n", anagrmma(s1, s2));

	return 0;
}

int anagrmma(unsigned char* s1, unsigned char* s2) {
	int mat [256] = {0};
	size_t l[2];

	l[0] = len(s1);
	l[1] = len(s2);

	//Per ogni carattere della stringa setto il corrispondete valore in mat
	for(size_t i = 0; i < l[0]; i++) mat[s1[i]]++;
	for(size_t i = 0; i < l[1]; i++) mat[s2[i]]--;
	
	//controllo che l'array abbia tutti i valori a zero
	for(size_t i = 0; i < 256; i++) if (mat[i]) return 0;

	return 1;
}

size_t len(unsigned char* s) {
	size_t l = 0;
	while(s[l]) l++;
	return l;
}

