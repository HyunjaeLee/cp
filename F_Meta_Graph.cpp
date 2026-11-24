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
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    --r1, --c1, --r2, --c2;
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (auto i = 0; i < N; ++i) {
        ranges::sort(G[i]);
    }
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto ans = inf;
    map<pair<int, int>, int> dist;
    dist[{r1, c1}] = 0;
    {
        vector<int> d(N, -1);
        d[c1] = 0;
        queue<int> q;
        q.push(c1);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : G[u]) {
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        if (r1 == r2) {
            ans = min(ans, d[c2]);
        }
        for (auto v : G[r1]) {
            dist[{r1, v}] = d[v];
        }
    }
    {
        vector<int> level(N, inf);
        level[r1] = 0;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        for (auto v : G[r1]) {
            pq.emplace(dist[{r1, v}], r1, v);
        }
        while (!pq.empty()) {
            auto [d, r, c] = pq.top();
            pq.pop();
            if (d != dist[{r, c}])
                continue;
            if (!dist.contains({c, r}) || d + 1 < dist[{c, r}]) {
                dist[{c, r}] = d + 1;
                pq.emplace(d + 1, c, r);
            }
            if (level[c] <= d + 1)
                continue;
            level[c] = d + 1;
            for (auto v : G[c]) {
                if (!dist.contains({c, v}) || d + 3 < dist[{c, v}]) {
                    dist[{c, v}] = d + 3;
                    pq.emplace(d + 3, c, v);
                }
            }
        }
    }
    {
        vector<int> d(N, -1);
        queue<int> q;
        d[c2] = 0;
        q.push(c2);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : G[u]) {
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        for (auto v : G[r2]) {
            ans = min(ans, d[v] + dist[{r2, v}]);
        }
    }
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
