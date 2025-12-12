#include <bits/stdc++.h>

using namespace std;

unordered_map<string, vector<string>> prv;

int dp(const string &i) {
  static unordered_map<string, int> cache;
  if (i == "you")
    return 1;
  if (cache.count(i))
    return cache[i];

  int res = 0;
  for (const auto &j : prv[i])
    res += dp(j);

  cache[i] = res;
  return res;
}

unordered_map<string, int> global_cache;
int _dp(const string &src, const string &dst, const string &forbid) {
  if (dst == forbid)
    return 0;
  if (src == dst)
    return 1;
  if (global_cache.count(dst))
    return global_cache[dst];

  int res = 0;
  for (const auto &j : prv[dst]) {
    auto dpj = _dp(src, j, forbid);
    res += dpj;
  }

  global_cache[dst] = res;
  return res;
}
int dp(const string &src, const string &dst, const string &forbid) {
  global_cache.clear();
  return _dp(src, dst, forbid);
}

int main() {
  ifstream input_file("input.txt");

  string line;
  while (getline(input_file, line)) {
    stringstream ss(line);
    string cur;
    ss >> cur;
    cur.pop_back();
    string nxt;
    while (ss >> nxt)
      prv[nxt].push_back(cur);
  }

  cout << 1LL * dp("svr", "fft", "dac") * dp("fft", "dac", "") *
                  dp("dac", "out", "fft") +
              1LL * dp("svr", "dac", "fft") * dp("dac", "fft", "") *
                  dp("fft", "out", "dac")
       << endl;

  return 0;
}
