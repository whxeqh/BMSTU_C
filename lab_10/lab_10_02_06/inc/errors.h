#ifndef __ERRORS_H__
#define __ERRORS_H__

#define OK 0
#define ERR_IO 1
#define ERR_MEMORY 2
#define ERR_ACT 3
#define ERR_EMPTY 4

void print_error(const int rc);

#endif //__ERRORS_H__