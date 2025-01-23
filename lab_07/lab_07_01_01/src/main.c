#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "array.h"
#include "errors.h"

static bool is_validate_args(const int argc, const char **argv);

int main(const int argc, const char **argv)
{
    int rc = OK;
    const char *filename_in = NULL, *filename_out = NULL;
    int *pbeg = NULL, *pend = NULL;

    if (is_validate_args(argc, argv) == false)
    {
        print_error(ERR_ARGS);
        return ERR_ARGS;
    }

    filename_in = argv[1];
    filename_out = argv[2];

    rc = create_array_ex(&pbeg, &pend, filename_in);

    if (rc == OK)
    {
        if (argc == 4)
        {
            int *pbeg_dst = NULL, *pend_dst = NULL;
            rc = key(pbeg, pend, &pbeg_dst, &pend_dst);
            if (rc == OK)
            {
                free_array(pbeg);
                pbeg = pbeg_dst;        
                pend = pend_dst;    
                pbeg_dst = NULL;
                pend_dst = NULL;
            }
        }

        if (rc == OK)
        {
            size_t len = pend - pbeg;
            mysort(pbeg, len, sizeof(*pbeg), cmp_uni_int);
            rc = print_array_int_ex(pbeg, pend, filename_out);
        }
        
        free_array(pbeg);
    }
    
    if (rc != OK)
        print_error(rc);

    return rc;
}

static bool is_validate_args(const int argc, const char **argv)
{
    assert(argc > 0);
    assert(argv != NULL);
    
    if (argc != 3 && argc != 4)
        return false;

    if (argc == 4 && strcmp(argv[3], "f") != 0)
        return false;
    
    return true;
}
