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
    vector<vector<pair<int, int>>> adj(N);
    vector<int> indegree(N);
    for (auto i = 0; i < N; ++i) {
        int k;
        cin >> k;
        for (auto j = 0; j < k; ++j) {
            int a;
            cin >> a;
            --a;
            auto w = a < i ? 0 : 1;
            adj[a].emplace_back(i, w);
            indegree[i] += 1;
        }
    }
    queue<int> q;
    for (auto i = 0; i < N; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    vector<int> order;
    for (auto i = 0; i < N; ++i) {
        if (q.empty()) {
            cout << "-1\n";
            return;
        }
        auto u = q.front();
        q.pop();
        order.push_back(u);
        for (auto [v, w] : adj[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    vector<int> dist(N);
    for (auto u : order) {
        for (auto [v, w] : adj[u]) {
            dist[v] = max(dist[v], dist[u] + w);
        }
    }
    auto ans = ranges::max(dist) + 1;
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
