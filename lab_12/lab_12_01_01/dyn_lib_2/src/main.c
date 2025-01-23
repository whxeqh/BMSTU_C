#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>
#include "consts.h"

// Загружаю функцию
#define FUNC_LOAD(func_ptr, hlib, func_name) \
do { \
    func_ptr = dlsym(hlib, func_name); \
    if (!func_ptr) \
    { \
        return ERR_LOAD_FUNCTION; \
    } \
} while (0)

typedef int (*cmp_uni_int_dl)(const void *left, const void *right);

typedef struct lib_funcs
{
    cmp_uni_int_dl cmp_uni_int_dl;
    void (*mysort_dl)(void *pbeg, const size_t length, const size_t el_size, cmp_uni_int_dl uni_cmp);
    int (*filter_arr_size_dl)(const int *pb_src, const int *pe_src);
    int (*key_dl)(const int *pb_src, const int *pe_src, int *pb_dst, int **pe_dst);
    int (*print_array_int_ex_dl)(const int *pbeg, const int *pend, const char *file_name);
    int (*create_array_ex_dl)(int **pbeg, int **pend, const char *file_name);
    void (*destroy_array_dl)(int **arr);
    int (*print_error_dl)(const int rc);
} lib_funcs_t;

static int lib_load_funcs(void *hlib, lib_funcs_t *funcs);

static bool is_validate_args(const int argc, const char **argv);

int main(const int argc, const char **argv)
{
    int rc = OK;
    const char *filename_in = NULL, *filename_out = NULL;
    int *pbeg = NULL, *pend = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;

    void *hlib;
    lib_funcs_t funcs = { NULL };

    // Загружаю библиотеку
    hlib = dlopen("libs/libmydynlib.so", RTLD_NOW);
    if (!hlib)
    {
        rc = ERR_LOAD_LIBRARY;
        goto func_end;
    }

    rc = lib_load_funcs(hlib, &funcs);
    if (rc != OK)
        goto func_end;

    if (is_validate_args(argc, argv) == false)
    {
        rc = ERR_ARGS;
        goto func_end;
    }

    filename_in = argv[1];
    filename_out = argv[2];

    rc = funcs.create_array_ex_dl(&pbeg, &pend, filename_in);
    if (rc != OK)
        goto free_data;

    if (argc == 4)
    {
        int cnt_elems = funcs.filter_arr_size_dl(pbeg, pend);
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

        rc = funcs.key_dl(pbeg, pend, pb_dst, &pe_dst);
        if (rc != OK)
            goto free_data;

        funcs.destroy_array_dl(&pbeg);
        pbeg = pb_dst;
        pend = pe_dst;
        pb_dst = NULL;
        pe_dst = NULL;
    }

    size_t len = pend - pbeg;

    funcs.mysort_dl(pbeg, len, sizeof(*pbeg), funcs.cmp_uni_int_dl);
    rc = funcs.print_array_int_ex_dl(pbeg, pend, filename_out);

free_data:
    funcs.destroy_array_dl(&pbeg);

func_end:
    if (rc != OK)
        funcs.print_error_dl(rc);

    dlclose(hlib);
    return rc;
}

static int lib_load_funcs(void *hlib, lib_funcs_t *funcs)
{
    FUNC_LOAD(funcs->cmp_uni_int_dl, hlib, "cmp_uni_int");
    FUNC_LOAD(funcs->mysort_dl, hlib, "mysort");
    FUNC_LOAD(funcs->filter_arr_size_dl, hlib, "filter_arr_size");
    FUNC_LOAD(funcs->key_dl, hlib, "key");
    FUNC_LOAD(funcs->print_array_int_ex_dl, hlib, "print_array_int_ex");
    FUNC_LOAD(funcs->create_array_ex_dl, hlib, "create_array_ex");
    FUNC_LOAD(funcs->destroy_array_dl, hlib, "destroy_array");
    FUNC_LOAD(funcs->print_error_dl, hlib, "print_error");

    return OK;
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
