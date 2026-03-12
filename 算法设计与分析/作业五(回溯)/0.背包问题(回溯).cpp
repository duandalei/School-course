// 01背包(回溯思想)
#include <bits/stdc++.h>

using namespace std;

int cap, n;
int value[20], weight[20];
int ans = 0;

void dfs(int idx, int remaining_cap, int max_value)
{
    if (idx == n + 1)
    {
        if (max_value > ans)
        {
            ans = max_value;
        }
        return;
    }

    dfs(idx + 1, remaining_cap, max_value); // Not take
    if (remaining_cap >= weight[idx])       // Take
    {
        dfs(idx + 1, remaining_cap - weight[idx], max_value + value[idx]);
    }
}

int main()
{
    cin >> cap >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> value[i] >> weight[i];
    }
    dfs(1, cap, 0);
    cout << ans;
}

// 完全背包

/*
#include <bits/stdc++.h>
using namespace std;

int cap, n;
int value[20], weight[20];
int ans = 0;

void dfs(int idx, int remaining_cap, int max_value)
{
    if (idx == n + 1)
    {
        ans = max(ans, max_value);
        return;
    }

    // 不取第 idx 个，考虑下一个
    dfs(idx + 1, remaining_cap, max_value);

    // 取第 idx 个（还能继续取 idx）
    if (remaining_cap >= weight[idx])
    {
        dfs(idx, remaining_cap - weight[idx], max_value + value[idx]);
    }
}

int main()
{
    cin >> cap >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> value[i] >> weight[i];
    }
    dfs(1, cap, 0);
    cout << ans;
}



*/
