#include <iostream>
#include <vector>

using namespace std;

// 全局变量定义
int n;                // 迷宫大小
int maze[15][15];     // 迷宫地图 0:通 1:阻
bool visited[15][15]; // 访问标记
int totalPaths = 0;   // 路径总数计数器

// 定义8个方向的偏移量 (行, 列)
// 分别对应：左上, 上, 右上, 左, 右, 左下, 下, 右下
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 检查坐标是否在迷宫范围内且合法
bool isValid(int x, int y)
{
    // 1. 越界检查
    if (x < 0 || x >= n || y < 0 || y >= n)
        return false;
    // 2. 障碍物检查 (1 表示不可通过)
    if (maze[x][y] == 1)
        return false;
    // 3. 是否已访问检查
    if (visited[x][y])
        return false;

    return true;
}

// 深度优先搜索
void dfs(int x, int y)
{
    // 【基本情况】：到达终点 (右上角：行0，列n-1)
    if (x == 0 && y == n - 1)
    {
        totalPaths++;
        return;
    }

    // 尝试 8 个方向
    for (int i = 0; i < 8; ++i)
    {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if (isValid(nextX, nextY))
        {
            // 【标记】：设为已访问
            visited[nextX][nextY] = true;

            // 【递归】：进入下一层
            dfs(nextX, nextY);

            // 【回溯】：恢复为未访问，以便其他路径尝试
            visited[nextX][nextY] = false;
        }
    }
}

int main()
{
    // 1. 输入处理
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> maze[i][j];
            visited[i][j] = false; // 初始化访问数组
        }
    }


    // 标记起点并开始 DFS
    visited[0][0] = true;
    dfs(0, 0); // 从 (0,0) 开始

    // 3. 输出结果
    cout << totalPaths << endl;

    return 0;
}
