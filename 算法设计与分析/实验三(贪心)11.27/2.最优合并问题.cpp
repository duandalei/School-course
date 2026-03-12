//合并果子
#include <bits/stdc++.h>

using namespace std;

int k;
int num;
priority_queue<int, vector<int>, greater<int>> min_heap;

priority_queue<int, vector<int>> max_heap;

int main()
{
    cin >> k;
    for (int i = 1; i <= k; i++)
    {
        cin >> num;
        min_heap.push(num);
        max_heap.push(num);
    }
    int ans1 = 0, ans2 = 0;
    int x1, y1, x2, y2;
    // 需要合并k-1次
    for (int i = 1; i < k; i++)
    {
        x1 = min_heap.top(), min_heap.pop();
        y1 = min_heap.top(), min_heap.pop();
        ans2 += x1 + y1 - 1;
        min_heap.push(x1 + y1);
        x2 = max_heap.top(), max_heap.pop();
        y2 = max_heap.top(), max_heap.pop();
        ans1 += x2 + y2 - 1;
        max_heap.push(x2 + y2);
    }

    cout << ans1 << ' ' << ans2;
}