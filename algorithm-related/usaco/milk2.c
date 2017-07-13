/*
 ID: mohd_sh2
 LANG: C
 TASK: milk2
 */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define MAX(i,o) ((i)>(o)?(i):(o))
#define MIN(i,o) ((i)<(o)?(i):(o))
#define BUF 1000000

int n, max_to_explore = INT_MIN, min_to_explore = INT_MAX;
bool set[BUF];

int main() {

#ifndef STDIN
    freopen("milk2.out", "w", stdout);
    freopen("milk2.in", "r", stdin);
#endif

    scanf("%d", &n);

    int a, b;
    while (n-- > 0) {
        scanf("%d%d", &a, &b);
        max_to_explore = MAX(MAX(max_to_explore, a), b);
        min_to_explore = MIN(MIN(min_to_explore, a), b);
        while (a < b)
            set[a++] = 1;
    }

    int prev = 1, total_states[2] = { 0 }; // 0 - no milking, 1 - milking
    int cur_total = 0;

    // linear search
    for (int i = min_to_explore; i <= max_to_explore; i++) {
        if (set[i] != prev) {
            total_states[prev] = MAX(total_states[prev], cur_total);
            prev = set[i], cur_total = 1;
        } else {
            cur_total++;
        }
    }

    printf("%d %d\n", total_states[1], total_states[0]);

}
