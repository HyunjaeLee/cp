#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    i64 N, M, Y;
    cin >> N >> M >> Y;
    vector<vector<pair<int, i64>>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<i64> X(N);
    for (auto i = 0; i < N; ++i) {
        cin >> X[i];
    }
    constexpr auto inf = numeric_limits<i64>::max() / 4;
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> pq;
    vector<i64> dist(N, inf);
    pq.emplace(0, 0);
    dist[0] = 0;
    auto relax = [&] {
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (dist[u] != d) {
                continue;
            }
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
    };
    relax();
    auto best = 0;
    for (auto i = 0; i < N; ++i) {
        if (dist[i] + X[i] < dist[best] + X[best]) {
            best = i;
        }
    }
    for (auto i = 0; i < N; ++i) {
        auto d = dist[best] + X[best] + Y + X[i];
        if (d < dist[i]) {
            dist[i] = d;
            pq.emplace(d, i);
        }
    }
    relax();
    ranges::copy(dist | views::drop(1), ostream_iterator<i64>(cout, " "));
}
