#include<bits/stdc++.h>
using namespace std;
struct Node {
    int y;
    double v;
    Node(int _y,double _v){
        y=_y;
        v = _v;
    }
};

struct coordinate{
    int p,q;
    coordinate() : p(0), q(0) {}
    coordinate(int _p,int _q){
        p=_p;
        q = _q;
    }
};

int n, m;
double dist[101];
bool b[101];
coordinate node[101];//需要默认构造函数
vector<Node> edge[100001];


double edge_length(coordinate &node1,coordinate &node2){
    int dx = node1.p - node2.p;
    int dy = node1.q - node2.q;
    double len=sqrt(dx*dx+dy*dy);
    return len;
}


void dijkstra(int s, int t)
{
    memset(dist, 127, sizeof(dist));
    memset(b, false, sizeof(b));
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
            dist[i.y] = min(dist[i.y], dist[x] + i.v);
        }
    }
    printf("%.2f", dist[t]);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int x, y;
        scanf("%d%d", &x, &y);
        node[i] = coordinate(x, y);
    }
    
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int c,d;
        scanf("%d%d", &c, &d);
        double len = edge_length(node[c], node[d]);
        edge[c].push_back(Node(d,len));
        edge[d].push_back(Node(c, len));
    }
    int s,t;
    scanf("%d%d",&s,&t);
    dijkstra(s, t);
}

/*

5
0 0
2 0
2 2
0 2
3 1
5
1 2
1 3
1 4
2 5
3 5
1 5


*/


