/*
&emsp;&emsp;@author 巷北
&emsp;&emsp;@time 2026-02-18 14:58:06

这个是比较完整的书中的代码实现.
我添加了算法可视化部分.
可视化部分代码与算法强耦合, 有没有好的解耦合的设计方法呢?
*/
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void bfs(const std::vector<std::vector<int>> &grid,
         std::vector<std::vector<bool>> &visited, int x, int y,
         algkit::Graph &tree, const int &result) {
  std::queue<std::pair<int, int>> que;
  que.push({x, y});
  visited[x][y] = true;

  std::string lastPopNode = "";
  static int count = 1;
  while (!que.empty()) {
    std::pair<int, int> cur = que.front();
    que.pop();
    int curx = cur.first;
    int cury = cur.second;

    std::stringstream current;
    current << "(" << curx << ", " << cury << ")";

    std::string popNode = tree.addNode(
        {std::to_string(result), "Null", current.str(), "Null",
         std::to_string(count), std::to_string(que.size()), "出队"});
    ++count;
    if (!lastPopNode.empty()) {
      tree.addEdge(lastPopNode, popNode);
    }
    lastPopNode = popNode;

    for (int i = 0; i < 4; ++i) {
      int nextx = curx + dir[i][0];
      int nexty = cury + dir[i][1];

      if (nextx < 0 || nextx >= grid.size() || nexty < 0 ||
          nexty >= grid[0].size())
        continue;

      if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
        que.push({nextx, nexty});
        visited[nextx][nexty] = true;
        std::stringstream next;
        std::stringstream directed;

        next << "(" << nextx << ", " << nexty << ")";
        directed << "(" << dir[i][0] << ", " << dir[i][1] << ")";
        std::string pushNode = tree.addNode(
            {std::to_string(result), next.str(), current.str(), directed.str(),
             std::to_string(count), std::to_string(que.size()), "入队"});
        ++count;
        tree.addEdge(popNode, pushNode);
      }
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> infos = {"岛屿数量",    "nextx&&nexty", "curx&&cury",
                                    "dir",         "count",        "队列长度",
                                    "出队还是入队"};
  std::vector<int> layout = {1, 1, 1, 1, 1, 1, 1};
  algkit::Graph tree(infos, layout);

  std::vector<std::vector<int>> grid(n, std::vector<int>(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> grid[i][j];
    }
  }

  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

  int result = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!visited[i][j] && grid[i][j] == 1) {
        ++result;
        bfs(grid, visited, i, j, tree, result);
      }
    }
  }

  std::cout << result << std::endl;

  tree.toDot();
  tree.writeToFile("tree.dot");
  tree.exportSvg("tree.svg", true);
}
