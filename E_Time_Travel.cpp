#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, T;
    cin >> N >> T;
    vector<vector<pair<int, int>>> adj(N);
    for (auto i = 0; i < T; ++i) {
        int M;
        cin >> M;
        for (auto j = 0; j < M; ++j) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].emplace_back(v, i);
            adj[v].emplace_back(u, i);
        }
    }
    int K;
    cin >> K;
    vector<int> A(K);
    for (auto i = 0; i < K; ++i) {
        cin >> A[i];
        --A[i];
    }
    vector<vector<int>> F(T);
    for (auto i = 0; i < K; ++i) {
        F[A[i]].push_back(i);
    }
    constexpr auto inf = numeric_limits<int>::max() / 2;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(N, inf);
    dist[0] = 0;
    pq.emplace(dist[0], 0);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u])
            continue;
        for (auto [v, x] : adj[u]) {
            auto it = ranges::lower_bound(F[x], d);
            if (it != F[x].end() && *it + 1 < dist[v]) {
                dist[v] = *it + 1;
                pq.emplace(dist[v], v);
            }
        }
    }
    auto ans = dist[N - 1] < inf ? dist[N - 1] : -1;
    cout << ans << "\n";
}
