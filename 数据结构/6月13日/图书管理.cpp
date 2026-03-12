#include<bits/stdc++.h>
using namespace std;
int n;
vector<string> q;
string str;
int main(){
    scanf("%d",&n);
    string name;
    for (int i = 0; i < n;i++){
        cin >> str;
        if(str=="add"){
            cin >> name;
            q.push_back(name);
        }
        if(str=="find"){
            cin >> name;
            int has = 0;
            for (int k = 0; k < q.size();k++){
                if(name==q[k]){
                    has = 1;
                    break;
                }  
            }
            if(!has)  printf("no\n");
            else  printf("yes\n");
        }
    }
}