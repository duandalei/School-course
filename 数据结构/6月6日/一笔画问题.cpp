#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int y, idx;
    Node(int _y, int _idx)
    {
        y = _y;
        idx = _idx;
    }
    bool operator < (const Node&A) const{
        return y < A.y;
    }
};
vector<Node> edge[1001];
int n, m, cnt = 1, l, f[1001], c[1002], d[1001];
bool b[2002];

inline void dfs(int x)
{
    while (f[x] < d[x])
    {
        int y = edge[x][f[x]].y, idx = edge[x][f[x]].idx;
        if (!b[idx])
        {
            ++f[x];
            b[idx] = b[idx ^ 1] = true;
            dfs(y);
            c[++l] = y;
        }
        else
            ++f[x];
    }
}

inline void Euler()
{
    int x = 0; 
        for (int i = 1; i <= n; i++)
        {
            if (d[i]){
                x = i;
                break;
            }
                
        }
    memset(b, false, sizeof(b));
    memset(f, 0, sizeof(f));
    l = 0;
    dfs(x);
    c[++l] = x;
    for (int i = l; i;i--){
        printf("%d ", c[i]);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        edge[x].push_back(Node(y, ++cnt));
        edge[y].push_back(Node(x, ++cnt));
        ++d[x], ++d[y];
    }
    for(int i=1;i<=n;i++){
        sort(edge[i].begin(), edge[i].end());
    }
    Euler();
}
/*
5 5
1 2
2 3
3 4
4 5
5 1
*/
