/*
 * 题目：矩阵链乘法
 *
 * 题目描述：
 * 给定k个矩阵，每次可以合并相邻的两个矩阵，求使得总运算次数最少的合并方案。
 * 使用区间动态规划求解，dp[i][j]表示合并第i到第j个矩阵的最少运算次数。
 * 时间复杂度O(k^3)，空间复杂度O(k^2)。
 */
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

const int MAXN = 105;
int dp[MAXN][MAXN];
int row[MAXN], col[MAXN];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int k;
  cin >> k;

  for (int i = 1; i <= k; i++)
  {
    cin >> row[i] >> col[i];
  }

  // 初始化：单个矩阵不需要运算
  memset(dp, 0, sizeof(dp));

  // 区间DP：按长度从小到大枚举
  for (int len = 2; len <= k; len++)
  {
    for (int i = 1; i <= k - len + 1; i++)
    {
      int j = i + len - 1;
      dp[i][j] = INT_MAX;

      // 枚举分割点k，将[i,j]分为[i,k]和[k+1,j]
      for (int k = i; k < j; k++)
      {
        // 合并[i,k]的代价 + 合并[k+1,j]的代价 + 最后两个矩阵相乘的代价
        int cost = dp[i][k] + dp[k + 1][j] + row[i] * col[k] * col[j];
        dp[i][j] = min(dp[i][j], cost);
      }
    }
  }

  cout << dp[1][k] << endl;
  return 0;
}
