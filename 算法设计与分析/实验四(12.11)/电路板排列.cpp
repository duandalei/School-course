#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// 结构体定义
struct State
{
    std::vector<int> live_board; // live_board[i]：第i个插槽放置的电路板编号 (1-based index)
    int k;                       // 当前已确定的插槽数量 (已放置的电路板数量)
    int max_len;                 // 当前最大长度
    // 构造函数
    State(int n) : live_board(n + 1, 0), k(0), max_len(0) {}
    // 拷贝构造函数，方便状态复制
    State(const State &other) = default;
};

// 核心函数：计算当前排列的最大连接块长度
int calculate_max_len(const State &S, int n, int m, const std::vector<std::vector<int>> &Conn)
{
    int current_max_len = 0;

    // 遍历所有连接块 j (1 到 m)
    for (int j = 1; j <= m; ++j)
    {
        int min_slot = n + 1; // 最小插槽编号
        int max_slot = 0;     // 最大插槽编号
        bool has_board = false;

        // 遍历已放置的电路板 (插槽 1 到 S.k)
        for (int slot = 1; slot <= S.k; ++slot)
        {
            int board_id = S.live_board[slot];

            // 检查电路板 board_id 是否在连接块 j 中
            if (Conn[board_id][j] == 1)
            {
                min_slot = std::min(min_slot, slot);
                max_slot = std::max(max_slot, slot);
                has_board = true;
            }
        }

        if (has_board)
        {
            int len = max_slot - min_slot + 1;
            current_max_len = std::max(current_max_len, len);
        }
    }
    return current_max_len;
}

/**
 * 队列式分支限界法求解最小长度电路板排列
 */
int solve_min_length_arrangement(int n, int m, const std::vector<std::vector<int>> &Conn, std::vector<int> &best_permutation)
{

    int best_max_len = n + 1; // 全局最优：最小最大长度

    // 队列存储待扩展的活节点
    std::queue<State> Q;

    // 根节点：一个空的排列
    State root_state(n);
    Q.push(root_state);

    while (!Q.empty())
    {
        State current_state = Q.front();
        Q.pop();

        // 1. 检查是否为叶节点 (已完成一个完整的排列)
        if (current_state.k == n)
        {
            if (current_state.max_len < best_max_len)
            {
                best_max_len = current_state.max_len;
                best_permutation.assign(current_state.live_board.begin() + 1, current_state.live_board.end());
            }
            continue;
        }

        // 2. 分支：尝试将下一块未放置的电路板放入下一个插槽 (slot = k + 1)
        int next_slot = current_state.k + 1;

        // 记录哪些电路板已经被放置
        std::vector<bool> placed(n + 1, false);
        for (int i = 1; i <= current_state.k; ++i)
        {
            placed[current_state.live_board[i]] = true;
        }

        // 遍历所有未放置的电路板 board_id (1 到 n)
        for (int board_id = 1; board_id <= n; ++board_id)
        {
            if (!placed[board_id])
            {
                // 生成新状态 (子节点)
                State next_state = current_state;
                next_state.live_board[next_slot] = board_id;
                next_state.k = next_state.k + 1;

                // 计算新状态的最大长度
                next_state.max_len = calculate_max_len(next_state, n, m, Conn);

                // 限界：如果当前最大长度 < 全局最优，则入队
                if (next_state.max_len < best_max_len)
                {
                    Q.push(next_state);
                }
                // 如果 next_state.max_len == best_max_len，也可以入队以寻找其他最优排列，
                // 但为了效率和遵循严格的限界，我们在此只保留 < 的情况（除非 k=n）。
            }
        }
    }

    return best_max_len;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    if (!(std::cin >> n >> m))
        return 0;

    std::vector<std::vector<int>> Conn(n + 1, std::vector<int>(m + 1));

    // 读取输入数据
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            std::cin >> Conn[i][j];
        }
    }

    std::vector<int> best_p;
    int min_max_len = solve_min_length_arrangement(n, m, Conn, best_p);

    // 输出结果 (该程序对于您的输入将返回 5，并输出对应的排列)
    std::cout << min_max_len << "\n";
    for (size_t i = 0; i < best_p.size(); ++i)
    {
        std::cout << best_p[i] << (i == best_p.size() - 1 ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}