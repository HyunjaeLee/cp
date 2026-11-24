#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
}
// clang-format on

void solve() {
    i64 N, M, K;
    cin >> N >> M >> K;
    vector<i64> X(N);
    read(X);
    ranges::sort(X);
    i64 max_cnt = -1;
    i64 pos = -1;
    auto Frieren = [&](i64 x) {
        i64 cnt = 0;
        {
            auto r = ranges::upper_bound(X, x) - X.begin();
            auto l = r - K;
            if (0 <= l) {
                auto y = X[l] + 1;
                if ((x - y) & 1) {
                    ++y;
                }
                cnt += (x - y) / 2 + 1;
            } else {
                cnt += x + 1;
            }
        }
        {
            auto l = ranges::lower_bound(X, x) - X.begin();
            auto r = l + K - 1;
            if (r < N) {
                auto y = X[r] - 1;
                if ((y - x) & 1) {
                    --y;
                }
                cnt += (y - x) / 2 + 1;
            } else {
                cnt += M + 1 - x;
            }
        }
        cnt = max(0LL, cnt - 1);
        if (max_cnt < cnt) {
            max_cnt = cnt;
            pos = x;
        } else if (max_cnt == cnt) {
            pos = min(pos, x);
        }
    };
    Frieren(0);
    for (auto i = 0; i < N; ++i) {
        for (auto j = -2; j <= 2; ++j) {
            Frieren(clamp(X[i] + j, 0LL, M));
        }
    }
    cout << max_cnt << " " << pos << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
