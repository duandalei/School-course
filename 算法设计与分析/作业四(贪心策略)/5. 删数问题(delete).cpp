#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    int n;
    cin >> s >> n;

    vector<char> st; // 单调栈
    for (char c : s)
    {
        while (!st.empty() && st.back() > c && n > 0)
        {
            st.pop_back();
            n--;
        }
        st.push_back(c);
    }

    // 如果还没删够，从右侧继续删
    while (n > 0)
    {
        st.pop_back();
        n--;
    }

    // 去前导零
    int i = 0;
    while (i < st.size() && st[i] == '0')
        i++;

    if (i == st.size())
    {
        cout << 0;
    }
    else
    {
        for (; i < st.size(); i++)
            cout << st[i];
    }

    return 0;
}
