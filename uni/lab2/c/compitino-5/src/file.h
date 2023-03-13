#include <stdlib.h>
#include <stdio.h>

#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

#define BUFLEN 	1024
#define MAX_NAME_LEN 384 //nome del file o linghezza totale del path?

#define IS_DIR(file) (file->d_type == DT_DIR)
#define IS_FILE(file) (file->d_type == DT_REG)
#define IS_FILE(file) (file->d_type == DT_REG)

#define NOT_THIS_DIR(name) (strcmp(name, ".") != 0)
#define NOT_PREV_DIR(name) (strcmp(name, "..") != 0)

#define EXIT_ERROR(val, errval, msg) if ((val) == (errval)) { perror((msg)); exit(EXIT_FAILURE);}

#define CHECK_GETLINE(res)\
	if ((res) == -1 && !feof(f)) {perror("Error getline"); exit(EXIT_FAILURE);}

#define CHECK_READ(res, eof, n)\
	switch (res) {\
		case -1:\
			perror("Error read");\
			exit(EXIT_FAILURE);\
			break;\
		case 0:\
			eof = true;\
			break;\
		default:\
			n += res;\
			break;\
	}

void concat_path(char* path, char* name, char* newpath);
void file_to_array(char* path, double** numbers, size_t* actual_len, size_t* index);
