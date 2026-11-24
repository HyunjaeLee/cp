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
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    vector<tuple<int, int, int>> ans;
    auto Act = [&](int r, int c, int s) { ans.emplace_back(r, c, s); };
    auto Fill = [&](int n, int m) {
        for (auto i = 0; i + 1 < n; i += 2) {
            for (auto j = 0; j + 1 < m; j += 2) {
                Act(i, j, 1);
            }
        }
    };
    if ((N & 1) && (M & 1)) {
        auto rec = [&](this auto &&self, int r, int c, int w) -> void {
            if (w <= 1)
                return;
            Act(r, c, w - 1);
            for (auto i = 0; i < (w - 3) / 2; ++i) {
                Act(r, c + 1 + 2 * i, 1);
                Act(r + 1 + 2 * i, c + w - 2, 1);
                Act(r + w - 2, c + w - 3 - 2 * i, 1);
                Act(r + w - 3 - 2 * i, c, 1);
            }
            self(r + 2, c + 2, w - 4);
        };
        if (N < M) {
            Fill(N, M - N);
            rec(0, M - N, N);
        } else {
            Fill(N - M, M);
            rec(N - M, 0, M);
        }
    } else {
        Fill(N, M);
    }
    cout << ans.size() << "\n";
    for (auto [r, c, s] : ans) {
        cout << r + 1 << " " << c + 1 << " " << s << "\n";
    }
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
