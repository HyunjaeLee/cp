#include <atcoder/scc>
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
    int N, Q;
    cin >> N >> Q;
    vector<tuple<int, int, int>> E(Q);
    for (auto &[u, v, w] : E) {
        cin >> w >> v >> u;
        --u, --v;
        w *= -1;
    }
    atcoder::scc_graph G(N);
    for (auto [u, v, w] : E) {
        G.add_edge(u, v);
    }
    auto scc = G.scc();
    vector<int> id(N);
    for (auto i = 0; i < int(scc.size()); ++i) {
        for (auto x : scc[i]) {
            id[x] = i;
        }
    }
    for (auto [u, v, w] : E) {
        if (w == -1 && id[u] == id[v]) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    vector<vector<pair<int, int>>> adj(N);
    for (auto [u, v, w] : E) {
        adj[u].emplace_back(v, w);
    }
    vector<int> dp(N, N);
    for (auto s : scc) {
        for (auto u : s) {
            for (auto [v, w] : adj[u]) {
                dp[v] = min(dp[v], dp[u] + w);
            }
        }
    }
    show(dp);
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
