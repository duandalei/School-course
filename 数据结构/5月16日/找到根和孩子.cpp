#include <stdio.h>
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int a[n + 1][n + 1]; // 用于表示每个结点后面直接相连的子树
    int b[n + 1];        // 用于a数组的索引
    int root[n + 1];     // 用于找到根节点

    // 初始化作用
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < (n + 1); j++)
        {
            a[i][j] = -1;
        }
    }

    for (int i = 0; i < n + 1; i++)
    {
        b[i] = 0;
        root[i] = 0;
    }

    int x, y;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &x, &y);
        root[y]++;
        a[x][b[x]++] = y;
    }

    for (int i = 1; i < n + 1; i++)
    {
        if (root[i] == 0)
        {
            printf("%d\n", i);
        }
    }

    int max_index = 1;
    for (int i = 2; i < n + 1; i++)
    {
        if (b[i] > b[max_index])
        {
            max_index = i;
        }
    }
    printf("%d\n", max_index);
    for (int i = 0; i < b[max_index]; i++)
    {
        printf("%d ", a[max_index][i]);
    }
}

/*
输入
8 7
4 1
4 2
1 3
1 5
2 6
2 7
2 8


输出
4
2
6 7 8
*/