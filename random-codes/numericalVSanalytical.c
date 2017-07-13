#include<stdio.h>
#include<math.h>

/*
 * letak dua functions nie kat atas
 * supaya main boleh "nampak"
 */

double integral_F(double A, double B, double C, double x) {

    // aku pkai on9 calculator ja calculate integration result ni hahahahaha
    // (x^3.a)/3 + (x^2.b)/2 + cx + C
    return (pow(x,3)*A)/3 + (pow(x,2)*B)/2 + C*x;
}

double numerical_F(double A, double B, double C, double a, double b, int n)
{

    // cara lama, add block by block
    // makin tinggi nilai N (pecahan block antara a & b), makin tepat approximation kita dpt
    // nama teknik = riemann sum 

    double block = (b-a)/n;
    double sum = 0;

    for(double x = a; x <= b; x += block) {

        // small block area = current height * size of partitioned block
        double current_area = (A*pow(x,2) + B*x + C) * block;

        sum = sum + current_area;
    }
    
    return sum;
}

int main(void)
{
    double A, B, C, a, b;
    double result1, result2;

    printf("A, B, C, a, b : ");
    scanf("%lf %lf %lf %lf %lf", &A, &B, &C, &a, &b);

    result1 = integral_F(A, B, C, b) - integral_F(A, B, C, a);
    result2 = numerical_F(A, B, C, a, b, 1000000);

    printf("(1) Analytic result (integration) : %lf\n", result1);
    printf("(2) Numerical result (riemann approx sum) : %lf\n", result2);

    return 0;
}
