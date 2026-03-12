#include <bits/stdc++.h>

using namespace std;

double a, b, c, d;

double f(double x)
{
    return a * x * x * x + b * x * x + c * x + d;
}

int main()
{
    cin >> a >> b >> c >> d;
    for (double i = -101; i <= 101; i++)
    {
        if (f(i) == 0)
        {
            printf("%.2lf ", i);
        }
        if (f(i) * f(i + 1) >= 0)
        {
            continue;
        }
        double l = i, r = i + 1;
        while (l < r)
        {
            double mid = (l + r) / 2;
            if (abs(f(mid)) < 0.001)
            {
                printf("%.2lf ", mid);
                break;
            }
            if (f(mid) * f(i) < 0)
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }
    }
    return 0;
}