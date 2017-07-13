#include <stdio.h>

void int2bin(int n, int base) {
    if(n > 0) {
        int2bin(n / base, base);
        printf("%d ", n % base);
    }
}

int main() {

    int2bin(999, 2);
    puts("");

    int2bin(3103, 10);
    puts("");

    int2bin(10000, 3);
    puts("");
}
