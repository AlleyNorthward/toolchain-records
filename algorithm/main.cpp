int main() {
  freopen("input.txt", "r", stdin);
  int n, m, s, t;
  std::cin >> n >> m;
  std::vector<std::list<int>> adjacency_list(n);
  std::vector<int> inDegree(n, 0);

  while (m--) {
    std::cin >> s >> t;
    adjacency_list[s].push_back(t);
    ++inDegree[t];
  }

  std::queue<int> que;
  std::vector<int> result;
  for (int i = 0; i < n; ++i) {
    if (inDegree[i] == 0) {
      que.push(i);
    }
  }

  while (!que.empty()) {
    int node = que.front();
    que.pop();
    result.push_back(node);

    for (auto nextNode : adjacency_list[node]) {
      --inDegree[nextNode];
      if (inDegree[nextNode] == 0) {
        que.push(nextNode);
      }
    }
  }

  if (result.size() == n) {
    for (int i = 0; i < n - 1; ++i) {
      std::cout << result[i] << " ";
    }
    std::cout << result[n - 1] << std::endl;
    return 0;
  }

  std::cout << -1 << std::endl;
}
