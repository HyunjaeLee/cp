#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

void solve() {
    int L, R;
    cin >> L >> R;
    vector<array<int, 3>> edges;
    auto add = [&](int u, int v, int w) {
        assert(-1 <= u && u < v && v <= 21 && 1 <= w && w <= 1'000'000);
        edges.push_back({u + 2, v + 2, w});
    };
    for (auto i = 0; i <= 21; ++i) {
        add(-1, i, L);
    }
    for (auto i = 0; i < 20; ++i) {
        for (auto j = i + 1; j <= 20; ++j) {
            add(i, j, 1 << i);
        }
    }
    for (auto i = 0, w = 1; i < 20; ++i) {
        if ((((R - L) >> i) & 1) == 0)
            continue;
        add(i, 21, w);
        w += 1 << i;
    }
    cout << "YES\n";
    cout << 23 << " " << edges.size() << "\n";
    for (auto [u, v, w] : edges) {
        cout << u << " " << v << " " << w << "\n";
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
