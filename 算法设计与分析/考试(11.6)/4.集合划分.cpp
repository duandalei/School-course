#include <iostream>
#include <vector>
#include <numeric>
#define int long long
using namespace std;

int bell_number(int n)
{
    if (n == 0)
    {
        return 1;
    }

    // DP[i][j] 存储第二类斯特林数 S(i, j)，即 i 个元素划分为 j 个非空子集的方案数。
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // 基本情况：S(i, 0) = 0 (i >= 1) 和 S(0, 0) = 1
    dp[0][0] = 1;

    // 递推计算 S(i, j)
    for (int i = 1; i <= n; ++i)
    { // i 个元素
        for (int j = 1; j <= i; ++j)
        { // 划分为 j 个子集
            // 递推关系：S(i, j) = S(i-1, j-1) + j * S(i-1, j)
            // 1. i 独立成一个子集：S(i-1, j-1)
            // 2. i 加入到 i-1 元素形成的 j 个子集中的任意一个：j * S(i-1, j)
            dp[i][j] = dp[i - 1][j - 1] + (int)j * dp[i - 1][j];
        }
    }
    int ans = 0;
    for (int k = 1; k <= n; ++k)
    {
        ans += dp[n][k];
    }
    return ans;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int result = bell_number(n);
    cout << result << "\n";
    return 0;
}