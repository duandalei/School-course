#include <bits/stdc++.h>
using namespace std;

int n, m;
bool enemy[105][105];
int degreeCnt[105];

vector<int> order;     // 排序后的居民编号
vector<int> cur, best; // 当前解 & 最优解
int bestCnt = 0;

// 判断 resident 是否可以加入当前卫队
bool canJoin(int resident)
{
    for (int x : cur)
    {
        if (enemy[x][resident])
            return false;
    }
    return true;
}

void dfs(int idx)
{
    // 剪枝：即使后面全选，也不可能超过最优
    if ((int)cur.size() + (int)order.size() - idx <= bestCnt)
        return;

    // 搜索到末尾
    if (idx == (int)order.size())
    {
        if ((int)cur.size() > bestCnt)
        {
            bestCnt = cur.size();
            best = cur;
        }
        return;
    }

    int u = order[idx];

    // 尝试选 u
    if (canJoin(u))
    {
        cur.push_back(u);
        dfs(idx + 1);
        cur.pop_back();
    }

    // 不选 u
    dfs(idx + 1);
}

int main()
{
    cin >> n >> m;
    memset(enemy, false, sizeof(enemy));

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        enemy[u][v] = enemy[v][u] = true;
        degreeCnt[u]++;
        degreeCnt[v]++;
    }

    // 初始化顺序
    for (int i = 1; i <= n; i++)
        order.push_back(i);

    // 按矛盾数量（度数）升序稳定排序
    stable_sort(order.begin(), order.end(),
                [&](int a, int b)
                {
                    return degreeCnt[a] < degreeCnt[b];
                });

    dfs(0);

    // 输出结果
    vector<int> ans(n + 1, 0);
    for (int x : best)
        ans[x] = 1;

    cout << bestCnt << "\n";
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";

    return 0;
}
