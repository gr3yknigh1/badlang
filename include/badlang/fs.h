#ifndef BADLANG_FS_H_
#define BADLANG_FS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool fs_exists(const char *path);
uint64_t fs_file_size(FILE *fd);

#endif //  BADLANG_FS_H_
