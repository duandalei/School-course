#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  vector<int> missiles;
  int height;

  // 1. 读取输入
  // 题目中输入是一行若干个整数，由于不知道具体个数，
  // 使用 while(cin >> height) 读取直到输入结束
  while (cin >> height)
  {
    missiles.push_back(height);
  }

  int n = missiles.size();
  if (n == 0)
  {
    cout << 0 << endl
         << 0 << endl;
    return 0;
  }

  // --- 第一问：计算一套系统最多拦截多少导弹 ---
  // 逻辑：求最长不上升子序列的长度
  // dp1[i] 表示以第 i 个导弹结尾时，最多能拦截的导弹数
  vector<int> dp1(n, 1);
  int max_intercept = 1;

  for (int i = 1; i < n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      // 如果前面的导弹 j 高度 >= 当前导弹 i 高度
      // 说明 i 可以接在 j 后面
      if (missiles[j] >= missiles[i])
      {
        dp1[i] = max(dp1[i], dp1[j] + 1);
      }
    }
    // 更新全局最大值
    max_intercept = max(max_intercept, dp1[i]);
  }

  // --- 第二问：计算最少需要配备多少套系统 ---
  // 逻辑：根据Dilworth定理，这就等价于求“最长上升子序列”的长度
  // dp2[i] 表示以第 i 个导弹结尾的最长上升子序列长度
  vector<int> dp2(n, 1);
  int min_systems = 1;

  for (int i = 1; i < n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      // 如果前面的导弹 j 高度 < 当前导弹 i 高度 (严格上升)
      // 意味着必须用新的系统（或者说这是上升序列的一部分）
      if (missiles[j] < missiles[i])
      {
        dp2[i] = max(dp2[i], dp2[j] + 1);
      }
    }
    // 更新全局最大值
    min_systems = max(min_systems, dp2[i]);
  }

  // 输出结果
  cout << max_intercept << endl;
  cout << min_systems << endl;

  return 0;
}
