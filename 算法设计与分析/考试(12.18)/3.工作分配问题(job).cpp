#include <bits/stdc++.h>
using namespace std;

int n;
int c[21][21];
int dp[1 << 20];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> c[i][j];

    int N = 1 << n;
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int mask = 0; mask < N; mask++)
    {
        int p = __builtin_popcount(mask);
        for (int j = 0; j < n; j++)
        {
            if (!(mask & (1 << j)))
            {
                dp[mask | (1 << j)] =
                    min(dp[mask | (1 << j)],
                        dp[mask] + c[p][j]);
            }
        }
    }

    cout << dp[N - 1];
}
