#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "error_handling_utils.h"

#define IS_DIR(file) (file->d_type == DT_DIR)
#define IS_FILE(file) (file->d_type == DT_REG)
#define IS_FILE(file) (file->d_type == DT_REG)

#define NOT_THIS_DIR(name) (strcmp(name, ".") != 0)
#define NOT_PREV_DIR(name) (strcmp(name, "..") != 0)

/* Concatenate path and name like path + / + name
 * and return the result in newpath.
 *
 * TODO: MANCANO I CONTROLLI 
 */
void concat_path(char* path, char* name, char* newpath);
