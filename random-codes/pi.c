#include <stdio.h>
#include <math.h>

#define SIZE 100

unsigned __int128 fact(int N) // calculate factorial with O(n)
{
    static unsigned __int128 memo[SIZE] = {-1};
    if(memo[N] > -1) return memo[N];
    else return memo[N] = (N <= 1) ? 1 : fact(N-1) + fact(N-2);
}

int main()
{
    long double S = 0;

    int iter = 3; // greater iteration produce better approximation of Pi
    int k; // iteration k

    // constant value
    const long double k1 = 545140134, k2 = 13591409, k3 = -640320;
    const long double k4 = 426880, k5 = 10005;

    printf("\nPi Approximation : \n\n");

    for(k = 0; k <= iter-1; k++)
    {
        long double numerator = fact(6*k) * (k1*k + k2);
        long double denominator = fact(3*k) * pow(fact(k),3) * pow(k3, 3*k);

        S += numerator/denominator;

        long double Pi = (k4 * sqrt(k5)) / S;
        printf("k = %d : %.80Lg\n", k+1, Pi);
    }
}
