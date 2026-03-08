int main() {
  freopen("input.txt", "r", stdin);
  int n;
  std::cin >> n;
  std::string startStr, endStr, str;
  std::unordered_set<std::string> strList;
  std::cin >> startStr >> endStr;

  while (n--) {
    std::cin >> str;
    if (strList.count(str))
      continue;
    strList.insert(str);
  }

  std::queue<std::string> que;
  que.push(startStr);
  std::unordered_map<std::string, int> str_path_map;
  str_path_map.insert(std::pair<std::string, int>(startStr, 1));

  while (!que.empty()) {
    std::string word = que.front();
    que.pop();
    int path = str_path_map[word];

    for (int i = 0; i < word.size(); ++i) {
      std::string newWord = word;
      for (int j = 0; j < 26; ++j) {
        newWord[i] = j + 'a';
        if (newWord == endStr) {
          std::cout << path + 1 << std::endl;
          return 0;
        }

        if (!str_path_map.count(newWord) && strList.count(newWord)) {
          que.push(newWord);
          str_path_map.insert(std::pair<std::string, int>(newWord, path + 1));
        }
      }
    }
  }

  std::cout << 0 << std::endl;
}
