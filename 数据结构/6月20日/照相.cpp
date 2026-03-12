#include<bits/stdc++.h>

using namespace std;

int n;
vector<int> q1;
vector<int> q2;
bool compare1 (int X,int Y){
    return X < Y;
}
bool compare2(int X, int Y)
{
    return X > Y;
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int x;
        scanf("%d",&x);
        if(x%2!=0) q1.push_back(x);
        else  q2.push_back(x);
    }
    sort(q1.begin(),q1.end(),compare1);
    sort(q2.begin(),q2.end(),compare2);
    int total1 = q1.size();
    for (int i = 0; i < total1;i++){
        printf("%d ", q1[i]);
    }
    int total2=q2.size();
    for (int i = 0; i < total2;i++){
        printf("%d ", q2[i]);
    }
}