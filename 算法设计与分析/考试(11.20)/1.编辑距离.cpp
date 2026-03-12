/*
 * 题目：编辑距离
 *
 * 题目描述：
 * 计算将字符串A转换为字符串B所需的最少字符操作次数。
 * 三种操作：删除一个字符、插入一个字符、将一个字符改为另一个字符。
 * 使用动态规划求解，dp[i][j]表示A的前i个字符转换为B的前j个字符的最少操作次数。
 * 时间复杂度O(n*m)，空间复杂度O(n*m)。
 */
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

const int MAXN = 2005;
int dp[MAXN][MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string A, B;
  cin >> A >> B;

  int n = A.length();
  int m = B.length();

  // 初始化：空字符串转换
  for (int i = 0; i <= n; i++) {
    dp[i][0] = i; // A的前i个字符转换为空字符串需要删除i次
  }
  for (int j = 0; j <= m; j++) {
    dp[0][j] = j; // 空字符串转换为B的前j个字符需要插入j次
  }

  // 动态规划
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      
      if (A[i - 1] == B[j - 1]) {
        // 字符相同，不需要操作
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        // 字符不同，取三种操作的最小值
        // 1. 删除A[i-1]：dp[i-1][j] + 1
        // 2. 插入B[j-1]：dp[i][j-1] + 1
        // 3. 替换A[i-1]为B[j-1]：dp[i-1][j-1] + 1
        dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
      }
    }
  }

  cout << dp[n][m] << endl;
  return 0;
}
