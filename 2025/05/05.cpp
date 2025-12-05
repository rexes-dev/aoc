#include <bits/stdc++.h>
#include <limits>

using namespace std;

int main() {
  ifstream input_file("input.txt");
  string line;
  bool seen_empty_line = false;
  vector<long long> ing_ids;
  vector<pair<long long, long long>> ranges;
  while (getline(input_file, line)) {
    stringstream liness(line);
    if (seen_empty_line) {
      long long ing_id;
      liness >> ing_id;
      ing_ids.push_back(ing_id);
    } else {
      if (line.size() == 0) {
        seen_empty_line = true;
        continue;
      }
      long long sid, eid;
      char c;
      liness >> sid >> c >> eid;
      ranges.push_back({sid, eid});
    }
  }
  sort(ranges.begin(), ranges.end());
  vector<pair<long long, long long>> mranges;
  pair<long long, long long> cur = ranges[0];
  long long all_fresh_cnt = 0;
  for (auto r : ranges) {
    if (cur.second < r.first) {
      all_fresh_cnt += cur.second - cur.first + 1;
      mranges.push_back(cur);
      cur = r;
    } else {
      cur.second = max(cur.second, r.second);
    }
  }
  all_fresh_cnt += cur.second - cur.first + 1;
  mranges.push_back(cur);

  int fresh_cnt = 0;
  for (auto ing_id : ing_ids) {
    // it > ing_id
    auto it = upper_bound(mranges.begin(), mranges.end(),
                          make_pair(ing_id, numeric_limits<long long>::max()));
    if (it == mranges.begin())
      continue;
    --it;
    // it <= ing_id
    if (it->second >= ing_id)
      ++fresh_cnt;
  }
  cout << fresh_cnt << endl;
  cout << all_fresh_cnt << endl;

  return 0;
}
