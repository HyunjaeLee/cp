#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    i64 N, M, P;
    cin >> N >> M >> P;
    vector<vector<tuple<int, i64, int>>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v, w, a;
        cin >> u >> v >> w >> a;
        --u, --v;
        if (a || w <= P) {
            adj[u].emplace_back(v, w, a);
            adj[v].emplace_back(u, w, a);
        }
    }
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> pq;
    constexpr auto inf = numeric_limits<i64>::max() / 4;
    vector<i64> dist(N, inf);
    dist[0] = 0;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u])
            continue;
        for (auto [v, w, a] : adj[u]) {
            auto nd = dist[u] + w;
            if (!a && P < (dist[u] % P) + w) {
                nd = dist[u] + (P - dist[u] % P) + w;
            }
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.emplace(nd, v);
            }
        }
    }
    if (inf <= dist[N - 1]) {
        cout << "But I dont have 30k\n";
        return 0;
    }
    auto ans = (dist[N - 1] - 1) / P;
    cout << ans << "\n";
}
