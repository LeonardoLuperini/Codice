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


#define CHECK_GETLINE(res)\
	if ((res) == -1 && !feof(f)) {perror("Error getline"); exit(EXIT_FAILURE);}

void concat_path(char* path, char* name, char* newpath);
