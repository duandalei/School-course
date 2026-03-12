#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[100000];
int main(){
    scanf("%d%d",&n,&q);
    for (int i = 0; i < n;i++)
        scanf("%d", &a[i]);
    for (int i = 0;i<q;i++){
        int x;
        scanf("%d", &x);
        int left=0,right=n-1;
        int left_idx=-1, right_idx=-1;
        while(left<=right){
            int mid=(left+right)/2;
            if(a[mid]>=x){
                right = mid - 1;
                if(a[mid]==x)
                    left_idx = mid;
            }
            else
                left = mid + 1;
        }
        left=0,right=n-1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (a[mid] > x)
                right = mid - 1;
            else
            {
                if(a[mid]==x) right_idx = mid;
                left = mid + 1;
            }
        }
        if(left_idx!=-1)  printf("%d %d\n", left_idx, right_idx);
        else printf("-1 -1\n");
    }
}