#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> path;

// remain：还剩多少需要拆
// last：下一个数最小可以取多少（保证不递减）
void dfs(int remain, int last)
{
    if (remain == 0 && path.size()>1)
    {
        // 输出一种拆分
        for (int i = 0; i < path.size(); i++)
        {
            if (i > 0)
                cout << "+";
            cout << path[i];
        }
        cout << endl;
        return;
    }

    // 枚举下一个拆分的数
    for (int i = last; i <= remain; i++)
    {
        path.push_back(i);
        dfs(remain - i, i);
        path.pop_back(); // 回溯
    }
}

int main()
{
    cin >> n;
    // 从 1 开始拆，最大值不超过 n-1
    dfs(n, 1);

    return 0;
}
