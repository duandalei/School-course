#include <bits/stdc++.h>
#define int long long

using namespace std;

int x, y, z;
int fast(int base, int e, int mod)
{
    int res = 1;
    base = base % mod;
    while (e > 0)
    {
        if (e % 2 == 1)
        {
            res = res * base % mod;
        }
        base = (base * base) % mod;
        e = e / 2;
    }
    return res;
}

signed main()
{
    cin >> x >> y >> z;

    int ans = fast(x, y, z);

    printf("%lld^%lld mod %lld=%lld", x, y, z, ans);
    return 0;
}