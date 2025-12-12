#include <bits/stdc++.h>
#include <sstream>

using namespace std;

void read_final_state(stringstream &ss, string &final_state) {
  char c;
  ss >> c;
  while (c != ']') {
    ss >> c;
    if (c == '.' || c == '#') {
      final_state.push_back(c);
    }
  }
}

void read_general(stringstream &ss, vector<vector<int>> &wirings,
                  vector<int> &jolts) {
  char c;
  int i;
  while (true) {
    ss >> c;
    if (c == '(') {
      vector<int> cur;
      while (c != ')') {
        ss >> i >> c;
        cur.push_back(i);
      }
      wirings.push_back(cur);
    } else if (c == '{') {
      while (c != '}') {
        ss >> i >> c;
        jolts.push_back(i);
      }
    } else
      break;
  }
}

int main() {
  ifstream input_file("input.txt");
  string line;
  int fewest_presses = 0;
  while (getline(input_file, line)) {
    string final_state;
    vector<vector<int>> wirings;
    vector<int> jolts;
    stringstream ss(line);
    read_final_state(ss, final_state);
    read_general(ss, wirings, jolts);
    unordered_map<string, int> dist;
    queue<string> q;
    string init_state = string(final_state.size(), '.');
    dist[init_state] = 0;
    q.push(init_state);
    while (!dist.count(final_state)) {
      auto i = q.front();
      auto d = dist[i];
      q.pop();
      for (auto ws : wirings) {
        auto j = i;
        for (auto w : ws) {
          j[w] = '.' + '#' - j[w];
        }
        if (!dist.count(j)) {
          q.push(j);
          dist[j] = d + 1;
        }
      }
    }
    fewest_presses += dist[final_state];
  }
  cout << fewest_presses << endl;

  return 0;
}