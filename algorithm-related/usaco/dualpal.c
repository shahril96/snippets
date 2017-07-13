/*
 ID: mohd_sh2
 LANG: C
 TASK: dualpal
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

bool is_double_palidrome(int n) {

    int c=0;
    char buf[BUF];

    for(int b = 2; b <= 10; b++) {
        tobase(n, b, buf);
        if(is_palidrome(buf)) {
            if(++c >= 2) {
                return true;
            }
        }
    }

    return false;
}

int main() {

#ifndef STDIN
    freopen("dualpal.out", "w", stdout);
    freopen("dualpal.in", "r", stdin);
#endif

    int n,s;
    scanf("%d%d", &n, &s);

    for(int i = s+1, c=0; ; i++) {
        if(is_double_palidrome(i)) {
            printf("%d\n", i);
            if(++c >= n) break;
        }
    }

    return 0;
}