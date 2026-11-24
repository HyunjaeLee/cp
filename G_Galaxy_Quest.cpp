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
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<array<double, 3>> A(N);
    for (auto &[x, y, z] : A) {
        cin >> x >> y >> z;
    }
    vector<vector<pair<int, double>>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        auto dx = A[v][0] - A[u][0];
        auto dy = A[v][1] - A[u][1];
        auto dz = A[v][2] - A[u][2];
        auto w = 2 * sqrt(sqrt(dx * dx + dy * dy + dz * dz));
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    constexpr auto inf = numeric_limits<double>::infinity();
    vector<double> dist(N, inf);
    dist[0] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    pq.emplace(dist[0], 0);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] < d)
            continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    cout << fixed << setprecision(9);
    while (Q--) {
        int x, t;
        cin >> x >> t;
        --x;
        auto d = dist[x];
        if (t < d) {
            cout << "impossible\n";
            continue;
        }
        auto ans = t - sqrt(t * t - d * d);
        cout << ans << "\n";
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
