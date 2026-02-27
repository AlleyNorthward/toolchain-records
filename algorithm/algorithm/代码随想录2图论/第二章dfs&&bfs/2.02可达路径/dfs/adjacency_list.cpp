std::vector<std::vector<int>> result;
std::vector<int> path;

void dfs(const std::vector<std::list<int>> &adjacency_list, int start,
         int end, algkit::Graph &tree, const std::string &parent) {
  if (start == end) {
    result.push_back(path);
    return;
  }
  for (int i : adjacency_list[start]) {
    std::string children = tree.addNode({i}, algkit::Color::Purple);
    tree.addEdge(parent, children);
    path.push_back(i);
    dfs(adjacency_list, i, end, tree, children);
    path.pop_back();
  }
}

int main() {
  freopen("input.txt", "r", stdin);

  int n, m, s, t;
  std::cin >> n >> m;
  std::vector<std::list<int>> adjacency_list(n + 1);

  std::vector<std::string> infos{"节点"};
  std::vector<int> layout{1};
  algkit::Graph tree(infos, layout);

  while (m--) {
    std::cin >> s >> t;
    adjacency_list[s].push_back(t);
  }

  std::string parent = tree.addNode({1}, algkit::Color::Purple);
  path.push_back(1);
  dfs(adjacency_list, 1, n, tree, parent);

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
}
