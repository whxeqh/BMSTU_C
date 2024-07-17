#ifndef ERRORS_H
#define ERRORS_H

#define OK               0
#define ERR_IO           1
#define ERR_NO_WORDS     2
#define ERR_BUFF_TO_BIG  3

void print_error(const int rc);

#endif
