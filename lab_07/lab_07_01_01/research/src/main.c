#include "research.h"

int main(void)
{
    int reps[] = { 10, 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };
    make_research(reps, sizeof(reps) / sizeof(reps[0]));
    print_stats(sizeof(reps) / sizeof(reps[0]));

    return 0;
}