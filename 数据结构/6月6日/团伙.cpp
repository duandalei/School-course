#include <stdio.h>
#include <stdlib.h>
#define MAX 2010
int parent[MAX];
void init(int n)
{
    for (int i = 1; i <= 2 * n; i++)
    {
        parent[i] = i;
    }
}
int find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent[x]);//压缩路径
    }
    return parent[x];

}
void Set(int x, int y)
{
    int X = find(x);
    int Y = find(y);
    if (X != Y)
    {
        parent[X] = Y;
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    init(n);
    for (int i = 0; i < m; i++)
    {
        int p, x, y;
        scanf("%d%d%d", &p, &x, &y);
        if (p == 0)
        {
            Set(x, y);
        }
        else
        {
            Set(x, y + n);
            Set(y, x + n);
        }
    }
    int count = 0;
    int v[MAX] = {0};
    for (int i = 1; i <= n; i++)
    {
        int root = find(i);
        if (!v[root])
        {
            v[root] = 1;
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}