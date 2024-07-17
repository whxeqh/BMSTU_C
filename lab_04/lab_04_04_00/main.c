#include "io.h"
#include "calculations.h"

#define MAX_STRING_LEN (256 + 1)

int main(void)
{
    char buf[MAX_STRING_LEN];
    int rc = OK;
    bool ans;
    
    rc = input_string(buf, MAX_STRING_LEN);

    if (rc == OK)
    {   
        ans = is_ip_correct(buf);
        print_ans(ans);
    }

    return rc;    
}
