/*

======================第一次rewrite========================

-------------------------时间------------------------------
&emsp;&emsp;@author 巷北  
&emsp;&emsp;@time 2026-02-18 15:23:38  

-----------------------问题--------------------------------
写的时候, 似乎还是靠回忆, 没有形成真正的心理表征.
脑海里想的不是图像, 不是算法, 而单纯的是代码.
虽然问题不大, 但起不到任何训练的效果.
临界(result.size() == 0)忘了判断

--------------------心理表征-------------------------------
输入如何存储的?
每次的for循环是based0还是based1? 何时选择二者?
结果如何保存?
dfs临界判断是什么?
dfs外部循环, 内部循环分别代表什么?

解释:
输入是用二维矩阵存储的, 可以表示邻接矩阵, 也可以表示邻接表.
分析首节点是0开始的还是1开始的. 跟节点相关的, 以首节点为基础.
本题存储的是路径, 那么就用二维矩阵存储.
dfs临界判断的是是否到达目标节点(start==end). 到达了则存储路径
并return
对于邻接表, 邻接矩阵, 并没有外部循环(这个题目). 而关联矩阵会
有外部循环

*/

std::vector<std::vector<int>> result;
std::vector<int> path;

void dfs(const std::vector<std::vector<int>> &graph, int start, int end) {
  if (start == end) {
    result.push_back(path);
    return;
  }

  for (int i = 1; i <= end; ++i) {
    if (graph[start][i] == 1) {
      path.push_back(i);
      dfs(graph, i, end);
      path.pop_back();
    }
  }
}

int main() {
  int n, m, s, t;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n + 1, std::vector<int>(m + 1));

  for (int i = 1; i <= m; i++) {
    std::cin >> s >> t;
    graph[s][t] = 1;
  }

  path.push_back(1);
  dfs(graph, 1, n);

  if (result.size() == 0)
    std::cout << -1 << std::endl;
  for (const auto &path : result) {
    for (int i = 0; i < path.size() - 1; ++i) {
      std::cout << path[i] << " ";
    }
    std::cout << path[path.size() - 1] << std::endl;
  }
}
