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
    vector<i64> A(N);
    read(A);
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> subtree(N, 1);
    vector<i64> S = A;
    vector<int> parent(N, -1);
    vector<set<pair<int, int>>> G(N);
    [&](this auto &&self, int u) -> void {
        for (auto v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                self(v);
                subtree[u] += subtree[v];
                S[u] += S[v];
                G[u].emplace(-subtree[v], v);
            }
        }
    }(0);
    while (Q--) {
        int t, x;
        cin >> t >> x;
        --x;
        if (t == 1) {
            auto ans = S[x];
            cout << ans << "\n";
        } else {
            auto it = G[x].begin();
            if (it == G[x].end())
                continue;
            auto p = parent[x];
            auto y = it->second;
            parent[y] = p;
            parent[x] = y;
            G[p].erase(pair(-subtree[x], x));
            G[x].erase(it);
            {
                auto a = subtree[x] - subtree[y];
                auto b = subtree[x];
                subtree[x] = a;
                subtree[y] = b;
            }
            {
                auto a = S[x] - S[y];
                auto b = S[x];
                S[x] = a;
                S[y] = b;
            }
            G[y].emplace(-subtree[x], x);
            G[p].emplace(-subtree[y], y);
        }
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
