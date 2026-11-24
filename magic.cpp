#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    auto S = 0;
    auto used = false;
    auto Query = [&](int a, int b) {
        S += a;
        cout << a << " " << b << endl;
    };
    auto seed = chrono::steady_clock::now().time_since_epoch().count();
    auto g = mt19937_64(seed);
    uniform_int_distribution<> dist(1, 13);
    while (true) {
        int x;
        cin >> x;
        if (x == -1) {
            return 0;
        }
        S += x;
        if (S < 550) {
            Query(dist(g), 0);
        } else {
            if (used) {
                Query(14 - x, 0);
            } else {
                Query(1, 1);
                int y;
                cin >> y;
                Query(12, 0);
                used = true;
            }
        }
    }
}
