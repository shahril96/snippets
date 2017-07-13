/* References :
   http://www.geeksforgeeks.org/dynamic-programming-set-4-longest-common-subsequence/
   https://www.ics.uci.edu/~eppstein/161/960229.html */

#include <stdio.h>
#include <string.h>

#define MAX(X,Y) ((X) > (Y)) ? (X) : (Y)

char str[100];

int lcs(char *X, char *Y, int m, int n)
{
    int i, j, table[50][50];
    char *ptr = str;

    for(i = m; i >= 0; i--)
        for(j = n; j >= 0; j--)
        {
            if(X[i] == 0 || Y[j] == 0)
                table[i][j] = 0;

            else if(X[i] == Y[j])
                table[i][j] = 1 + table[i+1][j+1];

            else
                table[i][j] = MAX(table[i+1][j], table[i][j+1]);
        }

    i = j = 0;

    while(i < m && j < n)
    {
        if(X[i] == Y[j])
        {
            *ptr++ = X[i];
            i++, j++;
        }
        else if(table[i+1][j] >= table[i][j+1]) i++;
        else j++;
    }

    return table[0][0];
}


int main()
{
    char X[] = "ACCGGGTTACCGTTTAAAACCCGGGTAACCT";
    char Y[] = "CCAGGACCAGGGACCGTTTACCAGCCTTAAACCA";

    printf("lcs -> %d\nlcs itself -> %s\n", lcs(X, Y, sizeof X - 1, sizeof Y - 1), str);
}
