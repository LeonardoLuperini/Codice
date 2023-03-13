#include "file.h"

void file_to_array(char* path, double** numbers, size_t* actual_len, size_t* index) {
	FILE* f;
	char* linebuf = NULL;
	char* test = NULL;
	size_t linelen = 0;
	ssize_t resgetline;
	
	EXIT_ERROR(f = fopen(path, "r"), NULL, "Error fopen");

	if (*actual_len == 0) {
		(*numbers) = reallocarray(*numbers, (*actual_len = 100), sizeof(double));
		EXIT_ERROR((*numbers), NULL, "Error realloc");
	}

	for (*index = 0; !feof(f);) {
		CHECK_GETLINE(resgetline = getline(&linebuf, &linelen, f));
		if (resgetline == -1) break;	

		if (*index == *actual_len) {
			(*numbers) = reallocarray(*numbers, (*actual_len *= 2), sizeof(double));
			EXIT_ERROR((*numbers), NULL, "Error realloc");
		}

		(*numbers)[(*index)] = strtod(linebuf, &test);
		if ((*numbers)[(*index)] != 0 && linebuf != test) (*index)++;
	}
	if (linebuf != NULL) free(linebuf);
	fclose(f);
}

void concat_path(char* path, char* name, char* newpath) {
	strcpy(newpath, path);
	strcat(newpath, "/");
	strcat(newpath, name);
}
