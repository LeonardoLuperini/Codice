#include<stdio.h>

#define N 4
int main(int argc, char* argv[]) {
	
	for (int i = 0; i < argc; i++) {
		int j = 0;
		while ( j < 30) {
			printf("%d : %c\n", argv[i][j], argv[i][j]);
			j++;
		}
	}

	return 0;
}

