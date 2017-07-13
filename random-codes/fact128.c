#include <stdio.h>

typedef unsigned __int128 uint128;

/* printing 128-bit value isn't official support yet
   so here's implementation of converting 128-bit value into string */
char *str_uint128(uint128 n)
{
    /* got confused about arithmetic operation with '0'? read more about ascii :) */
    static char buf[1000] = {0}, *buft = buf;
    int nbuf = 1000;

    if (n == 0)
        *buft = '0'; // obviously
    else for(buft += nbuf - 2; n > 0; n /= 10) // ever heard else-for? ;)
            *--buft = '0' + (n % 10);

    return buft;
}

uint128 fact(int N) // calculate factorial with O(n)
{
    uint128 n, i;
    for(n = i = 1; i <= N; i++)
        n *= i;
    return n;
}

int main()
{
    printf("%d! -> %s\n", 5, str_uint128(fact(5)));
    printf("%d! -> %s\n", 10, str_uint128(fact(10)));
    printf("%d! -> %s\n", 15, str_uint128(fact(15)));
}
