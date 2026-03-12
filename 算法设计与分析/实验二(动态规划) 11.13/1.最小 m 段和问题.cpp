#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // 用于 LLONG_MAX

using namespace std;

int main()
{
    // 1. 输入处理
    int n, m;
    cin >> n >> m;

    vector<int> nums(n + 1);
    vector<long long> prefix_sum(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> nums[i];
        // 计算前缀和，方便O(1)求区间和
        prefix_sum[i] = prefix_sum[i - 1] + nums[i];
    }

    // 2. DP 初始化
    // dp[i][j] 表示前 i 个数分成 j 段的最优解
    // 这是一个 (n+1) x (m+1) 的二维数组
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, LLONG_MAX));

    // 边界条件：前 i 个数分成 1 段，其代价就是前 i 个数的和
    for (int i = 1; i <= n; i++)
    {
        dp[i][1] = prefix_sum[i];
    }
    // 边界：dp[0][0] 可以在逻辑上视为 0，但主循环不会用到它，因为我们从 j=2 开始

    // 3. 状态转移
    // 外层循环：枚举段数 j，从 2 到 m
    for (int j = 2; j <= m; j++)
    {
        // 中层循环：枚举当前考虑的数字个数 i，从 j 到 n
        // (因为 i 个数最多只能分成 i 段，所以 i 至少要等于 j)
        for (int i = j; i <= n; i++)
        {

            // 内层循环：枚举分割点 k
            // 我们要把 [1...i] 分成两部分：[1...k] 分成 j-1 段，和 [k+1...i] 作为第 j 段
            // k 的范围：至少要有 j-1 个数给前 j-1 段，所以 k 从 j-1 开始
            // k < i，因为最后一段至少包含 1 个数
            for (int k = j - 1; k < i; k++)
            {

                // 计算最后一段 [k+1, i] 的和
                long long last_segment_sum = prefix_sum[i] - prefix_sum[k];

                // 当前这种切分方式下的“最大段和”
                long long current_max = max(dp[k][j - 1], last_segment_sum);

                // 我们要所有切分方式中最小的那个
                dp[i][j] = min(dp[i][j], current_max);
            }
        }
    }

    // 4. 输出结果
    cout << dp[n][m] << endl;

    return 0;
}
