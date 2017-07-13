/*
 ID: mohd_sh2
 LANG: C
 TASK: palsquare
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define BUF 100

/*
 * tobase_wrap & tobase is a functions that can convert
 * from one base to another, without needing a additional reverse function
 * furthermore, inc (global var) will mark the length of the number string (so no need strlen())
 */

int markend = 0, inc=0;
void tobase_wrap(int num, int base, char buf[]) {
    if (num < base) {
        buf[markend + 1] = '\0';
        buf[inc++] = num + ((num>9)?'A'-10:'0');
        return;
    }
    int n = num % base;
    markend++;
    tobase_wrap(num / base, base, buf);
    buf[inc++] = n + ((n>9)?'A'-10:'0');
}

void tobase(int num, int base, char buf[]) {
    markend=inc=0;
    tobase_wrap(num, base, buf);
}

bool is_palidrome(const char *buf) {
    char newbuf[BUF];
    strncpy(newbuf, buf, inc);
    for(int i = 0; i < inc; i++)
        if(buf[i] != newbuf[inc-i-1])
            return false;
    return true;
}

int main() {

#ifndef STDIN
    freopen("palsquare.out", "w", stdout);
    freopen("palsquare.in", "r", stdin);
#endif

    int b;
    char buf[BUF], square[BUF];

    scanf("%d", &b);
    for(int n = 1; n <= 300; n++) {
        tobase(n*n, b, square);
        if(is_palidrome(square)) {
            tobase(n, b, buf);
            printf("%s %s\n", buf, square);
        }
    }

    return 0;

}