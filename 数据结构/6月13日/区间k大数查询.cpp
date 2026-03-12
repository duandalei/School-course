#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int left, right, k;
        scanf("%d %d %d", &left, &right, &k);
        vector<int> current;
        for (int j = left - 1; j < right; j++)
        {
            current.push_back(a[j]);
        }
        sort(current.begin(), current.end());
        printf("%d\n", current[current.size() - k]);
    }
    return 0;
}

// #include<bits/stdc++.h>
// using namespace std;
// int n,m;
// int a[1001];
// set<int> q;
// int main(){
//     scanf("%d",&n);
//     for (int i = 0; i < n;i++){
//         scanf("%d", &a[i]);
//     }
//     scanf("%d",&m);
//     for (int i = 0; i < m;i++){
//         q.clear();
//         int x,y,z;
//         scanf("%d%d%d",&x,&y,&z);
//         for (int j = x - 1; j < y;j++){
//             q.insert(a[j]);
//         }
//         for (int k = 1; k <= (y - x + 1 - z);k++){
//             q.erase(q.begin());
//         }
//         int target = *q.begin();
//         printf("%d\n", target);
//     }
// }