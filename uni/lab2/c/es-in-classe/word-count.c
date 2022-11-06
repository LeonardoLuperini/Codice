#include <stdio.h>
#include <string.h>

#define N 100

char str[N];

void nuovaStringa();
void contaCaratteri();
void contaParole();
void contaRighe();

int main() {
	int opzione = -1;
	void (*f[4])(void) = {nuovaStringa, contaCaratteri, contaParole, contaRighe};
	
	while (1) {
		printf("Inerisci l'opzione che vuoi: 0- nuova stringa 1- contaCaratteri 2- contaParole 3- contaRighe\n");
		scanf("%d", &opzione);
		getchar();
		if (opzione < 4 && opzione>= 0) (*f[opzione])();
		else break;
	}

	return 0;
}

void nuovaStringa() {
	printf("Inserisci una nuova stringa:");
	fgets(str, N, stdin);
	str[strlen(str)-1] = "\0";
}

void contaCaratteri() {
	printf("caratteri:%ld\n", strlen(str));
}

void contaParole() {

	char strcp[(strlen(str)+1)];
	strcpy(strcp, str);
	char* tok = strtok(strcp, " ");
	
	int n = 0;
	if (tok != NULL) n = 1;
	while (strtok(NULL, " ") != NULL) {
		n++;
	}

	printf("parole:%d\n", n);
}

void contaRighe() {
	printf("Inserisci una nuova stringa:");
}
