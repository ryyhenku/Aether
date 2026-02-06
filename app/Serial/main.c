
#include "serial_debug.h"

extern void board_init();

int main()
{
    int a = 12;
    float b = 12.5;

    board_init();
    init_debug_serial("Uart12",115200,Data_Bits_8,Stop_Bits_1,None_Parity);

    printf("Hello World!\r\n");
    printf("int value:%d\r\n",a);
    printf("float value:%f\r\n",b);


    return 0;
}