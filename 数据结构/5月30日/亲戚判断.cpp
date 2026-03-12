#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;
int parent[MAXN];

int find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent[x]); // 路径压缩
    }
    return parent[x];
}

void unite(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
    {
        parent[rootX] = rootY;
    }
}



int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化并查集
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }

    // 处理亲戚关系
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        unite(a, b);
    }

    int q;
    scanf("%d", &q);
    int t = 0;
    int term[1000000];
    for (int i = 0; i < q; i++)
    {
        int c, d;
        scanf("%d%d", &c, &d);
        if (find(c) == find(d))
        {
            term[t++] = 1;

        }
        else
        {
            term[t++] = 0;
           
        }
    }
    for (int i = 0; i < t;i++){
        if(term[i]==0){
            printf("No\n");
        }
        else{
            printf("Yes\n");
        }
    }

        return 0;
}