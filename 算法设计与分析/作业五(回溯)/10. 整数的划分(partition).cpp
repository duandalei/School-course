#include <bits/stdc++.h>
using namespace std;

int n, k;
int ans = 0;

// last强制生成序列是非递减的：保证“不考虑顺序”
void dfs(int pos, int last, int sum)
{
    if (pos == k)
    {
        if (sum == n)
            ans++;
        return;
    }
    if (sum > n)
        return;

    // 剩余最少和：每份至少为 last
    if (sum + (k - pos) * last > n)
        return;

    for (int i = last; i <= n - sum; i++)
    {
        dfs(pos + 1, i, sum + i);
    }
}

int main()
{
    cin >> n >> k;
    dfs(0, 1, 0);
    cout << ans;
    return 0;
}
