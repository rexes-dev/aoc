#include <bits/stdc++.h>

using namespace std;

int main() {
  ifstream input_file("input.txt");
  string line;
  vector<vector<long long>> nums;
  vector<char> signs;
  vector<string> lines;
  while (getline(input_file, line)) {
    stringstream liness(line);
    if (isdigit(line[0]) || line[0] == ' ') {
      vector<long long> cur_nums;
      long long num;
      while (liness >> num)
        cur_nums.push_back(num);
      nums.push_back(cur_nums);
      lines.push_back(line);
    } else {
      char sign;
      while (liness >> sign)
        signs.push_back(sign);
    }
  }
  long long total = 0;
  for (int j = 0; j < nums[0].size(); ++j) {
    long long cur = nums[0][j];
    char sign = signs[j];
    for (int i = 1; i < nums.size(); ++i) {
      if (sign == '+')
        cur += nums[i][j];
      else
        cur *= nums[i][j];
    }
    total += cur;
  }
  cout << total << endl;

  long long grand_total = 0;
  int j = nums[0].size() - 1;
  int col = lines[0].size() - 1;
  long long cur_total = signs[j] == '+' ? 0 : 1;
  while (col >= 0) {
    char sign = signs[j];
    string cur;
    for (int i = 0; i < lines.size(); ++i) {
      cur.push_back(lines[i][col]);
    }
    if (cur == string(lines.size(), ' ')) {
      grand_total += cur_total;
      --j;
      if (j >= 0)
        cur_total = signs[j] == '+' ? 0 : 1;
    } else {
      if (sign == '+')
        cur_total += stoll(cur);
      else
        cur_total *= stoll(cur);
    }
    col--;
  }
  grand_total += cur_total;
  cout << grand_total << endl;

  return 0;
}