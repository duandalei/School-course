#include <bits/stdc++.h>
using namespace std;

int n, k;
int t[21];
int load[21];
int ans = INT_MAX;

void dfs(int idx)
{
    if (idx == n)
    {
        int cur = 0;
        for (int i = 0; i < k; i++)
            cur = max(cur, load[i]);
        ans = min(ans, cur);
        return;
    }

    for (int i = 0; i < k; i++)
    {
        if (load[i] + t[idx] >= ans)
            continue;

        // 剪枝：相同负载的机器只试一次
        bool same = false;
        for (int j = 0; j < i; j++)
            if (load[j] == load[i])
                same = true;
        if (same)
            continue;

        load[i] += t[idx];
        dfs(idx + 1);
        load[i] -= t[idx];
    }
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> t[i];

    // 关键优化：从大到小排序
    sort(t, t + n, greater<int>());

    dfs(0);
    cout << ans;
}

/*
#include <bits/stdc++.h>

using namespace std;

int n, k;
int ans;

int main()
{
    cin >> n >> k;
    vector<int> a(n, 0);
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < k; i++)
    {
        heap.push(a[i]);
    }
    for (int i = k; i < n; i++)
    {
        int temp = heap.top();
        heap.pop();
        heap.push(temp + a[i]);
    }
    int ans = 0;
    while (!heap.empty())
    {
        ans = heap.top();
        heap.pop();
    }
    cout << ans;
}

*/
