#include <bits/stdc++.h>

using namespace std;

using Shape = array<array<bool, 3>, 3>;

Shape read_shape(ifstream &ss) {
  Shape s;
  string line;
  ss >> line; // ignore
  for (int i = 0; i < 3; ++i) {
    ss >> line;
    for (int j = 0; j < 3; ++j) {
      s[i][j] = line[j] == '#';
    }
  }
  return s;
}

void print_shape(Shape s) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      char c = s[i][j] ? '#' : '.';
      cout << c;
    }
    cout << endl;
  }
}

Shape flip(Shape s) {
  Shape rs;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      rs[i][j] = s[i][2 - j];
    }
  }
  return rs;
}

Shape rotate(Shape s) {
  Shape rs;
  for (int j = 0; j < 2; ++j) {
    rs[0][j] = s[2 - j][0];
    rs[j][2] = s[0][j];
    rs[2][2 - j] = s[j][2];
    rs[2 - j][0] = s[2][2 - j];
  }
  return rs;
}

int main() {
  ifstream input_file("input.txt");

  for (int i = 0; i < 6; ++i)
    read_shape(input_file);

  int num_fit = 0;
  int x, y;
  char c;
  while (input_file >> x >> c >> y >> c) {
    vector<int> cnt(6);
    int total_cnt = 0;
    for (int i = 0; i < 6; ++i) {
      input_file >> cnt[i];
      total_cnt += cnt[i];
    }
    if (total_cnt <= (x / 3) * (y / 3)) {
      ++num_fit;
    }
  }
  cout << num_fit << endl;

  return 0;
}
