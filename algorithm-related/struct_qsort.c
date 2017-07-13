/* Performance of qsort, worst case O(n log n)
   
   Example input :

   3
   4 9
   -3 48
   -100 48

   Example output :

   before sort --
   x = 4, y = 9
   x = -3, y = 48
   x = -100, y = 48

   after sort --
   x = -100, y = 48
   x = -3, y = 48
   x = 4, y = 9 */

#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int x, y;
} List;

void print_struct(List *struct_ptr, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("x = %d, y = %d\n", struct_ptr[i].x, struct_ptr[i].y);
    }
}

int cmp_ret(const void *aptr, const void *bptr)
{
    int a = ((List *)aptr)->x, b = ((List *)bptr)->x;
    return (a > b) - (a < b);
}

int main()
{
    int n;
    scanf("%d", &n);

    List *li = (List *)malloc(sizeof(List) * n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &li[i].x, &li[i].y);
    }

    puts("\nbefore sort --");
    print_struct(li, n);

    qsort(li, n, sizeof(List), cmp_ret);

    puts("\nafter sort --");
    print_struct(li, n);

    free(li);
}
