int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void bfs(std::vector<std::vector<int>> &incidence_matrix, int x, int y) {
  std::queue<std::pair<int, int>> que;
  que.push({x, y});
  incidence_matrix[x][y] = 0;

  while (!que.empty()) {
    std::pair<int, int> cur = que.front();
    que.pop();
    int curx = cur.first;
    int cury = cur.second;

    for (int i = 0; i < 4; ++i) {
      int nextx = curx + dir[i][0];
      int nexty = cury + dir[i][1];

      if (nextx < 0 || nextx >= incidence_matrix.size() || nexty < 0 ||
          nexty >= incidence_matrix[0].size())
        continue;
      if (!incidence_matrix[nextx][nexty])
        continue;
      que.push({nextx, nexty});
      incidence_matrix[nextx][nexty] = 0; // 什么时候标记呢?
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> incidence_matrix(n, std::vector<int>(m, 0));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> incidence_matrix[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    if (incidence_matrix[i][0])
      bfs(incidence_matrix, i, 0);
    if (incidence_matrix[i][m - 1])
      bfs(incidence_matrix, i, m - 1);
  }
  for (int j = 1; j < m - 1; ++j) {
    if (incidence_matrix[0][j])
      bfs(incidence_matrix, 0, j);
    if (incidence_matrix[n - 1][j])
      bfs(incidence_matrix, n - 1, j);
  }

  int count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (incidence_matrix[i][j] == 1)
        count++;
    }
  }
  std::cout << count << std::endl;
}
