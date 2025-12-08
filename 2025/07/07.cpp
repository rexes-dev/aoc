#include <bits/stdc++.h>

using namespace std;

int main() {
  ifstream input_file("input.txt");
  string line;
  vector<string> lines;
  while (input_file >> line) {
    lines.push_back(line);
  }

  int m = lines.size();
  int n = lines[0].size();
  int sj = 0;
  for (int j = 0; j < lines[0].size(); ++j) {
    if (lines[0][j] == 'S')
      sj = j;
  }

  int num_split = 0;
  set<int> cur_cols = {sj};
  map<int, long long> col_to_t = {{sj, 1}};
  for (int i = 1; i < m; ++i) {
    set<int> next_cols;
    map<int, long long> next_col_to_t;
    for (int j : cur_cols) {
      if (lines[i][j] == '^') {
        if (j - 1 >= 0) {
          next_cols.insert(j - 1);
          next_col_to_t[j - 1] += col_to_t[j];
        }
        if (j + 1 < n) {
          next_cols.insert(j + 1);
          next_col_to_t[j + 1] += col_to_t[j];
        }
        ++num_split;
      } else {
        next_cols.insert(j);
        next_col_to_t[j] += col_to_t[j];
      }
    }
    cur_cols = next_cols;
    col_to_t = next_col_to_t;
  }
  cout << num_split << endl;
  long long timelines = 0;
  for (auto [_, cnt] : col_to_t) {
    timelines += cnt;
  }
  cout << timelines << endl;

  return 0;
}
