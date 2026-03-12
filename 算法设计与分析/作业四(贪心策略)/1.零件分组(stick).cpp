#include <bits/stdc++.h>
using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<pair<int, int>> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i].first >> a[i].second;
    }
    // 按 L 升序，L 相等时 W 升序
    sort(a.begin(), a.end(), [](const pair<int, int> &p1, const pair<int, int> &p2)
         {
        if(p1.first != p2.first) return p1.first < p2.first;
        return p1.second < p2.second; });

    // 我们用耐心排序：保存每个长度的尾元素（使尾元素尽可能小/大以便扩展）
    vector<int> tails; // tails[k] = 长度为 k+1 的下降序列的最小“开头”

    for (auto &pr : a)
    {
        int W = pr.second;

        // 找到第一个  <= W 的位置
        auto it = lower_bound(tails.begin(), tails.end(), W, greater<int>()); 
        if (it == tails.end())
            tails.push_back(W);
        else
            *it = W;
    }

    cout << (int)tails.size() << '\n';
    return 0;
}
