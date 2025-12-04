#include <bits/stdc++.h>

using namespace std;

int main() {
  ifstream input_file("input.txt");
  vector<string> m;
  string line;
  while (input_file >> line) {
    m.push_back(line);
  }

  auto is_valid = [&](int i, int j) {
    return 0 <= i && i < m.size() && 0 <= j && j < m[i].size();
  };

  auto cnt_around = [&](int i, int j) {
    int cnt = 0;
    for (int di = -1; di <= 1; ++di) {
      for (int dj = -1; dj <= 1; ++dj) {
        if (di == 0 && dj == 0 || !is_valid(i + di, j + dj))
          continue;
        if (m[i + di][j + dj] == '@')
          ++cnt;
      }
    }
    return cnt;
  };

  int rolls = 0;
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[i].size(); ++j) {
      if (m[i][j] == '.')
        continue;

      int cnt = cnt_around(i, j);

      if (cnt < 4)
        ++rolls;
    }
  }
  cout << rolls << endl;

  int total_rolls = 0;
  vector<vector<bool>> visit(m.size());
  queue<pair<int, int>> not_visit;
  for (int i = 0; i < m.size(); ++i) {
    visit[i] = vector<bool>(m[i].size(), false);
    for (int j = 0; j < m[i].size(); ++j)
      if (m[i][j] == '@')
        not_visit.push({i, j});
  }
  while (not_visit.size()) {
    auto [i, j] = not_visit.front();
    visit[i][j] = true;
    not_visit.pop();
    if (cnt_around(i, j) >= 4)
      continue;
    m[i][j] = '.';
    ++total_rolls;
    for (int di = -1; di <= 1; ++di) {
      for (int dj = -1; dj <= 1; ++dj) {
        if (di == 0 && dj == 0 || !is_valid(i + di, j + dj))
          continue;
        if (m[i + di][j + dj] == '@' && visit[i + di][j + dj]) {
          visit[i + di][j + dj] = false;
          not_visit.push({i + di, j + dj});
        }
      }
    }
  }
  cout << total_rolls << endl;

  return 0;
}
