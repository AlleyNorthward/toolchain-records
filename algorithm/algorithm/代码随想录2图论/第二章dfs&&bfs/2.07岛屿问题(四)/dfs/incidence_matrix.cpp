int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void dfs(std::vector<std::vector<int>> &incidence_matrix, int x, int y) {
  incidence_matrix[x][y] = 0;

  for (int i = 0; i < 4; ++i) {
    int nextx = dir[i][0] + x;
    int nexty = dir[i][1] + y;

    if (nextx < 0 || nextx >= incidence_matrix.size() || nexty < 0 ||
        nexty >= incidence_matrix[0].size())
      continue;

    if (incidence_matrix[nextx][nexty] == 0)
      continue;
    dfs(incidence_matrix, nextx, nexty);
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> incidence_matrix(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> incidence_matrix[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    if (incidence_matrix[i][0])
      dfs(incidence_matrix, i, 0);
    if (incidence_matrix[i][m - 1])
      dfs(incidence_matrix, i, m - 1);
  }

  for (int i = 1; i < m - 1; ++i) { // 相对于原书, 这里优化了一下
    if (incidence_matrix[0][i])
      dfs(incidence_matrix, 0, i);
    if (incidence_matrix[n - 1][i])
      dfs(incidence_matrix, n - 1, i);
  }

  int area = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (incidence_matrix[i][j] == 1)
        ++area;
    }
  }

  std::cout << area << std::endl;
}
