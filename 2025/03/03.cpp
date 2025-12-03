#include <bits/stdc++.h>

using namespace std;

int main() {
  ifstream input_file("input.txt");
  string line;
  int total_jolt = 0;
  long long new_total_jolt = 0;
  while (input_file >> line) {
    char mc = 0;
    int j = 0;
    for (int i = 0; i < line.size() - 1; ++i) {
      if (line[i] > mc) {
        mc = line[i];
        j = i;
      }
    }
    char nmc = 0;
    for (int i = j + 1; i < line.size(); ++i) {
      if (line[i] > nmc) {
        nmc = line[i];
      }
    }
    int cur_jolt = (mc - '0') * 10 + (nmc - '0');
    total_jolt += cur_jolt;

    long long new_cur_jolt = 0;
    int k = -1;
    for (int i = 0; i < 12; ++i) {
      char mc = 0;
      for (int j = k + 1; j < line.size() + i - 11; ++j) {
        if (line[j] > mc) {
          mc = line[j];
          k = j;
        }
      }
      new_cur_jolt *= 10;
      new_cur_jolt += mc - '0';
    }
    new_total_jolt += new_cur_jolt;
  }

  cout << total_jolt << endl;
  cout << new_total_jolt << endl;

  return 0;
}