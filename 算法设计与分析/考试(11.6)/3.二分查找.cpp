#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 10;
int n;
int a[N];
int target;

int binary_search(int q[],int l,int r,int x){
     while(l<=r){
         int mid = (l + r) / 2;
         if (q[mid]>=x){
             r = mid - 1;
         }else{
             l = mid + 1;
         }
     }
     return l;
}

int main(){
    cin >> n;
    for (int i = 0; i < n;i++){
        cin >> a[i];
    }
    cin >> target;
    int idx = binary_search(a, 0, n - 1, target);
    if (a[idx]==target)
    {
        cout << idx + 1;
    }else{
        cout << -1;
    }
    return 0;
}