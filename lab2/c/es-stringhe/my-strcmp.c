#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 1000

int my_strcmp(char* s1, char* s2);

int main() {
	char s1[N], s2[N];
	int res;

	scanf("%s", s1);
	scanf("%s", s2);

	res = my_strcmp(s1, s2);
	printf("%s\n", (res)? ((res < 0)? "-1" : "+1") : "0");


	return 0;
}

int my_strcmp(char* s1, char* s2) {
	int f, s;
	int n = (strlen(s1) < strlen(s2)) ? strlen(s1) : strlen(s2);
	
	int i = 0;
	while (i < n) {
		f = (int) s1[i];
		s = (int) s2[i];
		if (!(f == s)) return f-s;
		i++;
	}
	return (strlen(s1) == strlen(s2)) ? 0 : ( (strlen(s1) < strlen(s2)) ? -1 : 1);
}
