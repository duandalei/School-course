#include <bits/stdc++.h>

using namespace std;

int n;

struct act
{
    int start;
    int end;
};

bool compare(const act &A, const act &B)
{
    return A.start < B.start;
}

int main()
{
    cin >> n;
    vector<act> activaty(n);
    for (int i = 0; i < n; i++)
    {
        cin >> activaty[i].start >> activaty[i].end;
    }
    sort(activaty.begin(), activaty.end(), compare);
    priority_queue<int, vector<int>, greater<int>> heap_min;
    heap_min.push(activaty[0].end);
    for (int i = 1; i < n; i++)
    {
        int finish = heap_min.top();
        if (finish <= activaty[i].start)
        {
            heap_min.pop();
            heap_min.push(activaty[i].end);
        }
        else
        {
            heap_min.push(activaty[i].end);
        }
    }
    cout << (int)heap_min.size();
}