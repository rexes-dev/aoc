#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
  std::ifstream input_file("input.txt");
  if (!input_file) {
    std::cerr << "Error: Unable to open file." << std::endl;
    return -1;
  }

  std::string input_line;
  std::vector<std::vector<std::string>> lks;
  std::vector<std::string> cur_lk;
  while (std::getline(input_file, input_line)) {
    if (input_line.size() == 0) {
      lks.push_back(cur_lk);
      cur_lk.clear();
    } else
      cur_lk.push_back(input_line);
  }
  lks.push_back(cur_lk);

  int unique_lk_cnt = 0;
  for (int i = 0; i < lks.size(); ++i) {
    for (int j = i + 1; j < lks.size(); ++j) {
      auto lk_i = lks[i];
      auto lk_j = lks[j];
      bool is_key = false;
      bool is_lock = false;
      if (lk_i[0][0] == '#')
        is_lock = true;
      else
        is_key = true;
      if (lk_j[0][0] == '#')
        is_lock = true;
      else
        is_key = true;
      if (!is_key || !is_lock) continue;
      bool pos = true;
      for (int jj = 0; jj < lk_i[0].size(); ++jj) {
        for (int ii = 0; ii < lk_i.size(); ++ii) {
          if (lk_i[ii][jj] == '#' && lk_j[ii][jj] == '#') pos = false;
        }
      }
      if (pos) ++unique_lk_cnt;
    }
  }
  std::cout << unique_lk_cnt << std::endl;

  return 0;
}
