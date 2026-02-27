int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
int max_ = 0;
int result;

void bfs(const std::vector<std::vector<int>> &incidence_matrix,
         std::vector<std::vector<bool>> &isvisited, int x, int y) {
  std::queue<std::pair<int, int>> que;
  que.push({x, y});
  isvisited[x][y] = true;
  ++result;

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
        isvisited[nextx][nexty] = true;
        ++result;
      }
    }
  }

  if (::max_ < result)
    ::max_ = result;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> incidence_matrix(n, std::vector<int>(m, 0));
  std::vector<std::vector<bool>> isvisited(n, std::vector<bool>(m, false));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> incidence_matrix[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!isvisited[i][j] && incidence_matrix[i][j] == 1) {
        result = 0;
        bfs(incidence_matrix, isvisited, i, j);
      }
    }
  }

  std::cout << ::max_ << std::endl;
}
