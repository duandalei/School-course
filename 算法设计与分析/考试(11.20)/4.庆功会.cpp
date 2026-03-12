/*
 * 题目：庆功会（多重背包问题）
 *
 * 题目描述：
 * 有n种奖品，每种奖品有价格v、价值w和数量限制s。
 * 给定拨款金额m，求能购买的最大价值。
 * 使用多重背包动态规划求解，可以转换为0-1背包或使用二进制优化。
 * 时间复杂度O(n*m*s)，可优化到O(n*m*log(s))。
 */
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 505;
const int MAXM = 6005;
int dp[MAXM];
int v[MAXN], w[MAXN], s[MAXN];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++)
  {
    cin >> v[i] >> w[i] >> s[i];
  }

  // 多重背包：每种物品可以选择0到s[i]件
  for (int i = 1; i <= n; i++)
  {
    // 从大到小枚举金额
    for (int j = m; j >= v[i]; j--)
    {
      // 枚举选择第i种物品的数量
      for (int k = 0; k <= s[i] && k * v[i] <= j; k++)
      {
        dp[j] = max(dp[j], dp[j - k * v[i]] + k * w[i]);
      }
    }
  }

  cout << dp[m] << endl;
  return 0;
}
