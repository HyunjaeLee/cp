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
    int N, K;
    cin >> N >> K;
    if (N % 2 == 0) {
        cout << "-1\n";
        return;
    }
    auto g = gcd(N, K);
    vector<vector<int>> A(N / g, vector<int>(g));
    ranges::iota(A[0], 0);
    for (auto i = 1; i < N / g; ++i) {
        for (auto j = 0; j < g; ++j) {
            A[i][j] = (A[i - 1][j] + K) % N;
        }
    }
    vector<pair<int, int>> ans;
    auto add = [&](pair<int, int> a, pair<int, int> b) {
        auto [r1, c1] = a;
        auto [r2, c2] = b;
        auto u = A[r1][c1];
        auto v = A[r2][c2];
        ans.emplace_back(u, v);
    };
    for (auto i = 0; i < N / g - 1; i += 2) {
        for (auto j = 0; j < g; j += 2) {
            add({i, j}, {i + 1, j});
        }
    }
    for (auto i = 0; i < N / g - 1; i += 2) {
        for (auto j = 0; j < g - 1; j += 2) {
            add({i, j}, {i, j + 1});
        }
    }
    for (auto j = 1; j < g; j += 2) {
        add({N / g - 2, j}, {N / g - 2, j + 1});
    }
    auto M = int(ans.size());
    assert(2 * M == N - 1);
    cout << M << "\n";
    for (auto [u, v] : ans) {
        cout << u << " " << v << "\n";
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
