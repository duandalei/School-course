#include <bits/stdc++.h>

using namespace std;

struct student
{
    int idx;
    int time;
};
bool compare(const student &A, const student &B)
{
    if (A.time != B.time)
    {
        return A.time < B.time;
    }
    return A.idx < B.idx;
}
int n;
int main()
{
    cin >> n;
    vector<student> activity(n);
    for (int i = 0; i < n; i++)
    {
        cin >> activity[i].time;
        activity[i].idx = i;
    }
    sort(activity.begin(), activity.end(), compare);
    int sum_wait = 0;
    int wait = 0; // 每个人总共要等待的时间
    for (int i = 0; i < n; i++)
    {
        cout << activity[i].idx + 1 << ' ';
        wait += activity[i].time;
        sum_wait += wait;
    }
    cout << endl;
    // 注意精度问题
    // 错误写法 printf("%.2lf", (double) (sum_wait / n));
    printf("%.2lf", (double)sum_wait / n); // 正确写法
    // 正确写法 printf("%.2lf", 1.0 * sum_wait / n);
    return 0;
}