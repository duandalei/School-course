#include <bits/stdc++.h>

using namespace std;

int path[10];
int n;
bool on_path[10];
void pailie(int k)
{
    if (k == n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << path[i] << ' ';
        }
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (on_path[i])
            continue;
        path[k] = i;
        on_path[i] = true;
        pailie(k + 1);
        on_path[i] = false;
    }
}

int main()
{
    memset(on_path, false, sizeof(on_path));
    cin >> n;
    pailie(0);
    return 0;
}
