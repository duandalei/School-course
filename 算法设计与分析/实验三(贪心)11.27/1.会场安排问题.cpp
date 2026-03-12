#include <iostream>
#include <vector>
#include <algorithm>
#include <queue> 

using namespace std;

// 定义活动结构体
struct Activity
{
    int start;
    int end;
};

// 用于排序的比较函数：按开始时间升序
bool compare(const Activity &a, const Activity &b)
{
    return a.start < b.start;
}

void solve()
{
    int k;
    cin >> k;

    // 1. 读取所有活动
    vector<Activity> activities(k);
    for (int i = 0; i < k; ++i)
    {
        cin >> activities[i].start >> activities[i].end;
    }

    // 2. 贪心策略的第一步：按开始时间排序
    sort(activities.begin(), activities.end(), compare);

    // 3. 使用最小堆存储已分配会场的结束时间
    // 默认的 priority_queue 是大顶堆，需要用 greater<int> 模板参数实现小顶堆
    priority_queue<int, vector<int>, greater<int>> min_heap;

    // 4. 遍历活动并进行贪心分配
    for (const auto &activity : activities)
    {

        // 检查是否有会场可以重用 (堆非空)
        if (!min_heap.empty())
        {
            // 获取最早空闲的会场结束时间 (堆顶)
            int earliest_finish_time = min_heap.top();

            // 核心贪心判断：
            // 如果最早空闲的会场能接上当前活动 (当前活动开始 >= 最早空闲时间)
            if (activity.start >= earliest_finish_time)
            {
                // 情况一：重用会场
                min_heap.pop();              // 弹出旧的结束时间
                min_heap.push(activity.end); // 压入新的结束时间
            }
            else
            {
                // 情况二：最早空闲的会场也不能用，必须新增会场
                min_heap.push(activity.end); // 将新会场的结束时间压入
            }
        }
        else
        {
            // 初始情况：堆为空，第一个活动必须分配一个新会场
            min_heap.push(activity.end);
        }
    }

    // 5. 结果：堆中元素的数量即为最少需要的会场数
    cout << min_heap.size() << endl;
}

int main()
{
    // 优化输入/输出速度
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}