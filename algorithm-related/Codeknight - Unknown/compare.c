
#include <stdio.h>
#include <string.h>

int main() {

    char a[999999], b[999999];
    char *c, *d;
    int an, bn;
  
    // %n = read number of bytes read, ez & fast way without strlen()
    scanf("%s%n", a, &an);
    scanf("%s%n", b, &bn);
    bn--; // decrement to minus zero null terminator
  
    // pointer increment
    c = a, d = b; // tmp pointer
    while(*c == '0') { c++; an--; }
    while(*d == '0') { d++; bn--; }
    if(an > bn) {
        printf(">\n");
        return 0;
    } else if (an < bn) {
        printf("<\n");
        return 0;
    } else {
        int cmp = strcmp(c, d);
        if(cmp == 0) 
            printf("=\n");
        else if (cmp < 0) 
            printf("<\n");
        else
            printf(">\n");
        return 0;
    }
}