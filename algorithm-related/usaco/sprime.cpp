/*
 ID: mohd_sh2
 LANG: C
 TASK: sprime
 */

#include <stdio.h>
#include <stdbool.h>

// nthpri = super-primes which in length=N
// nnth = how many super-primes there in length=N
int nthpri[9][100];
int nnth[9];

bool primetest(int num) {
    if (num < 2) return false;
    if (num <= 3) return true;
    if (num%2 == 0 || num%3 ==0) return false;
    for (int i = 5; i*i <= num; i++)
        if (num %i ==0) return false;
    return true;
}

int main() {

#ifndef STDIN
    freopen("sprime.out", "w", stdout);
    freopen("sprime.in", "r", stdin);
#endif

    int N;
    scanf("%d", &N);

    // initialize length=1
    nthpri[1][0]=2, nthpri[1][1]=3, nthpri[1][2]=5, nthpri[1][3]=7;
    nnth[1]=4;

    // generate superPrimes whose below & eq to N
    for(int i=2; i <= N; i++)
        for(int j=0; j<nnth[i-1]; j++) // loop length=1 primes
            for(int l=1; l<=9; l += 2) { // loop odd number 1-9
                int num = nthpri[i-1][j]*10 + l;
                if(primetest(num))
                    nthpri[i][nnth[i]++] = num;
            }

    // print answers
    for(int i=0; i<nnth[N]; i++)
        printf("%d\n", nthpri[N][i]);

    return 0;
}