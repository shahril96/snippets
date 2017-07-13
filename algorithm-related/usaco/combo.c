/*
 ID: mohd_sh2
 LANG: C
 TASK: combo
 */

#include <stdio.h>
#include <stdbool.h>

int solutions = 0;
int n, key[2][3];

int next(int num) { return ++num > n ? 1 : num; }
int prev(int num) { return --num <= 0 ? n : num; }

bool check(int tmp[]) {
    for (int i = 0; i < 2; i++) {
        int c = 0, kd, td;
        for (int j = 0; j <= 2; j++) {
            kd = key[i][j], td = tmp[j];
            if (td == kd ||
                td == next(kd) || td == next(next(kd)) ||
                td == prev(kd) || td == prev(prev(kd)))
            {
                c++;
            }
        }
        if (c == 3) {
            return true;
        }
    }
    return false;
}

int main() {

#ifndef STDIN
    freopen("combo.out", "w", stdout);
    freopen("combo.in", "r", stdin);
#endif

    scanf("%d", &n);
    scanf("%d%d%d", &key[0][2], &key[0][1], &key[0][0]);
    scanf("%d%d%d", &key[1][2], &key[1][1], &key[1][0]);

    int tmp[3];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int o = 1; o <= n; o++) {
                tmp[2] = i, tmp[1] = j, tmp[0] = o;
                if (check(tmp))
                    solutions++;
            }
        }
    }

    printf("%d\n", solutions);

    return 0;
}