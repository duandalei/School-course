#include <bits/stdc++.h>

using namespace std;

int s1, t1, s2, t2, n, m;
int f[201][201], path[201][201];

void printPath(int s, int t)
{
    if (s == t)
    {
        printf("%d ", s);
        return;
    }
    if (path[s][t] == -1)   return;
    printPath(s, path[s][t]);
    printf("%d ", t);
}

int main()
{
    scanf("%d%d%d%d%d%d", &s1, &t1, &s2, &t2, &n, &m);
    memset(f, 127, sizeof(f));
    memset(path, -1, sizeof(path));

    for (int i = 1; i <= n; i++)
    {
        f[i][i] = 0;
        path[i][i] = i;
    }

    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        if (z < f[x][y] || (z == f[x][y] && x < path[x][y]))
        {
            f[x][y] = z;
            path[x][y] = x;
        }
        if (z < f[y][x] || (z == f[y][x] && x < path[y][x]))
        {
            f[y][x] = z;
            path[y][x] = y;
        }
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (f[i][k] < 1 << 30 && f[k][j] < 1 << 30)
                {
                    if (f[i][j] > (f[i][k] + f[k][j]))
                    {
                        f[i][j] = f[i][k] + f[k][j];
                        path[i][j] = k;
                    }
                    if (f[i][j] == f[i][k] + f[k][j])
                    {
                        path[i][j] = min(path[i][j], k);
                    }
                    
                }
            }
        }
    }
    printf("%d\n", f[s1][t1]);
    printPath(s1, t1);
    printf("\n");
    printf("%d\n", f[s2][t2]);
    printPath(s2, t2);
    printf("\n");
}

// 不会弗洛伊德,用dijkstra实现

/*
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int y, v;
    Node(int _y, int _v) { y = _y; v = _v;}
};
int s1, t1, s2, t2;
int n, m, dist[201], pre[201];
bool b[201];
vector<Node> edge[40001];
void dijkstra(int s, int t)
{
    memset(dist, 127, sizeof(dist));
    memset(b, false, sizeof(b));
    memset(pre, -1, sizeof(pre));
    dist[s] = 0;
    for (;;)
    {
        int x = -1;
        for (int i = 1; i <= n; i++)
        {
            if (!b[i] && dist[i] < 1 << 30)
            {
                if (x == -1 || dist[x] > dist[i])
                {
                    x = i;
                }
            }
        }
        if (x == -1 || x == t)
        {
            break;
        }
        b[x] = true;
        for (auto i : edge[x])
        {
            if(dist[i.y]>dist[x]+i.v){
                dist[i.y] = dist[x] + i.v;
                pre[i.y] = x;
            }
            else if(dist[i.y]==dist[x]+i.v){
                if(pre[i.y]==-1||x<pre[i.y]) pre[i.y] = x;
            }
        }
    }
}

void print_path(int t,int pre[]){
    int path[200], idx = 0, current = t;
    while(current!=-1){
        path[idx++]=current;
        current = pre[current];
    }
    // for (int i = 0; i < idx / 2;i++){
    //     int term=path[i];
    //     path[i]=path[idx-1-i];
    //     path[idx - 1 - i] = term;
    // }
    // for(int i=0;i<idx;i++)  printf("%d ",path[i]);
    for (int i = idx - 1; i >= 0;i--)  printf("%d ",path[i]);
        printf("\n");
}

int main()
{
    scanf("%d%d%d%d%d%d", &s1, &t1, &s2, &t2, &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edge[a].push_back(Node(b, c));
        edge[b].push_back(Node(a, c));
    }
    dijkstra(s1, t1);
    printf("%d\n", dist[t1]);
    print_path(t1, pre);
    dijkstra(s2, t2);
    printf("%d\n", dist[t2]);
    print_path(t2, pre);
}

*/

/*
输入
1 3
2 5
5 7
1 2 6
1 4 2
1 5 23
2 3 4
2 4 3
3 4 20
3 5 7

输出
9
1 4 2 3
11
2 3 5


*/
