#include<bits/stdc++.h>

using namespace std;

int n, m;

int main(){
    cin >> n >> m;
    vector<int> a(n,0);
    vector<int> b(m,0);
    int ans = 0;
    for (int i = 0; i < n;i++){
        cin >> a[i] ;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n && i < m;i++){
        b[i] = a[i];
        ans += a[i];
    }
    for (int i = m; i < n;i++){
        
        sort(b.begin(),b.end());
        ans += b[0] + a[i];
        b[0] += a[i];
    }
    cout << ans;
}