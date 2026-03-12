#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10005

typedef struct
{
    int c; // 价格
    int d; // 价值
} Cloud;

int parent[MAX_N];
Cloud clouds[MAX_N];
Cloud groups[MAX_N];
int dp[MAX_N];

// 并查集 - 查找根节点
int find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 并查集 - 合并
void unite(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
    {
        parent[rootY] = rootX;
    }
}

int main()
{
    int n, m, w;
    scanf("%d %d %d", &n, &m, &w);

    // 初始化并查集
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }

    // 读取云朵信息
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", &clouds[i].c, &clouds[i].d);
    }

    // 处理搭配关系
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    // 初始化组信息
    for (int i = 1; i <= n; i++)
    {
        groups[i].c = 0;
        groups[i].d = 0;
    }

    // 计算每个组的总价格和总价值
    for (int i = 1; i <= n; i++)
    {
        int root = find(i);
        groups[root].c += clouds[i].c;
        groups[root].d += clouds[i].d;
    }

    // 初始化动态规划数组
    for (int i = 0; i <= w; i++)
    {
        dp[i] = 0;
    }

    // 0-1背包问题求解
    for (int i = 1; i <= n; i++)
    {
        if (groups[i].c == 0 && groups[i].d == 0)
            continue; // 跳过空组

        for (int j = w; j >= groups[i].c; j--)
        {
            if (dp[j - groups[i].c] + groups[i].d > dp[j])
            {
                dp[j] = dp[j - groups[i].c] + groups[i].d;
            }
        }
    }

    printf("%d\n", dp[w]);
    return 0;
}