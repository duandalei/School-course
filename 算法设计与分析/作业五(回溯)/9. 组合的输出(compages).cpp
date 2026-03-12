#include <bits/stdc++.h>

using namespace std;

int n, r;
int path[30];

void dfs(int start, int idx)
{
    if (idx == r + 1)
    {
        for (int i = 1; i <= r; i++)
        {
            cout << setw(3) << path[i];
        }
        cout << endl;
        return;
    }
    for (int i = start; i <= n; i++)
    {
        path[idx] = i;
        dfs(i + 1, idx + 1);
    }
}

int main()
{
    cin >> n >> r;
    dfs(1, 1);
    return 0;
}