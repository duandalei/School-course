// 最简单暴力的思想:每个任务都有两种选择(A或B);n个任务,就有2^n种可能,回溯遍历所有可能

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

const int INF = 1e9;

int main()
{
  int n;
  cin >> n;

  vector<int> a(n), b(n);
  int sumA = 0;
  for (int i = 0; i < n; ++i)
  {
    cin >> a[i];
    sumA += a[i]; // A完成所有作业的最大可能时间
  }
  for (int i = 0; i < n; ++i)
  {
    cin >> b[i];
  }

  // dp[j]表示 A 同学工作量为 j 时，B 同学完成其分配任务的最小时间
  // 初始化为一个很大的数
  vector<int> dp(sumA + 1, INF);
  dp[0] = 0;

  int currentSumA = 0;
  for (int i = 0; i < n; ++i)
  {
    currentSumA += a[i];
    // 必须逆序遍历，防止上一轮的状态被本轮新更新的值覆盖（类似0/1背包优化）
    for (int j = currentSumA; j >= 0; --j)
    {
      int timeB = dp[j] + b[i]; // 方案1：给B做
      int timeA = INF;
      if (j >= a[i])
      {
        timeA = dp[j - a[i]]; // 方案2：给A做
      }
      dp[j] = min(timeA, timeB);
    }
  }

  // 计算最终结果
  int minTotalTime = INF;
  for (int j = 0; j <= sumA; ++j)
  {
    if (dp[j] != INF)
    {
      // 该方案的总时间取决于 A 和 B 中较慢的那一个
      int currentTime = max(j, dp[j]);
      minTotalTime = min(minTotalTime, currentTime);
    }
  }

  cout << minTotalTime << endl;

  return 0;
}
