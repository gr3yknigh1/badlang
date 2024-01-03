#ifndef BADLANG_FS_H_
#define BADLANG_FS_H_

#include <stdio.h>

#include "badlang/types.h"

bool fs_exists(const char *path);
unsigned long fs_file_size(FILE *fd);

#endif //  BADLANG_FS_H_
