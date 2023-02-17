#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 1000

char* my_strcat1(char* s1, char* s2) {
	char* res = (char*) malloc( (strlen(s1)+strlen(s2)) * sizeof(char));
	strcpy(res, s1);
	strcat(res, s2);
	return res;
}

int main() {
	char s1[N], s2[N], *s3;
	
	scanf("%s %s", s1, s2);
	
	s3 = my_strcat1(s1, s2);
	printf("%s", s3);

	free(s3);
	return 0;
}


