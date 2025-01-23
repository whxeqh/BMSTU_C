#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "errors.h"
#include "file.h"
#include "array.h"

static bool is_validate_args(const int argc, const char **argv);

int main(const int argc, const char **argv)
{
    int rc = OK;
    const char *filename_in = NULL, *filename_out = NULL;
    int *pbeg = NULL, *pend = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;

    if (is_validate_args(argc, argv) == false)
    {
        rc = ERR_ARGS;
        goto func_end;
    }

    filename_in = argv[1];
    filename_out = argv[2];

    rc = create_array_ex(&pbeg, &pend, filename_in);
    if (rc != OK)
        goto free_data;

    if (argc == 4)
    {
        int cnt_elems = filter_arr_size(pbeg, pend);
        if (cnt_elems <= 0)
        {
            rc = ERR_EMPTY_ARRAY;
            goto free_data;
        }
        
        pb_dst = malloc(cnt_elems * sizeof(int));
        if (!pb_dst)
        {
            rc = ERR_MEMORY;
            goto free_data;
        }

        rc = key(pbeg, pend, pb_dst, &pe_dst);
        if (rc != OK)
            goto free_data;

        destroy_array(&pbeg);
        pbeg = pb_dst;        
        pend = pe_dst;    
        pb_dst = NULL;
        pe_dst = NULL;
    }

    size_t len = pend - pbeg;

    mysort(pbeg, len, sizeof(*pbeg), cmp_uni_int);
    rc = print_array_int_ex(pbeg, pend, filename_out);

free_data:
    destroy_array(&pbeg);

func_end:
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
