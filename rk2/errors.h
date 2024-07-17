#ifndef ERRORS_H
#define ERRORS_H

#define OK 0
#define ERR_IO 1
#define ERR_ARGS 2
#define ERR_FILE 3
#define ERR_UNKNOWN_ACT 4
#define ERR_FILE_HAS_TRASH 5

void print_err(const int rc);

#endif
