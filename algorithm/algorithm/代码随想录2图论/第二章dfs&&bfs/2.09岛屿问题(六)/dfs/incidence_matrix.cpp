// 思路很明确, 方法技巧也很灵活. 本来可能看不太懂, 但是昨天写了一个matrix可视化的类, 根据算法内部自行分析的话, 就会变得十分明确.
// 效果出奇的好, 哈哈
int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};
int n, m;

void dfs(const std::vector<std::vector<int>> &incidence_matrix,
         std::vector<std::vector<bool>> &isvisited, int x, int y,
         algkit::Matrix &matrix) {
  if (isvisited[x][y])
    return;
  isvisited[x][y] = true;
  matrix.setNodeColor({x, y}, algkit::Color::Orange);

  for (int i = 0; i < 4; ++i) {
    int nextx = x + dir[i][0];
    int nexty = y + dir[i][1];

    if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= m)
      continue;
    if (incidence_matrix[x][y] > incidence_matrix[nextx][nexty])
      continue;

    dfs(incidence_matrix, isvisited, nextx, nexty, matrix);
  }
  return;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::cin >> n >> m;
  std::vector<std::vector<int>> incidence_matrix(n, std::vector<int>(m, 0));
  algkit::Matrix matrix_ul(n, m);
  algkit::Matrix matrix_dr(n, m);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> incidence_matrix[i][j];
      matrix_ul.addNode({i, j}, std::to_string(incidence_matrix[i][j]));
      matrix_dr.addNode({i, j}, std::to_string(incidence_matrix[i][j]));
    }
  }

  std::vector<std::vector<bool>> isvisited_ul(n, std::vector<bool>(m, false));
  std::vector<std::vector<bool>> isvisited_dr(n, std::vector<bool>(m, false));

  for (int i = 0; i < n; ++i) {
    dfs(incidence_matrix, isvisited_ul, i, 0, matrix_ul);
    dfs(incidence_matrix, isvisited_dr, i, m - 1, matrix_dr);
  }

  for (int i = 0; i < m; ++i) {
    dfs(incidence_matrix, isvisited_ul, 0, i, matrix_ul);
    dfs(incidence_matrix, isvisited_dr, n - 1, i, matrix_dr);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (isvisited_dr[i][j] && isvisited_ul[i][j]) {
        std::cout << i << " " << j << std::endl;
      }
    }
  }

  matrix_dr.writeToFile("matrix_dr.dot");
  matrix_ul.writeToFile("matrix_ul.dot");

  matrix_dr.exportSvg("matrix_dr.svg", true);
  matrix_ul.exportSvg("matrix_ul.svg", true);
}
