/*
贪心策略:始终挑选当前能参加的活动里，结束时间最早的那个。

因为它结束得早，能够为后面的活动留下最多的可用时间，从而使总活动数最大。
*/
#include <bits/stdc++.h>

using namespace std;

struct node
{
    int start;
    int end;
};


bool compare(const node &A, const node &B)
{
    return A.end < B.end; 
}

int n;

int main()
{
    cin >> n;
    vector<node> activity(n);
    for (int i = 0; i < n; i++)
    {
        cin >> activity[i].start >> activity[i].end;
    }

    // 按结束时间排序
    sort(activity.begin(), activity.end(), compare);

    int cnt = 0;
    int last_end = -1e9;

    // 贪心选择活动
    for (int i = 0; i < n; i++)
    {
        if (activity[i].start >= last_end)
        {
            cnt++;
            last_end = activity[i].end;
        }
    }

    cout << cnt;
    return 0;
}
