int main() {
  freopen("input.txt", "r", stdin);
  std::string beginStr, endStr, str;
  int n;
  std::cin >> n;

  std::unordered_set<std::string> strSet;
  std::cin >> beginStr >> endStr;

  for (int i = 0; i < n; ++i) {
    std::cin >> str;
    strSet.insert(str);
  }

  std::unordered_map<std::string, int> visitMap;

  std::queue<std::string> que;
  que.push({beginStr});
  visitMap.insert(std::pair<std::string, int>(beginStr, 1));

  while (!que.empty()) {
    std::string word = que.front();
    que.pop();
    int path = visitMap[word];

    for (int i = 0; i < word.size(); ++i) {
      std::string newWord = word;

      for (int j = 0; j < 26; ++j) {
        newWord[i] = j + 'a';

        if (newWord == endStr) {
          std::cout << path + 1 << std::endl;
          return 0;
        }

        if (strSet.find(newWord) != strSet.end() &&
            visitMap.find(newWord) == visitMap.end()) {
          visitMap.insert(std::pair<std::string, int>(newWord, path + 1));
          que.push(newWord);
        }
      }
    }
  }
}
