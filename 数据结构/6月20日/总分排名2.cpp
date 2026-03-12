#include<bits/stdc++.h>

using namespace std;
int n;
string name;
struct node{
    string str;
    int x, y, z;
    int total,rank,origin;
    node(string _str,int _x,int _y,int _z,int _total,int _origin){
        str=_str;
        x = _x, y = _y, z = _z;
        total = _total;
        origin = _origin;
    }
};
bool compare(const node &A,const node &B){
    return A.total > B.total ||(A.total==B.total&&A.origin<B.origin);
}
vector<node> student;
int main(){
    cin >> n >> name;
    for(int i=0;i<n;i++){
        string s;
        int a,b,c;
        cin >> s >> a >> b >> c;
        int sum = a + b + c;
        student.push_back(node(s, a, b, c,sum,i));
    }
    sort(student.begin(),student.end(),compare);
   
    student[0].rank = 1;
    for(int i=1;i<n;i++){
         if(student[i].total==student[i-1].total){
             student[i].rank =student[i-1].rank;
         }else{
             student[i].rank = i + 1;
         }
         
    }
    int sum;
    for (int i = 0; i < n; i++)
    {
        if (student[i].str == name)
        {
            sum = student[i].total;
            printf("%d %d\n", student[i].total, student[i].rank);
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (student[i].total==sum)
        {
            cout << student[i].str <<endl;
        }
    }
    return 0;
}