#include <bits/stdc++.h>
using namespace std;

template <typename T, T inf = numeric_limits<T>::max() / 2>
optional<vector<T>> goldberg_radzik(const auto &g, int src) {
    auto n = int(g.size());
    vector<T> dist(n, inf);
    dist[src] = 0;
    vector<int> cur{src}, nxt, order;
    vector<int> state(n); // -t: in stack/labeled, t: visited
    for (auto t = 1; !cur.empty(); ++t) {
        order.clear();
        auto dfs = [&](auto &&self, int u) {
            if (state[u] == t || state[u] == -t) return state[u] == t;
            state[u] = -t;
            for (auto [v, w] : g[u]) {
                if (dist[v] <= dist[u] + w) continue;
                dist[v] = dist[u] + w;
                if (!self(self, v)) return false;
            }
            state[u] = t;
            order.push_back(u);
            return true;
        };
        for (auto u : cur) {
            if (state[u] == t) continue;
            auto can_relax = false;
            for (auto [v, w] : g[u]) {
                if (dist[u] + w < dist[v]) {
                    can_relax = true;
                    break;
                }
            }
            if (can_relax && !dfs(dfs, u)) return nullopt;
        }
        nxt.clear();
        for (auto u : order | views::reverse) {
            for (auto [v, w] : g[u]) {
                if (dist[v] <= dist[u] + w) continue;
                dist[v] = dist[u] + w;
                if (state[v] != -t) {
                    state[v] = -t;
                    nxt.push_back(v);
                }
            }
        }
        swap(cur, nxt);
    }
    return dist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, S;
    cin >> N >> M >> S;
    constexpr auto inf = numeric_limits<int>::max() / 2;
    vector<vector<pair<int, int>>> g(N);
    for (auto i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }
    auto opt = goldberg_radzik<int, inf>(g, S);
    if (!opt) {
        cout << "NEGATIVE CYCLE\n";
        return 0;
    }
    auto dist = *opt;
    for (auto i = 0; i < N; ++i) {
        if (dist[i] == inf) {
            cout << "INF\n";
        } else {
            cout << dist[i] << "\n";
        }
    }
}
