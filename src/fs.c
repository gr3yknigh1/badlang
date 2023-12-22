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
bl_fs_is_exists(const char *p) {
    return access(p, F_OK) == RC_OK;
}

unsigned long
bl_fs_file_size(FILE *fd) {
    unsigned long size = 0;

    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    return size;
}
