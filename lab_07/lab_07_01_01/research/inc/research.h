#ifndef __RESEARCH_H__
#define __RESEARCH_H__

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

#include <stdio.h>

#define ITERATIONS 30

void print_stats(const size_t reps);

void make_research(const int *reps, const size_t length);

#endif