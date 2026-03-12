#include <bits/stdc++.h>

using namespace std;

int n, m;

int array_min(vector<int> q,int len){
    int temp = q[0];
    int idx = 0;
    for (int i = 1; i < len;i++){
       if(q[i]<temp){
           temp = q[i];
           idx = i;
       }
    }
    return idx;
}

int main()
{
    cin >> n >> m;
    vector<int> a(n, 0);
    vector<int> wait_time(m, 0);//每个人需要等待的时间
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
       
    }
    int ans = 0;
    sort(a.begin(), a.end());
    for (int i = 0; i < m;i++){
        wait_time[i] = a[i];
        ans += a[i];
    }


    for (int i = m; i < n;i++){
        int idx = array_min(wait_time, m);
        wait_time[idx] = wait_time[idx]  + a[i];
        ans += wait_time[idx];
    }
    cout << ans;
}