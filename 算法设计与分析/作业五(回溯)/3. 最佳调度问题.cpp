/*
不考虑任何剪枝和优化
🔹 对每一个任务，都有 k 台机器可以选
🔹 一共 n 个任务
👉 所有可能的分配方案数 = kⁿ
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // 用于使用 INT_MAX

using namespace std;

// 全局变量
int n, k;
int tasks[25];          // 存储任务时间
int machines[25];       // 存储每台机器当前的累计时间
int best_ans = INT_MAX; // 存储找到的最小的最早完成时间

// 深度优先搜索
// task_idx: 当前正在处理第几个任务
void dfs(int task_idx)
{
    // 【基本结束条件】：所有任务都已经分配完毕
    if (task_idx == n)
    {
        // 找出所有机器中时间最长的那个
        int current_max_time = 0;
        for (int i = 0; i < k; i++)
        {
            if (machines[i] > current_max_time)
            {
                current_max_time = machines[i];
            }
        }
        // 更新全局最优解
        if (current_max_time < best_ans)
        {
            best_ans = current_max_time;
        }
        return;
    }

    // 尝试将当前任务分配给第 0 到 k-1 台机器
    for (int i = 0; i < k; i++)
    {
        // 【剪枝 1】：如果当前这台机器加上新任务后，时间已经超过了目前已知的最优解
        // 那么这个放法肯定不是最优的，直接跳过
        if (machines[i] + tasks[task_idx] >= best_ans)
        {
            continue;
        }

        // 执行操作：放入任务
        machines[i] += tasks[task_idx];

        // 递归处理下一个任务
        dfs(task_idx + 1);

        // 回溯：撤销操作，把任务拿出来，尝试放入下一台机器
        machines[i] -= tasks[task_idx];

        // 【剪枝 2】：如果当前机器是空的（时间为0），放入任务和放入后面其他空机器是等价的
        // 为避免重复搜索同样的情况，直接跳出循环
        if (machines[i] == 0)
            break;
    }
}

// 降序比较函数，用于sort
bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    // 1. 输入
    if (!(cin >> n >> k))
        return 0;

    for (int i = 0; i < n; i++)
    {
        cin >> tasks[i];
    }

    // 2. 排序优化：从大到小排序，利于剪枝
    sort(tasks, tasks + n, cmp);

    // 初始化机器时间为 0
    for (int i = 0; i < k; i++)
    {
        machines[i] = 0;
    }

    // 3. 开始搜索
    dfs(0);

    // 4. 输出结果
    cout << best_ans << endl;

    return 0;
}
