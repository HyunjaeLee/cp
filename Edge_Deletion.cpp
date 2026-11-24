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
    int N, M;
    cin >> N >> M;
    vector<array<int, 3>> E(M);
    vector<vector<pair<int, i64>>> adj(N);
    for (auto &[u, v, w] : E) {
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    set<pair<int, int>> S;
    constexpr auto inf = numeric_limits<i64>::max() / 4;
    for (auto i = 0; i < N; ++i) {
        priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> pq;
        vector<i64> dist(N, inf);
        dist[i] = 0;
        pq.emplace(dist[i], i);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        vector<vector<int>> in(N);
        for (auto [u, v, w] : E) {
            if (dist[u] + w == dist[v]) {
                in[v].push_back(u);
            } else if (dist[v] + w == dist[u]) {
                in[u].push_back(v);
            }
        }
        for (auto v = 0; v < N; ++v) {
            if (in[v].size() == 1) {
                auto u = in[v][0];
                S.insert(minmax({u, v}));
            }
        }
    }
    auto ans = M - int(S.size());
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
