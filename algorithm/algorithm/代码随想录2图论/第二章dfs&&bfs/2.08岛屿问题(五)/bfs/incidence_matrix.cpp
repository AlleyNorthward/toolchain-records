int dir[4][2] = {1, 0, 0, 1, 0, -1, -1, 0};

void bfs(const std::vector<std::vector<int>> &incidence_matrix,
         std::vector<std::vector<int>> &isvisited, int x, int y) {
  std::queue<std::pair<int, int>> que;
  que.push({x, y});
  isvisited[x][y] = 1;

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
      if (!isvisited[nextx][nexty] && incidence_matrix[nextx][nexty] == 1) {
        que.push({nextx, nexty});
        isvisited[nextx][nexty] = 1;
      }
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> incidence_matrix(n, std::vector<int>(m, 0));
  std::vector<std::vector<int>> isvisited(n, std::vector<int>(m, 0));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> incidence_matrix[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    if (incidence_matrix[i][0])
      bfs(incidence_matrix, isvisited, i, 0);
    if (incidence_matrix[i][m - 1])
      bfs(incidence_matrix, isvisited, i, m - 1);
  }

  for (int j = 1; j < m - 1; ++j) {
    if (incidence_matrix[0][j])
      bfs(incidence_matrix, isvisited, 0, j);

    if (incidence_matrix[n - 1][j])
      bfs(incidence_matrix, isvisited, n - 1, j);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m - 1; ++j) {
      std::cout << isvisited[i][j] << " ";
    }
    std::cout << isvisited[i][m - 1] << std::endl;
  }
}
