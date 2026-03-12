#include <bits/stdc++.h>
using namespace std;

int main()
{
    int w, n;
    cin >> w >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a.begin(), a.end());

    int left = 0, right = n - 1;
    int res = 0;

    while (left <= right)
    {
        if (a[left] + a[right] <= w)
        {
            left++;
            right--;
        }
        else
        {
            // 只能右边自己用一组
            right--;
        }
        res++;
    }

    cout << res;
    return 0;
}
