#include "file.h"

void concat_path(char *path, char *name, char *newpath) {
    strcpy(newpath, path);
    strcat(newpath, "/");
    strcat(newpath, name);
}
