#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
};

long long get_area(Point t1, Point t2) {
  return 1LL * (abs(t2.x - t1.x) + 1) * (abs(t2.y - t1.y) + 1);
}

bool point_in_edge(Point t, Point e1, Point e2) {
  if (t.x == e1.x && t.x == e2.x && min(e1.y, e2.y) <= t.y &&
      t.y <= max(e1.y, e2.y)) {
    return true;
  }
  if (t.y == e1.y && t.y == e2.y && min(e1.x, e2.x) <= t.x &&
      t.x <= max(e1.x, e2.x)) {
    return true;
  }
  return false;
}

bool point_in_poly(Point t, vector<Point> &tiles) {
  int n = tiles.size();
  int cross_cnt = 0;
  for (int i = 0; i < n; ++i) {
    auto e1 = tiles[i];
    auto e2 = tiles[(i + 1) % n];
    if (point_in_edge(t, e1, e2))
      return true;
    if (e1.y == e2.y)
      continue;
    if (e1.y > e2.y)
      swap(e1.y, e2.y);
    if (t.x < e1.x && e1.y <= t.y && t.y < e2.y)
      ++cross_cnt;
  }
  return cross_cnt % 2 == 1;
}

bool rect_in_poly(Point t1, Point t2, vector<Point> &tiles) {
  if (t1.x > t2.x)
    swap(t1.x, t2.x);
  if (t1.y > t2.y)
    swap(t1.y, t2.y);

  for (int x : {t1.x, t2.x}) {
    for (int y : {t1.y, t2.y}) {
      if (!point_in_poly({x, y}, tiles))
        return false;
    }
  }

  int n = tiles.size();
  for (int y : {t1.y, t2.y}) {
    for (int i = 0; i < n; ++i) {
      auto e1 = tiles[i];
      auto e2 = tiles[(i + 1) % n];
      if (e1.y == e2.y)
        continue;
      if (e1.y > e2.y)
        swap(e1.y, e2.y);
      if (t1.x < e1.x && e1.x < t2.x && e1.y <= y && y < e2.y)
        return false;
    }
  }
  for (int x : {t1.x, t2.x}) {
    for (int i = 0; i < n; ++i) {
      auto e1 = tiles[i];
      auto e2 = tiles[(i + 1) % n];
      if (e1.x == e2.x)
        continue;
      if (e1.x > e2.x)
        swap(e1.x, e2.x);
      if (t1.y < e1.y && e1.y < t2.y && e1.x <= x && x < e2.x)
        return false;
    }
  }

  return true;
}

int main() {
  ifstream input_file("input.txt");
  int x, y;
  char c;
  vector<Point> tiles;
  while (input_file >> x >> c >> y) {
    tiles.push_back(Point{x, y});
  }
  int n = tiles.size();
  long long largest_area = 0;
  long long restricted_largest_area = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      largest_area = max(largest_area, get_area(tiles[i], tiles[j]));
      if (rect_in_poly(tiles[i], tiles[j], tiles)) {
        restricted_largest_area =
            max(restricted_largest_area, get_area(tiles[i], tiles[j]));
      }
    }
  }
  cout << largest_area << endl;
  cout << restricted_largest_area << endl;

  return 0;
}