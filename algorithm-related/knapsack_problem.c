#include <stdio.h>
#include <string.h>

#define max(X,Y) ((X) > (Y)) ? (X) : (Y)

typedef struct item
{
    int value;
    int weight;
} Item;

int knapSack(Item it[], int max_weight, int n)
{
    int dp_table[n+1][max_weight+1];
    int i, w;

    for(i = 0; i <= n; i++)
        for(w = 0; w <= max_weight; w++)
            if(i == 0 || w == 0)
                dp_table[i][w] = 0;

            else if(it[i-1].weight > w)
                dp_table[i][w] = dp_table[i-1][w];

            else
                dp_table[i][w] = max(it[i-1].value + dp_table[i-1][w-it[i-1].weight], dp_table[i-1][w]);

    return dp_table[i-1][w-1];
}

int main()
{
    Item it[] =
    {
        {60, 10},
        {100, 20},
        {120, 30},
        {1000, 50}
    };

    memset(dp_mem, -1, sizeof dp_mem);

    printf("total value : %d\n", knapSack(it, 50, sizeof it / sizeof it[0]));

    return 0;
}
