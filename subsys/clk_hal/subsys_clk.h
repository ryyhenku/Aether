#ifndef __SUBSYS_CLK_H__
#define __SUBSYS_CLK_H__


#include <stdio.h>

typedef struct
{
    char *clk_name;
    int (*clk_init)(void);
}clk_ops_t;

void clk_dev_register(clk_ops_t *ops);
clk_ops_t* clk_ops_get();


#endif /* __SUBSYS_CLK_H__ */

