#ifndef BADLANG_LOGS_H_
#define BADLANG_LOGS_H_

#include <stdio.h>

#define LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#define LOG_DEBUG(...) fprintf(stdout, __VA_ARGS__)

#endif // BADLANG_LOGS_H_
