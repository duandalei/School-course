/*
 * 题目：最长公共上升子序列
 *
 * 题目描述：
 * 对于两个数列A和B，求它们的最长公共上升子序列的长度。
 * 公共上升子序列：既是A和B的公共子序列，又是严格递增的。
 * 使用动态规划求解，结合最长公共子序列和最长上升子序列的思想。
 * dp[i][j]表示考虑A的前i个元素和B的前j个元素时，以B[j]结尾的LCIS长度。
 * 时间复杂度O(n^2)，使用maxv优化避免内层循环，空间复杂度O(n^2)。
 */
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 3005;

// dp[i][j]：考虑A[1..i]和B[1..j]时，以B[j]结尾的最长公共上升子序列（LCIS）的长度。
int dp[MAXN][MAXN];
int A[MAXN], B[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  // 读入序列A和B (从索引1开始存储)
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> B[i];
  }

  // --- 动态规划主循环 O(n^2) ---
  for (int i = 1; i <= n; i++) {
    // maxv：用于优化的变量。
    // 它记录了所有 B[k] < A[i] 的 dp[i-1][k] 的最大值。
    int maxv = 0;

    for (int j = 1; j <= n; j++) {

      // ** 状态转移方程的核心实现 **
      if (A[i] == B[j]) {
        // 情况 1: A[i] 匹配 B[j]
        // 新的长度是 max(不使用A[i]时的长度, 使用A[i]匹配时的长度)
        dp[i][j] = max(dp[i - 1][j], maxv + 1);
      } else {
        // 情况 2: A[i] 不匹配 B[j] (或 A[i] != B[j])
        dp[i][j] = dp[i - 1][j];
      }
      // ** 状态转移方程的核心实现结束 **

      // 维护 maxv (为 j+1 时做准备)：
      // 如果 B[j] < A[i]，那么 dp[i-1][j] 可以作为未来 A[i] 匹配时的合格前缀。
      // 必须使用 dp[i-1][j]，因为 LCIS
      // 必须是严格上升的，A[i]不能接在由A[i]生成的子序列后面。
      if (B[j] < A[i]) {
        maxv = max(maxv, dp[i - 1][j]);
      }
    }
  }

  // --- 找出最终答案 ---
  // 最终答案是 dp[n][j] 在 j=1 到 n 范围内的最大值。
  int ans = 0;
  for (int j = 1; j <= n; j++) {
    ans = max(ans, dp[n][j]);
  }

  cout << ans << endl;
  return 0;
}