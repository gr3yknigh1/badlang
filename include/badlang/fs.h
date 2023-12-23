#ifndef BADLANG_FS_H_
#define BADLANG_FS_H_

#include <stdbool.h>
#include <stdio.h>

bool fs_exists(const char *path);
unsigned long fs_file_size(FILE *fd);

#endif //  BADLANG_FS_H_
