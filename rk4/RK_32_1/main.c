#include "errors.h"
#include "list.h"

int main(int argc, char **argv)
{
    errors_e rc = OK;
    node_t *head = NULL;

    if(argc != 2)
    {
        print_error(ERR_ARGS);
        return ERR_ARGS;
    }

    rc = list_read_ex(argv[1], &head);

    if (rc == OK && head)
        rc = task(head);

    if (rc == OK)
        rc = list_print(head);

    list_destroy(&head);

    if (rc != OK)
        print_error(rc);

    return rc;
}
