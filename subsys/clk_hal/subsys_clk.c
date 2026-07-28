#include "subsys_clk.h"


static clk_ops_t* __g_clk_dev;

void clk_dev_register(clk_ops_t *ops)
{
    __g_clk_dev = ops;
}


clk_ops_t* clk_ops_get()
{
    return __g_clk_dev;
}

