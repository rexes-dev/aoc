#include <bits/stdc++.h>

using namespace std;

int get_parent(int i, vector<int> &parents) {
  if (parents[i] == i)
    return i;
  return parents[i] = get_parent(parents[i], parents);
}

bool unite(int i, int j, vector<int> &parents, vector<int> &szs) {
  i = get_parent(i, parents);
  j = get_parent(j, parents);
  if (i != j) {
    if (szs[i] < szs[j])
      swap(i, j);

    // i >= j
    parents[j] = i;
    szs[i] += szs[j];
    if (szs[i] == parents.size())
      return true;
  }
  return false;
}

int main() {
  ifstream input_file("input.txt");
  string line;
  vector<tuple<int, int, int>> jbs;
  while (input_file >> line) {
    stringstream liness(line);
    int x, y, z;
    char c;
    liness >> x >> c >> y >> c >> z;
    jbs.emplace_back(x, y, z);
  }
  int n = jbs.size();
  vector<tuple<long long, int, int>> dist;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      auto [x1, y1, z1] = jbs[i];
      auto [x2, y2, z2] = jbs[j];

      long long d2 = 0;
      d2 += 1LL * (x1 - x2) * (x1 - x2);
      d2 += 1LL * (y1 - y2) * (y1 - y2);
      d2 += 1LL * (z1 - z2) * (z1 - z2);
      dist.emplace_back(d2, i, j);
    }
  }
  sort(dist.begin(), dist.end());

  vector<int> szs(n);
  vector<int> parents(n);
  for (int i = 0; i < n; ++i) {
    parents[i] = i;
    szs[i] = 1;
  }

  long long last_two_x = 1;
  bool seen_last_unity = false;
  for (int di = 0; di < 1000; ++di) {
    auto [d2, i, j] = dist[di];
    bool last_unity = unite(i, j, parents, szs);
    if (last_unity) {
      last_two_x *= get<0>(jbs[i]);
      last_two_x *= get<0>(jbs[j]);
      seen_last_unity = true;
      break;
    }
  }

  vector<int> largest_circuit_sizes;
  for (int i = 0; i < n; ++i) {
    if (i == get_parent(i, parents))
      largest_circuit_sizes.push_back(szs[i]);
  }
  sort(largest_circuit_sizes.begin(), largest_circuit_sizes.end());
  long long largest_circuit_sizes3 = 1;
  for (int i = 0; i < 3; ++i)
    largest_circuit_sizes3 *=
        largest_circuit_sizes[largest_circuit_sizes.size() - 1 - i];
  cout << largest_circuit_sizes3 << endl;

  if (!seen_last_unity) {
    for (int di = 1000; di < dist.size(); ++di) {
      auto [d2, i, j] = dist[di];
      bool last_unity = unite(i, j, parents, szs);
      if (last_unity) {
        last_two_x *= get<0>(jbs[i]);
        last_two_x *= get<0>(jbs[j]);
        seen_last_unity = true;
        break;
      }
    }
  }
  cout << last_two_x << endl;

  return 0;
}
