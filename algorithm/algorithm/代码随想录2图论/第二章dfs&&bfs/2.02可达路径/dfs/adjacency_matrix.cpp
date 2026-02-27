std::vector<std::vector<int>> result;
std::vector<int> path;

void dfs(const std::vector<std::vector<int>> &adjacency_matrix, int start,
         int end, algkit::Graph &tree, const std::string &parent,
         algkit::Graph &graph, const std::vector<std::string> &nodes,
         std::vector<bool> &visited) {
  if (start == end) {
    result.push_back(path);
    return;
  }

  static int count = 1;
  visited[start] = true;
  for (int i = 1; i <= end; ++i) {
    std::string children = tree.addNode({i});
    tree.addEdge(parent, children);
    if (adjacency_matrix[start][i] == 1 && visited[i] == false) {
      tree.setNodeColor(children, algkit::Color::Red);
      path.push_back(i);
      graph.addEdge(nodes[start], nodes[i], count);
      ++count;
      dfs(adjacency_matrix, i, end, tree, children, graph, nodes, visited);
      path.pop_back();
    }
  }
  visited[start] = false;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m, s, t;
  std::cin >> n >> m;

  std::vector<std::string> infos = {"节点"};
  std::vector<int> layout{1};
  algkit::Graph graph(infos, layout);
  std::vector<std::string> nodes(n + 1);
  algkit::Graph tree(infos, layout);

  for (int i = 1; i <= n; ++i) {
    nodes[i] = graph.addNode({i}, algkit::Color::Blue);
  }

  std::vector<std::vector<int>> adjacency_matrix(n + 1,
                                                 std::vector<int>(n + 1));
  while (m--) {
    std::cin >> s >> t;
    adjacency_matrix[s][t] = 1;
  }

  std::vector<bool> visited(n + 1, false);
  std::string root = tree.addNode({1});
  path.push_back(1);
  visited[1] = true;
  dfs(adjacency_matrix, 1, n, tree, root, graph, nodes, visited);

  if (result.size() == 0)
    std::cout << -1;
  for (const auto &path : result) {
    for (int i = 0; i < path.size() - 1; ++i) {
      std::cout << path[i] << " ";
    }
    std::cout << path[path.size() - 1] << std::endl;
  }

  tree.toDot();
  tree.writeToFile("tree.dot");
  tree.exportSvg("tree.svg", true);

  graph.toDot();
  graph.writeToFile("graph.dot");
  graph.exportSvg("graph.svg", true);
}
