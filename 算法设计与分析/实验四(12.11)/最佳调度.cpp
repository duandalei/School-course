#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;

// 定义节点结构
struct Node
{
    int assigned_count;             // 已经分配的任务数 (i)
    vector<long long> machine_time; // k台机器当前的总工作时间
    long long lower_bound;          // 节点的下界 L

    // 重载 < 运算符，用于优先队列 (小顶堆)
    // 使得 lower_bound 较小的节点具有更高的优先级
    bool operator>(const Node &other) const
    {
        return lower_bound > other.lower_bound;
    }
};

// 任务调度问题求解
long long solve_scheduling(int n, int k, vector<int> &tasks)
{
    // 1. 预处理：将任务时间降序排序 (启发式优化)
    sort(tasks.rbegin(), tasks.rend());

    // 计算所有任务的总时间
    long long total_time = accumulate(tasks.begin(), tasks.end(), 0LL);

    // 初始化：最优解 (最小Makespan)
    long long C_min = numeric_limits<long long>::max();

    // 优先队列：小顶堆，按 lower_bound 排序
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // 2. 根节点初始化
    Node root;
    root.assigned_count = 0;
    root.machine_time.assign(k, 0); // 所有机器时间初始化为 0
    // 根节点的下界：所有任务总时间除以机器数 k 的上界 (这是一个全局下界)
    root.lower_bound = (total_time + k - 1) / k;

    pq.push(root);

    // 3. 搜索过程
    while (!pq.empty())
    {
        Node u = pq.top();
        pq.pop();

        // 剪枝：如果节点的下界 L >= C_min，则无需再扩展
        if (u.lower_bound >= C_min)
        {
            continue;
        }

        // 检查是否为叶节点 (所有任务已分配)
        if (u.assigned_count == n)
        {
            // 计算当前调度的最大完成时间 (Makespan)
            long long current_makespan = *max_element(u.machine_time.begin(), u.machine_time.end());
            // 更新最优解
            C_min = min(C_min, current_makespan);
            continue;
        }

        // 非叶节点：尝试分配下一个任务 tasks[u.assigned_count]
        int task_time = tasks[u.assigned_count];
        long long remaining_time = total_time - accumulate(u.machine_time.begin(), u.machine_time.end(), 0LL) - task_time;

        // 遍历 k 台机器，进行分支
        for (int j = 0; j < k; ++j)
        {
            Node v = u; // 复制父节点

            // 任务分配
            v.assigned_count++;
            v.machine_time[j] += task_time;

            // 计算子节点 v 的下界 L'
            long long max_current_time = *max_element(v.machine_time.begin(), v.machine_time.end());

            // 下界 L' = max(当前机器最大时间, (所有任务总时间 / k) )
            // 采用更精确的下界： max(当前机器最大时间, (当前总时间 + 剩余任务总时间) / k )
            // 这里我们使用： max(当前机器最大时间, (当前机器总时间 + 剩余时间) / k )
            long long average_remaining = (remaining_time + k - 1) / k;

            // L' = max(当前机器最大时间, max(当前机器最大时间, 剩余任务平均时间 + min(机器当前时间)))
            // 简化为：当前最大机器时间 或 (所有任务总时间/k)的max，我们继续使用当前最大时间 + 剩余平均时间

            // L' = max( max_current_time, total_time / k );

            // L' = 当前机器最大时间 + 剩余任务平均时间 (这是一个好的下界)
            long long lower_bound_2 = max_current_time;
            if (v.assigned_count < n)
            {
                long long remaining_tasks_sum = 0;
                for (int m = v.assigned_count; m < n; ++m)
                {
                    remaining_tasks_sum += tasks[m];
                }
                lower_bound_2 = max(max_current_time, (remaining_tasks_sum + k - 1) / k + *min_element(v.machine_time.begin(), v.machine_time.end()));
            }

            // 最终决定使用一个相对简单的下界，即 max_current_time 本身
            // 实际上，max(max_current_time, total_time / k) 更能发挥限界作用
            v.lower_bound = max(max_current_time, (total_time + k - 1) / k);

            // 再次剪枝：如果 L' < C_min，则将节点加入队列
            if (v.lower_bound < C_min)
            {
                pq.push(v);
            }
        }
    }

    return C_min;
}

// 主函数和样例输入/输出
int main()
{
    // 禁用同步，提高 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;

    // 输入 n 和 k
    if (!(cin >> n >> k))
        return 0;

    // 输入任务时间
    vector<int> tasks(n);
    for (int i = 0; i < n; ++i)
    {
        if (!(cin >> tasks[i]))
            return 0;
    }

    // 求解并输出结果
    long long result = solve_scheduling(n, k, tasks);
    cout << result << endl;

    return 0;
}