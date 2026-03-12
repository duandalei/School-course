/*
 * 题目：最小m段和
 *
 * 题目描述：
 * 将n个整数组成的序列分割为m段，每段子序列在原序列中连续排列。
 * 求使得m段子序列的和的最大值达到最小的分割方案。
 * 使用动态规划求解，dp[i][j]表示前i个数分成j段的最大段和的最小值。
 * 也可以使用二分+贪心的方法。
 * 时间复杂度O(n^2*m)，可优化。
 */
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
int a[MAXN];
int dp[MAXN][MAXN]; // dp[i][j]：前i个数分成j段的最大段和的最小值
int s[MAXN];        // 前缀和

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++)
  {
    cin >> a[i];
    s[i] = s[i - 1] + a[i];
  }

  // 初始化
  for (int i = 1; i <= n; i++)
  {
    dp[i][1] = s[i]; // 前i个数分成1段，就是前缀和
  }

  // 动态规划
  for (int j = 2; j <= m; j++)
  { // 枚举段数
    for (int i = j; i <= n; i++)
    { // 前i个数，至少需要j个数才能分成j段
      dp[i][j] = INT_MAX;

      // 枚举最后一段的起点k
      // 前k-1个数分成j-1段，第k到i个数作为第j段
      for (int k = j - 1; k < i; k++)
      {
        int last_seg = s[i] - s[k]; // 最后一段的和
        dp[i][j] = min(dp[i][j], max(dp[k][j - 1], last_seg));
      }
    }
  }

  cout << dp[n][m] << endl;
  return 0;
}
