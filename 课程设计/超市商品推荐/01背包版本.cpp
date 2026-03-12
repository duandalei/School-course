// 基于01背包算法的超市商品推荐

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// 商品结构体
struct Item
{
    int id;           // 商品唯一标识符
    string name;      // 商品名称
    double price;     // 商品价格（单位：元，支持小数）
    int satisfaction; // 商品满意度（整数，用于推荐算法计算）
};

// 超市管理系统类
class SupermarketManager
{
private:
    // ========== 常量定义 ==========
    static const string DATA_FILE;  // 数据文件名
    static const string CSV_HEADER; // csv表头(id,name,price,satisfaction)
    static constexpr double CENTS_PER_YUAN = 100.0;

    // ========== 成员变量 ==========
    vector<Item> items; // 所有商品的完整数据列表
    int nextId = 1;     // 下一个可用的商品ID（自动递增分配）

    // ========== 工具函数 ==========

    // 删除字符串开头和结尾的空格、制表符、回车符、换行符
    static string trim(const string &s)
    {
        size_t b = s.find_first_not_of(" \t\r\n");
        if (b == string::npos)
            return "";
        size_t e = s.find_last_not_of(" \t\r\n");
        return s.substr(b, e - b + 1);
    }

    // 按逗号分割CSV格式的字符串
    static vector<string> splitCsv(const string &line)
    {
        vector<string> cols; // 存储拆分后的字段
        string cur;          // 当前字段的临时存储
        for (char ch : line)
        {
            if (ch == ',')
            {
                cols.push_back(cur);
                cur.clear();
            }
            else
            {
                cur.push_back(ch);
            }
        }
        // 最后一个字段（后面没有逗号）
        cols.push_back(cur);
        return cols;
    }

    // 将元转化为分
    static int yuanToCents(double priceYuan)
    {
        // 使用 std::llround 进行四舍五入，先转为long long避免溢出
        long long cents = std::llround(priceYuan * CENTS_PER_YUAN);
        // 处理负数情况（价格不应为负）
        if (cents < 0)
            cents = 0;
        // 限制在int范围内，避免溢出
        if (cents > std::numeric_limits<int>::max())
            cents = std::numeric_limits<int>::max();
        return (int)cents;
    }

    // ========== 数据管理函数 ==========

    // 根据items列表计算并更新nextId
    void updateNextId()
    {
        int maxId = 0;
        for (const auto &it : items)
            maxId = std::max(maxId, it.id);
        nextId = std::max(maxId + 1, nextId);
    }

    // 检查数据文件是否存在，如果不存在则创建并写入CSV表头
    void ensureFileExistsWithHeader()
    {
        // 检查文件是否存在且可读
        if (ifstream(DATA_FILE).good())
            return; // 文件已存在，直接返回
        // 文件不存在，创建文件并写入CSV表头
        ofstream fout(DATA_FILE);
        if (fout)
        {
            fout << CSV_HEADER; // CSV表头：列名
        }
    }

    // 将内存中的items列表写入CSV文件
    void saveAll()
    {
        // 以覆盖模式打开文件（ios::trunc表示清空原文件内容）
        ofstream fout(DATA_FILE, ios::out | ios::trunc);
        if (!fout)
        {
            cerr << "写入文件失败: " << DATA_FILE << "\n";
            return;
        }
        // 写入CSV表头
        fout << CSV_HEADER;
        // 设置浮点数输出格式：固定小数点，保留2位小数
        fout.setf(std::ios::fixed);
        fout << setprecision(2);
        // 遍历所有商品，逐行写入
        for (const auto &it : items)
        {
            fout << it.id << "," << it.name << "," << it.price << ","
                 << it.satisfaction << "\n";
        }
    }

    // 从CSV文件中读取所有商品数据到内存
    void loadAll()
    {
        items.clear();                // 清空现有商品列表
        ensureFileExistsWithHeader(); // 确保文件存在
        ifstream fin(DATA_FILE);      // 打开文件准备读取

        if (!fin)
        {
            cerr << "无法打开数据文件: " << DATA_FILE << "\n";
            nextId = 1; // 文件打开失败，重置nextId
            return;
        }

        string line;
        bool header = true; // 标记是否为第一行（表头）
        // 逐行读取文件
        while (std::getline(fin, line))
        {
            line = trim(line); // 去除首尾空白
            if (line.empty())
                continue; // 跳过空行
            // 跳过第一行表头
            if (header)
            {
                header = false;
                continue;
            }
            // 按逗号分割CSV行
            auto cols = splitCsv(line);
            if (cols.size() < 4)
                continue; // 字段不足4个，跳过此行

            Item it;
            try
            {
                // 解析各字段（使用try-catch处理格式错误）
                it.id = std::stoi(trim(cols[0]));           // 商品ID（整数）
                it.name = trim(cols[1]);                    // 商品名称（字符串）
                it.price = std::stod(trim(cols[2]));        // 商品价格（浮点数）
                it.satisfaction = std::stoi(trim(cols[3])); // 满意度（整数）
            }
            catch (...)
            {
                // 解析失败，跳过此行（格式错误）
                continue;
            }
            items.push_back(it);
        }
        // 加载完成后，更新nextId以确保正确性
        updateNextId();
    }

    // ========== 核心功能函数 ==========

    // 添加商品（或更新同名商品）
    void addItem()
    {
        cout << "输入商品名称: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string name;
        std::getline(cin, name); // 读取完整行（支持带空格的名称）
        name = trim(name);       // 去除首尾空白
        if (name.empty())
        {
            cout << "名称不能为空\n";
            return;
        }

        // 输入价格（循环直到输入有效）
        double price;
        while (true)
        {
            cout << "输入价格(元, 可含小数): ";
            if (cin >> price)
            {
                break;
            }
            else
            {
                cout << "⚠️ 价格输入无效，请输入数字\n";
                cin.clear();                                         // 让 cin 可以继续工作
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清理输入缓冲区的垃圾字符
            }
        }

        // 输入满意度（循环直到输入有效）
        int satisfaction;
        while (true)
        {
            cout << "输入满意度(整数): ";
            if (cin >> satisfaction)
            {
                break;
            }
            else
            {
                cout << "⚠️ 满意度输入无效，请输入整数\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // 检查是否已存在同名商品
        for (auto &existing : items)
        {
            if (existing.name == name)
            {
                // 名称已存在，比较价格和满意度
                const double EPS = 1e-6; // 浮点数比较精度（避免精度误差）
                // 如果价格和满意度完全相同，不修改
                if (std::abs(existing.price - price) < EPS && existing.satisfaction == satisfaction)
                {
                    cout << "ℹ️ 商品 \"" << name << "\" 已存在，且价格和满意度完全相同，无需修改\n";
                    return;
                }
                else
                {
                    // 数据不同，更新已有商品的价格和满意度
                    existing.price = price;
                    existing.satisfaction = satisfaction;

                    saveAll(); // 保存到文件
                    cout << "✅ 已更新商品 \"" << name << "\" (ID: " << existing.id << ") 的价格和满意度\n";
                    return;
                }
            }
        }

        // 不存在同名商品，创建新商品
        Item it;
        it.id = nextId++; // 分配新的唯一ID并自增
        it.name = name;
        it.price = price;
        it.satisfaction = satisfaction;

        items.push_back(it); // 添加到商品列表

        saveAll(); // 保存到文件
        cout << "✅ 已录入,分配ID: " << it.id << "\n";
    }

    // 显示所有商品的信息
    void listItems() const
    {
        if (items.empty())
        {
            cout << "暂无商品\n";
            return;
        }
        cout << "--- 商品列表 ---\n";
        // 输出表头（左对齐，设置列宽）
        cout << left << setw(5) << "ID" << setw(30) << "名称" << setw(10) << "价格(元)" << "满意度\n";
        for (const auto &it : items)
        {
            cout << left << setw(5) << it.id << setw(30) << it.name << setw(10) << it.price << it.satisfaction << "\n";
        }
    }

    // 根据商品ID删除指定商品

    void deleteItem()
    {
        int id;
        while (true)
        {
            cout << "输入要删除的商品ID: ";
            if (cin >> id)
            {
                break;
            }
            else
            {
                cout << "⚠️ 输入无效，请输入数字\n";
                cin.clear();                                         // 清除错误标志
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩余字符
            }
        }

        // 使用std::remove_if将匹配的元素移动到容器末尾
        // remove_if返回新的逻辑末尾迭代器
        auto it = std::remove_if(items.begin(), items.end(), [&](const Item &x)
                                 { return x.id == id; });

        // 检查是否找到要删除的商品
        if (it == items.end())
        {
            cout << "未找到该ID\n";
            return;
        }
        items.erase(it, items.end());
        // 删除商品后，更新nextId
        updateNextId();
        saveAll(); // 保存到文件
        cout << "✅ ID=" << id << " 的商品已删除\n";
    }

    // 根据商品ID修改商品的名称、价格或满意度
    void modifyItem()
    {
        int id;
        while (true)
        {
            cout << "输入要修改的商品ID: ";
            if (cin >> id)
            {
                break;
            }
            else
            {
                cout << "⚠️ 输入无效，请输入数字\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // 遍历查找指定ID的商品
        for (auto &it : items)
        {
            if (it.id == id)
            {
                // 显示当前商品信息
                cout << "当前: 名称=" << it.name << " 价格=" << it.price << " 满意度=" << it.satisfaction << "\n";
                // 前面可能有 cin >> id =>留下一个换行符 \n 在输入缓冲区
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "新名称(留空则不改): ";
                string newName;
                std::getline(cin, newName); // getline会读走'\n',所以后面不需要cin.ignore
                newName = trim(newName);
                if (!newName.empty()) // 非空则更新
                    it.name = newName;

                // --- 修改价格 ---
                cout << "新价格(元, 直接回车不改): ";
                string priceLine;
                std::getline(cin, priceLine);
                priceLine = trim(priceLine);
                if (!priceLine.empty())
                {
                    try
                    {
                        it.price = std::stod(priceLine);
                    }
                    catch (...)
                    {
                        // 转换失败，保持原价格
                        cout << "⚠️ 价格无效，保持不变\n";
                    }
                }

                // --- 修改满意度 ---
                cout << "新满意度(整数, 直接回车不改): ";
                string satLine;
                std::getline(cin, satLine);
                satLine = trim(satLine);
                if (!satLine.empty())
                {
                    try
                    {
                        it.satisfaction = std::stoi(satLine);
                    }
                    catch (...)
                    {
                        // 转换失败，保持原满意度
                        cout << "⚠️ 满意度无效，保持不变\n";
                    }
                }

                saveAll();
                cout << "✅ 已修改商品 ID=" << id << "\n";
                return;
            }
        }
        cout << "未找到该ID\n";
    }

    // 根据名称关键词搜索商品
    void searchItems() const
    {
        cout << "按名称关键词搜索，输入关键词: ";
        // 前面可能有 cin >> id =>留下一个换行符 \n 在输入缓冲区
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string key;
        std::getline(cin, key);
        key = trim(key);
        if (key.empty())
        {
            cout << "关键词为空\n";
            return;
        }

        bool any = false; // 标记是否找到匹配商品
        for (const auto &it : items)
        {
            // 使用string::find查找子串（string::npos表示未找到）
            if (it.name.find(key) != string::npos)
            {
                // 如果是第一个匹配的商品，输出表头
                if (!any)
                {
                    cout << "--- 匹配结果 ---\n";
                    cout << left << setw(5) << "ID" << setw(30) << "名称" << setw(10) << "价格(元)" << "满意度\n";
                }
                any = true;
                cout << left << setw(5) << it.id << setw(30) << it.name << setw(10) << it.price << it.satisfaction << "\n";
            }
        }
        // 未找到任何匹配商品
        if (!any)
            cout << "未找到匹配商品\n";
    }

    // 推荐购买方案（完全背包问题）
    void recommendPlan() const
    {
        if (items.empty())
        {
            cout << "暂无商品，无法推荐\n";
            return;
        }

        double budgetYuan;
        while (true)
        {
            cout << "输入预算金额(元): ";
            if ((cin >> budgetYuan) && budgetYuan > 0)
            {
                break;
            }
            else
            {
                cout << "⚠️ 预算输入无效或必须大于0\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        vector<int> wgt;      // 商品价格（单位：分），作为背包问题中的"重量"
        vector<int> val;      // 商品满意度，作为背包问题中的"价值"
        vector<string> names; // 对应的商品名称（避免后续重复查找）

        for (const auto &it : items)
        {
            int cents = yuanToCents(it.price); // 将价格从元转换为分
            if (cents <= 0)
                continue;
            wgt.push_back(cents);
            val.push_back(it.satisfaction);
            names.push_back(it.name);
        }

        // 检查是否有有效商品
        if (wgt.empty())
        {
            cout << "商品价格无效，无法计算\n";
            return;
        }

        int cap = yuanToCents(budgetYuan);
        vector<int> dp(cap + 1, 0);

        // 使用二维bool数组记录路径，因为0/1背包不能用一维数组简单回溯
        //  picked[i][c] = true 表示在考虑第i个商品、容量为c时，选择了该商品
        vector<vector<bool>> picked(wgt.size(), vector<bool>(cap + 1, false));

        // 外层循环：遍历每个商品
        for (int i = 0; i < (int)wgt.size(); i++)
        {
            for (int c = cap; c >= wgt[i]; c--)
            {
                int alt = dp[c - wgt[i]] + val[i];
                if (alt > dp[c])
                {
                    dp[c] = alt;
                    picked[i][c] = true;
                }
            }
        }

        int maxSat = dp[cap];
        vector<int> countPerIndex(wgt.size(), 0);
        int currentCap = cap;

        // 倒序遍历商品，通过 picked 数组还原选择
        for (int i = wgt.size() - 1; i >= 0; i--)
        {
            // 如果当前容量下记录了选择了商品 i
            if (currentCap >= wgt[i] && picked[i][currentCap])
            {
                countPerIndex[i] = 1; // 0/1背包数量固定为 1
                currentCap -= wgt[i];
            }
        }

        double totalCostCents = (double)(cap - currentCap);
        // 转换为元
        double totalCostYuan = totalCostCents / CENTS_PER_YUAN;
        cout << "\n========== 🛒 推荐购买方案 ==========" << "\n";
        cout << "最大满意度: " << maxSat << "\n";
        cout << "推荐购买:" << "\n";
        bool purchased = false; // 标记是否购买了商品
        // 遍历所有商品，输出购买数量大于0的商品
        for (int i = 0; i < (int)countPerIndex.size(); i++)
        {
            if (countPerIndex[i] > 0)
            {
                purchased = true;
                string name = names[i];
                double cost = (double)wgt[i] * countPerIndex[i] / CENTS_PER_YUAN;
                cout << "  - " << name << " x " << countPerIndex[i] << " (小计 " << cost << " 元)\n";
            }
        }
        if (!purchased)
        {
            cout << "  - (未购买任何商品，可能是预算过低)\n";
        }

        cout << "总花费: " << totalCostYuan << " 元\n";
        cout << "剩余预算: " << std::max(0.0, budgetYuan - totalCostYuan) << " 元\n";
        cout << "======================================\n";
    }

public:
    SupermarketManager()
    {
        loadAll(); // 构造时自动加载所有数据
    }

    void menuLoop()
    {
        // 无限循环，直到用户选择退出
        for (;;)
        {
            cout << "\n========== 🛍️ 超市商品推荐系统 ==========" << "\n";
            cout << "1. 商品录入\n";
            cout << "2. 浏览商品\n";
            cout << "3. 删除商品\n";
            cout << "4. 修改商品\n";
            cout << "5. 搜索商品\n";
            cout << "6. 推荐购买方案 (01背包)\n";
            cout << "0. 退出\n";
            cout << "========================================\n";
            cout << "请选择功能(0-6): " << std::flush;

            int op;
            while (true)
            {
                if (cin >> op)
                {
                    break;
                }
                cerr << "⚠️ 输入无效，请重新输入数字\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "请选择功能(0-6): " << std::flush;
            }

            switch (op)
            {
            case 1:
                addItem(); // 添加商品
                break;
            case 2:
                listItems(); // 列出所有商品
                break;
            case 3:
                deleteItem(); // 删除商品
                break;
            case 4:
                modifyItem(); // 修改商品
                break;
            case 5:
                searchItems(); // 搜索商品
                break;
            case 6:
                recommendPlan(); // 推荐购买方案
                break;
            case 0:
                // 退出程序
                cout << "👋 感谢使用，再见!\n";
                return; // 退出循环，程序结束
            default:
                // 无效选择（不在0-6范围内）
                cout << "无效选择\n";
                break;
            }
        }
    }
};

const string SupermarketManager::DATA_FILE = "商品目录.txt";
const string SupermarketManager::CSV_HEADER = "id,name,price,satisfaction\n";

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cout.setf(std::ios::unitbuf); // 设置 unitbuf 后，每次输出操作后立即刷新缓冲区，输出会立即显示;

    cout.setf(std::ios::fixed); // 统一设置输出格式
    cout << setprecision(2);    // 固定小数点，保留2位小数

    SupermarketManager manager;
    manager.menuLoop();
    return 0;
}
