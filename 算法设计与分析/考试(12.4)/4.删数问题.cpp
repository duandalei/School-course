#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    int n;
    cin >> s >> n;
    vector<char> st;
    for (char c : s)
    {
        while (!st.empty() && n > 0 && st.back() > c)
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
    
    //删除前导0
    int i = 0;
    while (i <(int) st.size() && st[i] == '0')
    {
        i++;
    }

    if (i ==(int) st.size())
    {
        cout << 0;
    }
    else
    {
        for (; i <(int) st.size(); i++)
            cout << st[i];
    }

    return 0;
}