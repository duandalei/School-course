// 总体思路:一共有n个工作,每个工作有n个分配选择(假设一人可以承担多个工作)

#include <bits/stdc++.h>
using namespace std;

int n;
int ans = 1e9;
int a[30][30];
bool b[30]; // 确保每一个人都有一份工作

// idx表示当前第几个工作,total表示总花费
void dfs(int idx, int total)
{
    if (idx == n + 1)
    {
        if (total < ans)
        {
            ans = total;
        }
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!b[i])
        {
            total += a[idx][i];
            b[i] = 1;
            dfs(idx + 1, total);
            total = total - a[idx][i];
            b[i] = 0;
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
        }
    }
    dfs(1, 0);
    cout << ans;
}
