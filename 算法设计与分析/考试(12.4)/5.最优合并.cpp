#include <bits/stdc++.h>

using namespace std;

priority_queue<int, vector<int>, greater<int>> heap_min;
priority_queue<int, vector<int>> heap_max;

int n;
int num;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        heap_min.push(num);
        heap_max.push(num);
    }
    int res1 = 0, res2 = 0;
    int temp1 = 0, temp2 = 0, temp3 = 0;
    for (int i = 1; i < n; i++)
    {
        temp1 = heap_max.top(), heap_max.pop();
        temp2 = heap_max.top(), heap_max.pop();
        temp3 = temp1 + temp2;
        res1 += temp3 - 1;
        heap_max.push(temp3);
    }
    for (int i = 1; i < n; i++)
    {
        temp1 = heap_min.top(), heap_min.pop();
        temp2 = heap_min.top(), heap_min.pop();
        temp3 = temp1 + temp2;
        res2 += temp3 - 1;
        heap_min.push(temp3);
    }
    cout << res1 << '\n'
         << res2;
}