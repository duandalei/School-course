#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, m;
    int *a, *b, *c;
    scanf("%d", &n);
    a = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", a + i);
    }
    scanf("%d", &m);
    b = (int *)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d", b + i);
    }
    c = (int *)malloc(sizeof(int) * (n + m));
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    while (cnt1 < n && cnt2 < m)
    {
        if (a[cnt1] > b[cnt2])
        {
            c[cnt3++] = b[cnt2++];
        }
        else
        {
            c[cnt3++] = a[cnt1++];
        }
    }
    while (cnt1 < n)
    {
        c[cnt3++] = a[cnt1++];
    }
    while (cnt2 < m)
    {
        c[cnt3++] = b[cnt2++];
    }
    for (int i = 0; i < cnt3; i++)
    {
        printf("%d ", c[i]);
    }
}