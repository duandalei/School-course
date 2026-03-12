// #include<bits/stdc++.h>

// using namespace std;
// vector<pair<int,int>> q;
// int n;
// int main(){
//     scanf("%d",&n);
//     for(int i=0;i<n;i++){
//         int x,y;
//         scanf("%d%d",&x,&y);
//         q.push_back({x, y});
//     }
//     int length = 0;
//     for(int i=0;i<n;i++){
//       for(int j=i+1;j<n;j++){
//         int a=abs(q[i].first-q[j].first);
//         int b = abs(q[i].second - q[j].second);
//         length = max(length, a + b);
//       }
//     }
//     cout << length;
// }
//曼哈顿距离的特性


#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> x(n), y(n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &x[i], &y[i]);
    }

    int max_sum = INT_MIN, min_sum = INT_MAX;
    int max_diff = INT_MIN, min_diff = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        max_sum = max(max_sum, x[i] + y[i]);
        min_sum = min(min_sum, x[i] + y[i]);
        max_diff = max(max_diff, x[i] - y[i]);
        min_diff = min(min_diff, x[i] - y[i]);
    }

    cout << max(max_sum - min_sum, max_diff - min_diff);
    return 0;
}



/*

xi ≥ xj 且 yi ≥ yj
|xi - xj| + |yi - yj| = (xi - xj) + (yi - yj) = (xi + yi) - (xj + yj)

情况 2：
xi ≥ xj 且 yi < yj
|xi - xj| + |yi - yj| = (xi - xj) + (yj - yi) = (xi - yi) - (xj - yj)

情况 3：
xi < xj 且 yi ≥ yj
|xi - xj| + |yi - yj| = (xj - xi) + (yi - yj) = (xj - yj) - (xi - yi)

情况 4：
xi < xj 且 yi < yj
|xi - xj| + |yi - yj| = (xj - xi) + (yj - yi) = (xj + yj) - (xi + yi)


*/