#include <bits/stdc++.h>
using namespace std;

int n, c;
int a[10010];
bool choice[10010];
bool temp = false;
int suffix[10010]; // 后缀和

void dfs(int start, int total)
{
    if (temp)
        return; // 剪枝3：已找到解

    if (total == c)
    {
        temp = true;
        for (int i = 1; i <= n; i++)
        {
            if (choice[i])
                cout << a[i] << ' ';
        }
        return;
    }

    if (total > c)
        return; // 剪枝1：超过目标(正整数集合,再往下只会更大)

    if (start <= n && total + suffix[start] < c)
        return; // 剪枝2：剩余不可能达到

    for (int i = start; i <= n; i++)
    {
        choice[i] = true;
        dfs(i + 1, total + a[i]);
        choice[i] = false;
    }
}

int main()
{
    cin >> n >> c;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    // 计算后缀和
    suffix[n + 1] = 0;
    for (int i = n; i >= 1; i--)
        suffix[i] = suffix[i + 1] + a[i];

    dfs(1, 0);

    if (!temp)
        cout << "No Solution!";

    return 0;
}
