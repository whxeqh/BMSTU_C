#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdbool.h>
#include "errors.h"

int input_string(char *buf, const size_t buf_size);
void print_ans(const bool ans);

#endif
