#include <stdbool.h>
#include <stdio.h>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif

#include "badlang/fs.h"
#include "badlang/rc.h"

bool
fs_exists(const char *path) {
    return access(path, F_OK) == RC_OK;
}

unsigned long
fs_file_size(FILE *fd) {
    unsigned long size = 0;

    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    return size;
}
