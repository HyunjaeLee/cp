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

#define TC
void solve() {
    int N;
    cin >> N;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> parent(N, -1);
    vector<vector<int>> children(N);
    [&](this auto &&self, int u) -> void {
        for (auto v : adj[u]) {
            if (v == parent[u])
                continue;
            parent[v] = u;
            children[u].push_back(v);
            self(v);
        }
    }(0);
    constexpr auto inf = numeric_limits<i64>::max() / 4;
    auto K = 2 * (int(sqrt(N)) + 1);
    auto conv = [&](const vector<i64> &a, const vector<i64> &b) {
        auto n = int(a.size());
        auto m = int(b.size());
        vector<i64> c(min(K, n + m - 1), inf);
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < m && i + j < K; ++j) {
                c[i + j] = min(c[i + j], a[i] + b[j]);
            }
        }
        return c;
    };
    using S = array<vector<i64>, 2>;
    auto dp = [&](this auto &&self, int u) -> S {
        S a{{{inf, 0}, {inf, 0}}};
        for (auto v : children[u]) {
            auto b = self(v);
            a[0] = conv(a[0], b[0]);
            a[1] = conv(a[1], b[1]);
        }
        for (auto i = 0; i < 2; ++i) {
            for (auto j = 1; j < int(a[i ^ 1].size()); ++j) {
                a[i][0] = min(a[i][0], i64(j) * (j + 1) / 2 * (2 - i) + a[i ^ 1][j]);
            }
        }
        return a;
    }(0);
    auto ans = i64(N) * (N + 1) - min(dp[0][0], dp[1][0]);
    cout << ans << "\n";
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
