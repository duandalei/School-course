#include <bits/stdc++.h>

using namespace std;
int n;
vector<pair<string, int>> q;
bool compare(const pair<string, int> &A, const pair<string, int> &B)
{
    return A.second > B.second || (A.second == B.second && A.first < B.first);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        string str;
        int x;
        cin >> str;
        scanf("%d", &x);
        q.push_back({str, x});
    }
    sort(q.begin(),q.end(),compare);
    for (int i = 0; i < n;i++){
        cout << q[i].first << " " << q[i].second << endl;
    }
    return 0;
}