#ifndef BADLANG_FS_H_
#define BADLANG_FS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool bl_fs_exists(const char *path);
uint64_t bl_fs_file_size(FILE *fd);

#endif //  BADLANG_FS_H_
