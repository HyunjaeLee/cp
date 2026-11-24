#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, L, S, T;
    cin >> N >> M >> L >> S >> T;
    vector<vector<pair<int, int>>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
    }
    vector<int> color(N);
    auto dfs = [&](auto &&self, int u, int d, i64 acc) -> void {
        if (d == L) {
            if (S <= acc && acc <= T) {
                color[u] = 1;
            }
            return;
        }
        for (auto [v, w] : adj[u]) {
            self(self, v, d + 1, acc + w);
        }
    };
    dfs(dfs, 0, 0, 0);
    for (auto i = 0; i < N; ++i) {
        if (color[i]) {
            cout << i + 1 << " ";
        }
    }
}
