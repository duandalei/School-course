#include <bits/stdc++.h>
using namespace std;
int n, adj[101][101], dist[101];
bool b[101];
inline void prim()
{
    memset(dist, 127, sizeof(dist));
    memset(b, false, sizeof(b));
    dist[1] = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int x = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!b[j] && dist[j] < 1 << 30)
            {
                if (x == -1 || dist[x] > dist[j])
                {
                    x = j;
                }
            }
        }
        ans += dist[x];
        b[x] = true;
        for (int k = 1; k <= n; k++)
        {
            if (adj[x][k])
            {
                dist[k] = min(dist[k], adj[x][k]);
            }
        }
    }
    cout << ans;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int x;
            cin >> x;
            adj[i][j] = x;
        }
    }

    prim();
}

