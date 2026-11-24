#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

template <typename T, T inf = numeric_limits<T>::max() / 2>
vector<T> bellman_ford(int n, const vector<tuple<int, int, T>> &edges, int src) {
    vector<T> dist(n, inf);
    dist[src] = 0;
    for (auto i = 0; i < n; ++i) {
        for (auto [u, v, w] : edges) {
            if (dist[u] < inf && dist[u] + w < dist[v]) {
                dist[v] = (i < n - 1) ? max(-inf, dist[u] + w) : -inf;
            }
        }
    }
    for (auto i = 0; i < n; ++i) {
        for (auto [u, v, w] : edges) {
            if (dist[u] == -inf) {
                dist[v] = -inf;
            }
        }
    }
    return dist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (true) {
        int N, M, Q, S;
        cin >> N >> M >> Q >> S;
        if (N == 0 && M == 0 && Q == 0 && S == 0) {
            break;
        }
        constexpr auto inf = numeric_limits<int>::max() / 2;
        vector<tuple<int, int, int>> edges(M);
        for (auto &[u, v, w] : edges) {
            cin >> u >> v >> w;
        }
        auto dist = bellman_ford(N, edges, S);
        for (auto i = 0; i < Q; ++i) {
            int u;
            cin >> u;
            if (dist[u] == inf) {
                cout << "Impossible\n";
            } else if (dist[u] == -inf) {
                cout << "-Infinity\n";
            } else {
                cout << dist[u] << "\n";
            }
        }
    }
}
