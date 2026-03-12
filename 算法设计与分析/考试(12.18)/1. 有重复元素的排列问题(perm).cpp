#include <bits/stdc++.h>
using namespace std;

string s;
bool used[505];
vector<char> path;
long long cnt = 0;

void dfs()
{
    if (path.size() == s.size())
    {
        for (char c : path)
            cout << c;
        cout << "\n";
        cnt++;
        return;
    }

    for (int i = 0; i < s.size(); i++)
    {
        if (used[i])
            continue;
        if (i > 0 && s[i] == s[i - 1] && !used[i - 1])
            continue;

        used[i] = true;
        path.push_back(s[i]);
        dfs();
        path.pop_back();
        used[i] = false;
    }
}

int main()
{
    int n;
    cin >> n >> s;
    sort(s.begin(), s.end());
    dfs();
    cout << cnt;
}
