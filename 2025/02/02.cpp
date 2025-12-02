#include <bits/stdc++.h>

using namespace std;

long long closest_invalid(long long num) {
    auto num_str = to_string(num);
    int n = num_str.size();
    if (n%2 == 1) 
        return stoll("1" + string(n / 2,'0') + "1" + string(n / 2, '0'));
    auto half_str = num_str.substr(0, n/2);
    auto half2_str = half_str + half_str;
    if (half2_str >= num_str) return stoll(half2_str);
    half_str = to_string(stoll(half_str) + 1);
    half2_str = half_str + half_str;
    return stoll(half2_str);
}

set<long long> generate_invalids(long long fid, long long lid) {
    set<long long> invalids;

    auto fids = to_string(fid);
    auto lids = to_string(lid);
    for (int k = 2; k <= lids.size(); ++k) {
        int min_len = (fids.size() + k - 1) / k;
        if (min_len == 0) min_len = 1;
        int max_len = lids.size() / k;
        if (min_len > max_len) continue;
        long long min_num = stoll("1" + string(min_len - 1, '0'));
        long long max_num = stoll("1" + string(max_len , '0')) - 1;
        for (long long cur = min_num; cur <= max_num; ++cur) {
            string curs = to_string(cur);
            string curks;
            for (int kk = 0; kk < k; ++kk) curks += curs;
            auto curk_num = stoll(curks);
            if (curk_num > lid) break;
            else if (curk_num >= fid) invalids.insert(curk_num);
        }
    }

    return invalids;
}

int main() {
    ifstream input_file("input.txt");
    string input_line;
    input_file >> input_line;

    for (auto& c: input_line) {
        if (c == ',') c = ' ';
    }

    stringstream ss(input_line);

    long long fid, lid;
    char c;
    long long sum_of_invalids = 0;
    long long sum_of_invalids2 = 0;
    while (ss >> fid>>c>>lid)  {
        auto cur = closest_invalid(fid);
        while (cur <= lid){
            sum_of_invalids += cur++;
            cur = closest_invalid(cur);
        }
        auto st = generate_invalids(fid, lid);
        for (auto el: st) sum_of_invalids2 += el;
    }
    cout<<sum_of_invalids<<endl;
    cout<<sum_of_invalids2<<endl;

    return 0;
}
