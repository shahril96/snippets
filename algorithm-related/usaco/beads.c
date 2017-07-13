/*
 ID: mohd_sh2
 LANG: C
 TASK: beads
 */

#include <stdio.h>
#include <stdlib.h>
#define BUF 10000
#define MAX(i,o) ((i)>(o)?(i):(o))

int n;
char str[BUF];

int next(int i) {
    i++;
    return i % n;
}
int prev(int i) {
    i--;
    return i < 0 ? n - 1 : i;
}

int solve() {

    int t = 0;
    for (int i = 0; i < n; i++) {

        // current value
        int ti = 0;
        char prevc = 0, nextc = 0;

        ti++;
        prevc = nextc = str[i];

        // go backward
        int u, setu = 0;
        for (u = prev(i); u != i; u = prev(u)) {

            if (!setu && (nextc != 'r' || nextc != 'b')) {
                nextc = str[u];
                setu = 1; // one time only
            }

            if (str[u] == 'w' || str[u] == nextc) {
#ifdef DEBUG
                printf("str[u] = %c, nextc = %c, u = %d\n", str[u], nextc, u);
#endif
                ti++;
            } else
                break;
        }

        // more forward one step (don't process this character)
        u = next(u);

        // go forward
        int o, seto = 0;
        for (o = next(i); o != u && o != i; o = next(o)) {

            if (!seto && (prevc != 'r' || prevc != 'b')) {
                prevc = str[o];
                seto = 1; // one time only
            }

            if (str[o] != nextc && (str[o] == 'w' || str[o] == prevc)) {
#ifdef DEBUG
                printf("str[o] = %c, prevc = %c, u = %d, o = %d\n", str[o], prevc, u, o);
#endif
                ti++;
            } else
                break;

        }

#ifdef DEBUG
        printf("i = %d, t = %d, ti = %d\n", i, t, ti);
#endif

        t = MAX(t, ti);
    }
    return t;
}

int main() {

#ifndef STDIN
    freopen("beads.out", "w", stdout);
    freopen("beads.in", "r", stdin);
#endif

    scanf("%d", &n);
    scanf("%s", str);
    printf("%d\n", solve());

    return 0;
}
