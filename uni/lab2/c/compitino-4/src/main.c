#include "file.h"
#include "statistic.h"

/* SCRIVERO' IN INGLESE PERCHE' MI TROVO MEGLIO
 * (NO, NON HO COPIATO DA INTERNET XD)
 */

#define NPRINTF(s, n)\
	for(int i = 0; i < n; i++) {\
		printf("%s", s);\
	}\
	printf("\n");

#define CHECK_NEED_REALLOCARRAY(array, maxn, n, type)\
	if (n == maxn) {\
		CHECK_ERROR((array = reallocarray(array, maxn += 2, sizeof(type))), NULL, "Error realloc");\
	}

void filetoarray(char* path, double* numbers, size_t* maxn, size_t* n);
void filehandle(char* path); 
void dirhandle(char* path);
void recbody(char* path);


int main(int argc, char* argv[]) {
	char* path;
	GET_PATHDIR(path);
	
	printf("%-10s %-10s %-10s %-20s\n", "n", "avg", "std", "file");
	NPRINTF("-", 50);	
	
	recbody(path);

	free(path);
	return 0;
}

void filetoarray(char* path, double* numbers, size_t* maxn, size_t* n) {
	FILE* f;
	char* linebuf = NULL;
	char* test = NULL;
	size_t linelen = 0;
	int res;

	CHECK_FOPEN((f = fopen(path, "r")));
	for ((*n) = 0; !feof(f);) {
		CHECK_GETLINE((res = getline(&linebuf, &linelen, f)));
		if (res == -1) break;	
		CHECK_NEED_REALLOCARRAY(numbers, (*maxn), (*n), double);
		numbers[(*n)] = strtod(linebuf, &test);
		if (numbers[(*n)] != 0 && linebuf != test) (*n)++;
	}
	free(linebuf);
	fclose(f);
}

void filehandle(char* path) {
	struct dirent* file;
	char* filepath = NULL;
	size_t maxn = 1024;
	size_t n;
	double* numbers;
	DIR* d;

	CHECK_OPEND((d = opendir(path)));
	printf("dir:%s\n", path);
	CHECK_ERROR((numbers = calloc(maxn, sizeof(double))), NULL, "Error calloc");
	while ((errno = 0, file = readdir(d)) != NULL) {
		if (IS_FILE(file)) {
			CONCAT_PATH(path, file->d_name, filepath);
			filetoarray(filepath, numbers, &maxn, &n);
			printf("%-5lu %-10lf %-10lf %-20s\n", n, avg(numbers, n), std(numbers, n), file->d_name);
		}
	}
	free(numbers);
	free(filepath);
	CHECK_CLOSED(closedir(d));
}

void dirhandle(char* path) {
	struct dirent* file;
	char* newpath = NULL;
	DIR* d;

	CHECK_OPEND((d = opendir(path)));
	while ((errno = 0, file = readdir(d)) != NULL) 
		if (NOT_THIS_DIR(file->d_name) && NOT_PREV_DIR(file->d_name) && IS_DIR(file)){
			CONCAT_PATH(path, file->d_name, newpath);
			recbody(newpath);
		}
	CHECK_CLOSED(closedir(d));
	free(newpath);
}

void recbody(char* path) {
	filehandle(path);
	dirhandle(path);
}
