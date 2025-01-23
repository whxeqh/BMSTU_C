#ifndef __ERRORS_H__
#define __ERRORS_H__

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_MEMORY 3
#define ERR_ARGS 4
#define ERR_FILE 5
#define ERR_NO_INVERSE 6

void print_error(const int rc);

#endif //__ERRORS_H__
