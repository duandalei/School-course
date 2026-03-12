#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

// ===============================
// 常量定义
// ===============================
#define MAX_STATIONS 500             // 最大站点数
#define MAX_LINES 30                 // 最大线路数
#define FILE_NAME "成都地铁路径.txt" // 文件名
#define INF 0x3f3f3f3f               // 无穷大（用于Dijkstra算法）

// ===============================
// 数据结构定义
// ===============================
/**
 * 站点结构体
 */
typedef struct {
  char name[50];           // 站点名称
  int line_ids[MAX_LINES]; // 所属线路ID列表
  int line_count;          // 线路数量
  int id;                  // 唯一编号
} Station;

// ===============================
// 全局变量
// ===============================
Station stations[MAX_STATIONS];             // 站点数组
int station_count = 0;                      // 实际站点数
int adj_matrix[MAX_STATIONS][MAX_STATIONS]; // 邻接矩阵
int dist[MAX_STATIONS];                     // Dijkstra算法的距离数组
int pre[MAX_STATIONS];                      // Dijkstra算法的前驱数组
bool visited[MAX_STATIONS];                 // Dijkstra算法的访问标记

vector<string> edge[MAX_LINES + 1]; // 存储每条线路的所有站点（索引从1开始）

// ===============================
// 函数声明
// ===============================
void init_adj_matrix();
void read_lines_from_file();
int find_station_id(const char *name);
void dijkstra(int start, int end);
bool has_common_line(Station *s1, Station *s2, int *common_line);
void print_path(int end);
void query_line();
void query_station();
void query_path();
void print_menu();
bool validate_line_id(int line_id);

// ===============================
// 功能函数实现
// ===============================
/**
 * 查询线路所有站点
 */
void query_line() {
  int target_line;
  printf("请输入查询的线路号：");
  if (scanf("%d", &target_line) != 1) {
    printf("错误：输入格式不正确！\n");
    // 清空输入缓冲区
    while (getchar() != '\n')
      ;
    return;
  }

  if (!validate_line_id(target_line) || edge[target_line].empty()) {
    printf("错误：线路%d不存在或无数据！\n", target_line);
    return;
  }

  printf("\n线路%d的所有站点（共%d站）：\n", target_line,
         (int)edge[target_line].size());
  printf("----------------------------------------\n");
  int index = 1;
  for (const auto &station : edge[target_line]) {
    printf("%3d. %s\n", index++, station.c_str());
  }
  printf("----------------------------------------\n");
}

/**
 * 查询站点所属线路
 */
void query_station() {
  char target_name[50];
  printf("请输入查询的站点名称：");
  if (scanf("%49s", target_name) != 1) {
    printf("错误：输入格式不正确！\n");
    while (getchar() != '\n')
      ;
    return;
  }

  int target_idx = find_station_id(target_name);
  if (target_idx == -1) {
    printf("错误：站点'%s'不存在！请检查拼写是否正确。\n", target_name);
    return;
  }

  printf("\n%s所经过的线路为：", target_name);
  for (int k = 0; k < stations[target_idx].line_count; k++) {
    printf("%d号线", stations[target_idx].line_ids[k]);
    if (k < stations[target_idx].line_count - 1) {
      printf("、");
    }
  }
  printf("\n");
  printf("共经过 %d 条线路\n", stations[target_idx].line_count);
}

/**
 * 查询两点间最短路径
 */
void query_path() {
  char start_name[50], end_name[50];
  printf("请输入起点站点名称：");
  if (scanf("%49s", start_name) != 1) {
    printf("错误：输入格式不正确！\n");
    while (getchar() != '\n')
      ;
    return;
  }

  printf("请输入终点站点名称：");
  if (scanf("%49s", end_name) != 1) {
    printf("错误：输入格式不正确！\n");
    while (getchar() != '\n')
      ;
    return;
  }

  int start = find_station_id(start_name);
  int end = find_station_id(end_name);

  if (start == -1 || end == -1) {
    printf("错误：输入的站点不存在！请检查拼写。\n");
    if (start == -1)
      printf("  - 起点'%s'不存在\n", start_name);
    if (end == -1)
      printf("  - 终点'%s'不存在\n", end_name);
    return;
  }

  if (start == end) {
    printf("错误：起点和终点不能相同！\n");
    return;
  }

  dijkstra(start, end);
  if (dist[end] >= INF) {
    printf("无路径可达\n");
  } else {
    printf("\n最短路径距离：%d站\n", dist[end]);
    printf("----------------------------------------\n");
    print_path(end);
    printf("----------------------------------------\n");
  }
}

/**
 * 打印主菜单
 */
void print_menu() {
  printf("\n========== 成都地铁查询系统 ==========\n");
  printf("1. 查询线路所有站点\n");
  printf("2. 查询站点所属线路\n");
  printf("3. 查询两点间最短路径\n");
  printf("0. 退出程序\n");
  printf("====================================\n");
  printf("请选择功能(0-3)：");
}

/**
 * 验证线路ID是否有效
 */
bool validate_line_id(int line_id) {
  return line_id >= 1 && line_id <= MAX_LINES;
}

/**
 * 主函数
 */
int main() {
  // 初始化
  init_adj_matrix();      // 初始化邻接矩阵
  read_lines_from_file(); // 读取地铁线路数据

  if (station_count == 0) {
    printf("错误：未读取到任何站点数据！请检查数据文件。\n");
    return 1;
  }

  printf("数据加载成功！共%d个站点，%d条线路\n", station_count,
         (int)(sizeof(edge) / sizeof(edge[0])));

  // 主循环
  int target;
  do {
    print_menu();

    if (scanf("%d", &target) != 1) {
      printf("错误：输入格式不正确！请输入数字。\n");
      while (getchar() != '\n')
        ;
      continue;
    }

    // 根据选择执行相应功能
    switch (target) {
    case 1:
      query_line();
      break;
    case 2:
      query_station();
      break;
    case 3:
      query_path();
      break;
    case 0:
      printf("感谢使用，再见！\n");
      break;
    default:
      printf("错误：无效的选择！请输入0-3之间的数字。\n");
      break;
    }

    if (target != 0) {
      printf("\n按Enter键继续...");
      while (getchar() != '\n')
        ;
      getchar(); // 等待用户按Enter
    }
  } while (target != 0);

  return 0;
}

// ===============================
// 工具函数实现
// ===============================
/**
 * 初始化邻接矩阵
 */
void init_adj_matrix() {
  memset(adj_matrix, 0x3f, sizeof(adj_matrix)); // 使用0x3f3f3f3f作为无穷大
  for (int i = 0; i < MAX_STATIONS; i++) {
    adj_matrix[i][i] = 0; // 自己到自己的距离为0
  }
}

/**
 * 从文件读取线路数据
 */
void read_lines_from_file() {
  FILE *fp = fopen(FILE_NAME, "r");
  if (!fp) {
    // 尝试在上级目录查找文件
    char parent_path[200];
    strcpy(parent_path, "../");
    strcat(parent_path, FILE_NAME);
    fp = fopen(parent_path, "r");
    if (!fp) {
      printf("错误：无法打开数据文件 '%s'！\n", FILE_NAME);
      printf("请确保数据文件存在于当前目录或上级目录。\n");
      exit(EXIT_FAILURE);
    }
  }

  char line_buffer[100] = {0};          // 站点名称缓冲区（增大缓冲区）
  int current_line_id = -1;             // 当前处理的线路号
  int station_list[MAX_STATIONS] = {0}; // 当前线路的站点ID列表
  int list_len = 0;                     // 当前线路的站点数

  while (fgets(line_buffer, sizeof(line_buffer), fp)) {
    // 去除行末换行符和空格
    int len = strlen(line_buffer);
    while (len > 0 &&
           (line_buffer[len - 1] == '\n' || line_buffer[len - 1] == '\r' ||
            line_buffer[len - 1] == ' ' || line_buffer[len - 1] == '\t')) {
      line_buffer[--len] = '\0';
    }

    // 处理空行（线路分隔符）
    if (len == 0) {
      current_line_id = -1; // 重置线路状态
      list_len = 0;         // 清空站点列表
      continue;
    }

    // 检测线路标题（格式：线路X：）
    if (sscanf(line_buffer, "线路%d:", &current_line_id) == 1) {
      if (!validate_line_id(current_line_id)) { // 过滤非法线路号
        current_line_id = -1;
        continue;
      }
      list_len = 0;                     // 新线路开始，重置站点列表
    } else if (current_line_id != -1) { // 处理站点行
      // 去重处理：检查站点是否已存在
      edge[current_line_id].push_back(string(line_buffer));

      bool exists = false;
      int existing_station_id = -1;

      for (int i = 0; i < station_count; i++) {
        if (strcmp(stations[i].name, line_buffer) == 0) {
          // 添加线路ID（避免重复）
          bool has_line = false;
          for (int l = 0; l < stations[i].line_count; l++) {
            if (stations[i].line_ids[l] == current_line_id) {
              has_line = true;
              break;
            }
          }
          if (!has_line && stations[i].line_count < MAX_LINES) {
            stations[i].line_ids[stations[i].line_count++] = current_line_id;
          }
          existing_station_id = i;
          exists = true;
          break;
        }
      }

      // 新增站点
      if (!exists && station_count < MAX_STATIONS) {
        strncpy(stations[station_count].name, line_buffer,
                sizeof(stations[station_count].name) - 1);
        stations[station_count].name[sizeof(stations[station_count].name) - 1] =
            '\0';
        stations[station_count].line_ids[0] = current_line_id;
        stations[station_count].line_count = 1;
        stations[station_count].id = station_count;
        existing_station_id = station_count++;
      }

      // 构建邻接关系：当前站点与前一站点相连
      if (list_len > 0 && existing_station_id != -1) {
        int prev_station_id = station_list[list_len - 1];
        adj_matrix[prev_station_id][existing_station_id] = 1;
        adj_matrix[existing_station_id][prev_station_id] = 1; // 无向图
      }

      station_list[list_len++] = existing_station_id;
    }
  }

  fclose(fp);
}

/**
 * 查找站点ID
 * @param name 站点名称
 * @return 站点ID，未找到返回-1
 */
int find_station_id(const char *name) {
  if (name == nullptr) {
    return -1;
  }

  for (int i = 0; i < station_count; i++) {
    if (strcmp(stations[i].name, name) == 0) {
      return stations[i].id;
    }
  }
  return -1; // 未找到
}

/**
 * Dijkstra算法求最短路径
 * @param start 起点站点ID
 * @param end 终点站点ID
 */
void dijkstra(int start, int end) {
  // 初始化
  memset(visited, false, sizeof(visited));
  memset(dist, 0x3f, sizeof(dist));
  memset(pre, -1, sizeof(pre));
  dist[start] = 0;

  // Dijkstra主循环
  for (;;) {
    int min_idx = -1;
    int min_dist = INF;

    // 找到未访问的距离最小的节点
    for (int j = 0; j < station_count; j++) {
      if (!visited[j] && dist[j] < min_dist) {
        min_dist = dist[j];
        min_idx = j;
      }
    }

    // 如果找不到或已到达终点，退出
    if (min_idx == -1 || min_idx == end) {
      break;
    }

    visited[min_idx] = true;

    // 更新邻接节点的距离
    for (int v = 0; v < station_count; v++) {
      if (!visited[v] && adj_matrix[min_idx][v] < INF) {
        int new_dist = dist[min_idx] + adj_matrix[min_idx][v];
        if (new_dist < dist[v]) {
          dist[v] = new_dist;
          pre[v] = min_idx;
        }
      }
    }
  }
}

/**
 * 检查两个站点是否有共同线路
 * @param s1 站点1
 * @param s2 站点2
 * @param common_line 输出参数，共同线路ID
 * @return 是否有共同线路
 */
bool has_common_line(Station *s1, Station *s2, int *common_line) {
  if (s1 == nullptr || s2 == nullptr || common_line == nullptr) {
    return false;
  }

  for (int i = 0; i < s1->line_count; i++) {
    for (int j = 0; j < s2->line_count; j++) {
      if (s1->line_ids[i] == s2->line_ids[j]) {
        *common_line = s1->line_ids[i];
        return true;
      }
    }
  }
  return false;
}

/**
 * 打印路径及换乘信息
 * @param end 终点站点ID
 */
void print_path(int end) {
  int path[MAX_STATIONS];
  int idx = 0;
  int current = end;

  // 构建路径（从终点到起点）
  while (current != -1) {
    path[idx++] = current;
    current = pre[current];
  }

  // 反转路径（从起点到终点）
  for (int i = 0; i < idx / 2; i++) {
    int temp = path[i];
    path[i] = path[idx - 1 - i];
    path[idx - 1 - i] = temp;
  }

  printf("路径：\n");
  int pre_line = -1; // 记录前一站点的线路
  int transfers = 0;

  for (int i = 0; i < idx; i++) {
    int station_id = path[i];
    Station *s = &stations[station_id];
    int current_line = -1;

    // 查找与前一站点的共同线路（处理换乘）
    if (i > 0) {
      Station *pre_s = &stations[path[i - 1]];
      if (!has_common_line(s, pre_s, &current_line)) {
        // 没有共同线路，默认使用当前站点的第一条线路
        current_line = (s->line_count > 0) ? s->line_ids[0] : -1;
      }
    } else {
      // 起点站，使用第一条线路
      current_line = (s->line_count > 0) ? s->line_ids[0] : -1;
    }

    // 输出起点
    if (i == 0) {
      if (current_line > 0) {
        printf("%d号线 %s（起点）\n", current_line, s->name);
      } else {
        printf("%s（起点）\n", s->name);
      }
    } else if (i == idx - 1) {
      // 终点
      printf("→ %s（终点）\n", s->name);
    } else {
      // 检测换乘：线路变化且当前站点为换乘站
      if (current_line != pre_line && pre_line != -1 &&
          stations[path[i - 1]].line_count > 1) {
        // 换乘发生在前一站点，显示换乘信息
        printf("→ 在%s换乘%d号线\n", stations[path[i - 1]].name, current_line);
        printf("  %s\n", s->name);
        transfers++;
      } else {
        printf("→ %s\n", s->name);
      }
    }
    pre_line = current_line;
  }

  printf("\n总站点数：%d 站，换乘次数：%d 次\n", idx - 1, transfers);
}