#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    auto query_cnt = 0;
    auto query = [&](int r1, int r2, int c1, int c2) { // [r1, r2) x [c1, c2)
        query_cnt += 1;
        assert(query_cnt <= 3 * N);
        cout << "? " << r1 + 1 << " " << c1 + 1 << " " << r2 << " " << c2 << endl;
        int x;
        cin >> x;
        return x;
    };
    auto cnt = 0;
    for (auto i = 0; i < N; ++i) {
        auto x = query(0, 2 * N, 2 * i, 2 * i + 2);
        if (x <= 1) {
            if (x == 0) {
                cnt += 2;
            } else {
                cnt += 1;
            }
        } else {
            auto y = query(0, 2 * N, 2 * i, 2 * i + 1);
            auto z = x - y;
            if (y == 0) {
                cnt += 1;
            }
            if (z == 0) {
                cnt += 1;
            }
        }
    }
    for (auto i = 0; i < N; ++i) {
        auto x = query(2 * i, 2 * i + 2, 0, 2 * N);
        if (x <= 1) {
            if (x == 0) {
                cnt += 2;
            } else {
                cnt += 1;
            }
        } else {
            auto y = query(2 * i, 2 * i + 1, 0, 2 * N);
            auto z = x - y;
            if (y == 0) {
                cnt += 1;
            }
            if (z == 0) {
                cnt += 1;
            }
        }
    }
    auto ans = 2 * (N - 2 * N) + cnt;
    cout << "! " << ans << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
