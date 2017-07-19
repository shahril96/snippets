
/*
 * gcc -m32 thwart_IDA.c -o thwart_IDA
 */

#include <stdio.h>

/* throws off esp analysis to thwart hexrays

   Credit: https://github.com/RPISEC/MBE

   Note: For IDA user, you can simply fix "sp-analysis error"
         by pressing Alt+k at the wrong stack relative value,
         and adjust it to the correct one
*/
#define deathrays \
    __asm__ volatile("push     %eax      \n"\
                     "xor      %eax, %eax\n"\
                     "jz       .+5       \n"\
                     ".word    0xC483    \n"\
                     ".byte    0x04      \n"\
                     "pop      %eax      \n");

int main() {
    
    printf("Hello World!\n");

    int a, b;
    scanf("Values : %d%d", &a, &b);
    printf("A+B = %d\n", a+b);

    deathrays;

    return 0;
}
