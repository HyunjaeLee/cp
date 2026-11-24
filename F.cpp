#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    int v1, v2, v3, w1, w2;
    cin >> v1 >> v2 >> v3 >> w1 >> w2;
    --v1, --v2, --v3;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto bfs = [&](int S) {
        queue<int> q;
        q.emplace(S);
        vector<int> dist(N, -1);
        dist[S] = 0;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.emplace(v);
                }
            }
        }
        return dist;
    };
    auto d1 = bfs(v1);
    auto d2 = bfs(v2);
    auto d3 = bfs(v3);
    auto ans = numeric_limits<i64>::max();
    for (auto i = 0; i < N; ++i) {
        auto p = d1[i] * i64(w1) * w1;
        auto q = d2[i] * i64(w1) * (w1 + w2);
        auto r = d3[i] * i64(w2) * w2;
        ans = min(ans, p + q + r);
    }
    cout << ans << "\n";
}
