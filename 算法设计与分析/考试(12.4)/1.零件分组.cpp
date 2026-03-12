#include <bits/stdc++.h>
using namespace std;

struct Stick
{
    int L, W;
};

bool compare(const Stick &A,const Stick &B){
    if(A.L!=B.L) return A.L < B.L;
    return A.W < B.W;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Stick> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i].L >> a[i].W;
    }

    sort(a.begin(), a.end(), compare);
    vector<int> tails;
    for (auto &s : a)
    {
        int W = s.W;
        auto it = lower_bound(tails.begin(), tails.end(), W, greater<int>());
        if (it == tails.end())
            tails.push_back(W);
        else
            *it = W;
    }

    cout << tails.size() << '\n';
    return 0;
}
