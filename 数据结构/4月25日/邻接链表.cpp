/*输入 
5 6  (5代表5个顶点,6代表6条无向边)
1 3
2 4
1 4
2 3
3 5
2 5
输出
2 4 3
3 5 3 4
3 5 2 1
2 1 2
2 2 3
*/


#include <stdio.h>

#define MAX_N 5001
#define MAX_M 100001

// 边的数组
int edges[MAX_M * 2];
// 表头数组，存储每个顶点的第一条边的编号
int head[MAX_N];
// 下一条边的数组，存储同一起点的下一条边的编号
int next[MAX_M * 2];
// 记录每个顶点的边的数量
int edgeCount[MAX_N];
// 边的编号(索引)
int idx;

// 添加边的函数
void addEdge(int a, int b)//单向边
{
    edges[idx] = b;//malloc创建一个结点edges[idx],这个结点存放b
    next[idx] = head[a];//malloc创建的这个结点指向头结点的下一个
    head[a] = idx++;//头结点指向malloc创建的这一个结点
    edgeCount[a]++;//用于计数
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    // 初始化表头数组
    for (int i = 1; i <= n; i++)
    {
        head[i] = -1;
    }

    // 读取边的信息
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        // 无向边需要添加两条边
        addEdge(a, b);
        addEdge(b, a);
    }

    // 输出每个顶点的相邻顶点
    for (int i = 1; i <= n; i++)
    {
        printf("%d", edgeCount[i]);
        for (int j = head[i]; j != -1; j = next[j])
        {
            printf(" %d", edges[j]);
        }
        printf("\n");
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
int a[5001][100001], f[5001];//不能运行的原因是数组过大
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x][++f[x]] = y;
        a[y][++f[y]] = x;
    }
    for (int i = 1;i<=n;i++){
        printf("%d ", f[i]);
        for (int j = f[i]; j;j--){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
*/



/*
#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<int> edge[100];

int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cin >> n >> m;
    for (int i = 1;i<=m;i++){
        int x,y;
        cin >> x >> y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    for (int i = 1; i <= n;i++){
        int len=edge[i].size();
        cout << len << " ";
        for (int j = len - 1; j >= 0;j--){
            cout << edge[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}


*/
