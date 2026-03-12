/*
不考虑剪枝:按一定顺序枚举每个居民“选 / 不选”的所有可能组合，找出其中满足“互不为仇敌”的方案里人数最多的那个。
👉 本质是在构造一棵二叉决策树
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

// 最大居民数量 (N <= 100)
const int MAXN = 105;

// 全局变量
int n, m;
bool adj[MAXN][MAXN];  // 邻接矩阵：true表示是仇敌
int current_sol[MAXN]; // 当前DFS路径的选中状态 (下标为居民ID)
int best_sol[MAXN];    // 存储目前为止的最优方案
int max_cnt = 0;       // 目前找到的最大卫队人数

// 居民结构体，用于排序
struct Resident
{
    int id;     // 原始编号
    int degree; // 仇敌数量（度）
};

Resident p[MAXN]; // 👉 改为 1-indexed 使用

// 排序比较函数：按仇敌数量从小到大排序
bool cmp(const Resident &a, const Resident &b)
{
    return a.degree < b.degree;
}

// 检查是否可以将居民 u 加入当前队伍
bool is_safe(int u)
{
    for (int i = 1; i <= n; ++i)
    {
        if (current_sol[i] == 1 && adj[u][i])
        {
            return false;
        }
    }
    return true;
}

/**
 * 深度优先搜索
 * @param idx: 当前正在考虑排序后的第 idx 个居民 (1-indexed)
 * @param cnt: 当前卫队中已选的人数
 */
void dfs(int idx, int cnt)
{
    // 剪枝
    if (cnt + (n - idx + 1) <= max_cnt)
    {
        return;
    }

    // 边界条件
    if (idx == n + 1)
    {
        if (cnt > max_cnt)
        {
            max_cnt = cnt;
            memcpy(best_sol, current_sol, sizeof(current_sol));
        }
        return;
    }

    int u = p[idx].id;

    // 分支 1：选
    if (is_safe(u))
    {
        current_sol[u] = 1;
        dfs(idx + 1, cnt + 1);
        current_sol[u] = 0;
    }

    // 分支 2：不选
    dfs(idx + 1, cnt);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(adj, 0, sizeof(adj));
    memset(current_sol, 0, sizeof(current_sol));

    // 👉 p 数组从 1 开始初始化
    for (int i = 1; i <= n; ++i)
    {
        p[i].id = i;
        p[i].degree = 0;
    }

    // 读取仇敌关系
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u][v] = true;
        adj[v][u] = true;

        // 👉 直接用 1-indexed 的 p
        p[u].degree++;
        p[v].degree++;
    }

    // 👉 排序区间改为 [1, n]
    stable_sort(p + 1, p + n + 1, cmp);

    // 👉 从 1 开始 DFS
    dfs(1, 0);

    // 输出结果
    cout << max_cnt << endl;
    for (int i = 1; i <= n; ++i)
    {
        cout << best_sol[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}
