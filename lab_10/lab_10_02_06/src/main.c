#include "errors.h"
#include "actions.h"

int main(void)
{
    action_e act = ACT_UNKNOWN;
    int rc = OK;

    rc = read_act(&act);

    switch (act)
    {
        case ACT_OUT:
            rc = act_out();
            break;
        case ACT_ADD:
            rc = act_binary_operation(act);
            break;
        case ACT_MUL:
            rc = act_binary_operation(act);
            break;
        case ACT_LIN:
            rc = act_lin();
            break;
        case ACT_UNKNOWN:
            rc = ERR_ACT;
            break;
    }

    if (rc != OK)
        print_error(rc);

    return rc;
}