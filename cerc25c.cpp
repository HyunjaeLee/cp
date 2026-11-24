#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<vector<pair<int, int>>> adj(N);
    vector<int> deg(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        deg[u]++;
        deg[v]++;
        if (w) {
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
    }
    vector<int> parent(N, -1), sz(N, 1), color(N), is_leaf(N);
    for (auto i = 0; i < N; ++i) {
        is_leaf[i] = deg[i] == 1;
    }
    auto dfs0 = [&](this auto &&self, int u) -> void {
        color[u] = 1;
        for (auto [v, w] : adj[u]) {
            adj[v].erase(ranges::find(adj[v], pair{u, w}));
            parent[v] = u;
            self(v);
            sz[u] += sz[v];
        }
        for (auto i = 0; i < ssize(adj[u]); ++i) {
            if (sz[adj[u][0].first] < sz[adj[u][i].first]) {
                swap(adj[u][0], adj[u][i]);
            }
        }
    };
    vector<int> X(N);
    auto dfs1 = [&](this auto &&self, int u, int wp) -> void {
        // chain compress
        if (parent[u] != -1 && adj[u].size() == 1) {
            auto [v, w] = adj[u][0];
            self(v, min(wp, w));
            X[u] = X[v];
            return;
        }
        auto sum = is_leaf[u];
        for (auto [v, w] : adj[u] | views::drop(1)) {
            self(v, w);
            sum += X[v];
        }
        // handle the largest with a extra constraint
        if (!adj[u].empty()) {
            auto [v, w] = adj[u][0];
            self(v, min(w, sum + wp));
            sum += X[v];
        }
        for (auto [v, w] : adj[u]) {
            sum -= X[v];
            if (sum + wp < X[v]) {
                self(v, sum + wp);
            }
            sum += X[v];
        }
        if (parent[u] == -1 && (sum & 1)) { // is root
            cout << "-1\n";
            exit(0);
        }
        if (sum <= wp) {
            X[u] = sum;
        } else {
            X[u] = sum - 2 * ((sum - wp + 1) / 2);
        }
        assert(X[u] <= wp);
    };
    for (auto i = 0; i < N; ++i) {
        if (color[i])
            continue;
        dfs0(i);
        dfs1(i, 0);
    }
    i64 ans = 0;
    for (auto i = 0; i < N; ++i) {
        ans += X[i];
    }
    cout << ans << "\n";
}
