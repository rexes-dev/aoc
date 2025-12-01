#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ifstream input_file("input.txt");

    int dial = 50;
    int zero_cnt = 0;
    int zero_clicks = 0;

    char dir;
    int cnt;
    while (input_file>>dir>>cnt) {
        if (dir == 'L') {
            if (dial <= cnt)  {
                if (dial == 0) 
                    zero_clicks += cnt / 100;
                else 
                    zero_clicks += 1 + (cnt - dial) / 100;
            }
            dial -= cnt;
        }
        else {
            if (100 - dial <= cnt) {
                if (dial == 0) 
                    zero_clicks += cnt / 100;
                else
                    zero_clicks += 1 + (cnt - (100-dial)) / 100;
            }
            dial += cnt;
        }
        dial = (dial % 100 + 100) % 100;
        if (dial == 0) ++zero_cnt; 
    }
    cout<<zero_cnt<<endl;
    cout<<zero_clicks<<endl;

    return 0;
}
