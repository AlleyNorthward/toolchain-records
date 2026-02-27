int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
int result;

// 分析当前节点, 则需要在for循环外部return. 分析下一节点,
// 则需要在for循环内部判断
void dfs(const std::vector<std::vector<int>> &incidence_matrix,
         std::vector<std::vector<bool>> &isvisited, int x, int y,
         algkit::Graph &tree, const std::string &parent) {
  for (int i = 0; i < 4; ++i) {
    int nextx = x + dir[i][0];
    int nexty = y + dir[i][1];

    if (nextx < 0 || nextx >= incidence_matrix.size() || nexty < 0 ||
        nexty >= incidence_matrix[0].size())
      continue;

    std::stringstream cur, next;
    cur << "(" << x << ", " << y << ")";
    next << "(" << nextx << ", " << nexty << ")";
    std::string children = tree.addNode(
        {cur.str(), next.str(), std::to_string(isvisited[nextx][nexty])});
    tree.addEdge(parent, children);

    if (!isvisited[nextx][nexty] && incidence_matrix[nextx][nexty] == 1) {
      isvisited[nextx][nexty] = true;
      tree.setNodeColor(children, algkit::Color::Purple);
      dfs(incidence_matrix, isvisited, nextx, nexty, tree, children);
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> incidence_matrix(
      n, std::vector<int>(m, 0)); // based-0
  std::vector<std::vector<bool>> isvisited(n, std::vector<bool>(m, 0));

  std::vector<std::string> infos = {"当前节点", "下一节点", "isvisited"};
  std::vector<int> layout{1, 1, 1};
  algkit::Graph tree{infos, layout};

  std::string root =
      tree.addNode({"NULL", "NULL", "NULL"}, algkit::Color::Gray);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> incidence_matrix[i][j];
    }
  }

  // 搜索矩阵: incidence_matrix
  // 搜索对象: 每个节点
  // 搜索对象的邻居: 每个节点的下一集合中的节点.
  // 搜索集合: 四个方向, 上下所有.
  // 搜索条件: 1, false

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!isvisited[i][j] && incidence_matrix[i][j] == 1) {
        isvisited[i][j] = true;
        dfs(incidence_matrix, isvisited, i, j, tree, root);
        result++;
      }
    }
  }

  std::cout << result << std::endl;
  tree.toDot();
  tree.writeToFile("tree.dot");
  tree.exportSvg("tree.svg", true);
}
