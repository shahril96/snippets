/*  example input-output

    input :
    abc

    expected output :
    1 =>
    2 => a
    3 => b
    4 => ab
    5 => c
    6 => ac
    7 => bc
    8 => abc */

#include <stdio.h> // scanf, printf
#include <string.h> // strlen, memset
#include <math.h> // pow

typedef unsigned __int128 uint128;

/* printing 128-bit value isn't official support yet
   so here's implementation of converting 128-bit value into string

   - xdak kena mengena dngn tujuan asal program, cuma nk convert number jadi string ja */
char *str_uint128(uint128 n, char *buf, int nbuf)
{
    /* got confused about arithmetic operation with '0'? read more about ascii :) */
    if (n == 0)
        *buf = '0'; // obviously
    else for(buf += nbuf - 2; n > 0; n /= 10) // ever heard else-for? ;)
            *--buf = '0' + (n % 10);

    return buf;
}

int main()
{
    char P[125], add[125], bigint[125];
    printf("\nenter ur string here : ");
    scanf("%125s", P); // with buf overflow protection

    int len = strlen(P), i, walk;
    uint128 n = pow(2, len); // 2^N formula, to calculate number of subset for string P
    uint128 bit; // 128 bit is enough right?

    // algorithm for printing powerset start here
    for(bit = 0; bit < n; bit++)
    {
        // init all elements inside `add` & `bigint` to be zero
        // this method is fast compared manual looping and set all to zero ourself
        memset(add, 0, sizeof add);
        memset(bigint, 0, sizeof bigint);


        for(i = 0, walk = 0; i < len; i++)
        {
            /* bitwise explanation :
                - (uint128)1 =  by default, any constant number is in 32 bit size
                                to prevent further unsuitable bit size problem,
                                we convert it into 128 bits using type-casting technique

                - (uint128)1 << i = bit-shift by i value

                - ((uint128)1 << i) & bit = get bit-shift result and make "AND" operation with bit value

              got interesting with bitwise hack? read more here :) -> https://graphics.stanford.edu/~seander/bithacks.html
            */
            if(((uint128)1 << i) & bit) // bitwise hack ;)
            {
                /*  this statement will check whether bitwise result is 0 or not 0
                    if value is > 0, then statement will be correct */
                add[walk++] = P[i];
            }
        }

        printf("%s => %s\n", str_uint128(bit+1, bigint, sizeof bigint), add);
    }
}
