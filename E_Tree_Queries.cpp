#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

auto Bi(auto G) {
    auto N = int(G.size());
    vector<pair<int, int>> E;
    for (auto i = 0; i < N; ++i) {
        for (auto j : G[i]) {
            if (i < j) {
                E.emplace_back(i, j);
            } else {
                E.emplace_back(j, i);
            }
        }
    }
    ranges::sort(E);
    E.erase(unique(begin(E), end(E)), end(E));
    vector<vector<int>> adj(N);
    for (auto [u, v] : E) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    return adj;
}

auto Bi2(auto G) {
    auto N = int(G.size());
    vector<tuple<int, int, int>> E;
    for (auto i = 0; i < N; ++i) {
        for (auto [j, w] : G[i]) {
            if (i < j) {
                E.emplace_back(i, j, w);
            } else {
                E.emplace_back(j, i, w);
            }
        }
    }
    ranges::sort(E);
    E.erase(unique(begin(E), end(E)), end(E));
    vector<vector<pair<int, int>>> adj(N);
    for (auto [u, v, w] : E) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    return adj;
}

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> frag_id;
    const int sq = 400;
    int root = 0;
    vector<int> depth(N, 0);
    vector<int> dfs_order;
    auto dfs = [&](auto &&self, int u, int p) -> void {
        dfs_order.push_back(u);
        for (auto v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                self(self, v, u);
            }
        }
    };
    dfs(dfs, root, -1);
    vector<int> sz(N, 0);
    auto nvirt = 0;
    for (auto u : dfs_order | views::reverse) {
        sz[u] = 1;
        auto sum = 0;
        vector<int> bucket, children;
        for (auto v : adj[u])
            if (depth[u] < depth[v])
                sz[u] += sz[v];
        for (auto v : adj[u]) {
            if (depth[u] < depth[v]) {
                sum += sz[v];
                bucket.push_back(v);
                if (sum > sq) {
                    int nd = int(adj.size());
                    adj.push_back(bucket);
                    bucket.clear();
                    children.push_back(nd);
                    sz[u] -= sum;
                    sum = 0;
                    ++nvirt;
                }
            }
        }
        bucket.insert(bucket.end(), children.begin(), children.end());
        swap(adj[u], bucket);
    }
    auto iroot = int(adj.size());
    adj.push_back({root});
    nvirt++;
    frag_id.assign(N, -1);
    vector<vector<pair<int, int>>> adj_virt(nvirt);
    auto build = [&](auto &self, int u, int id, int dist) -> void {
        if (N <= u) {
            int new_id = u - N;
            if (id != -1 && id != new_id) {
                adj_virt[id].emplace_back(new_id, dist);
            }
            dist = 0;
            id = new_id;
        } else {
            frag_id[u] = id;
        }
        for (int v : adj[u]) {
            auto w = int(v < N);
            self(self, v, id, dist + w);
        }
    };
    build(build, iroot, -1, 0);
    adj = Bi(adj);
    adj_virt = Bi2(adj_virt);
    vector<int> hit(nvirt), color(N);
    auto dfs1 = [&](auto &&self, auto &&other, int u, int p, bool flag, int group) -> int {
        if (u < N && color[u]) {
            return -1;
        }
        auto ret = 0;
        for (auto v : adj[u]) {
            if (flag && (v - N == group || (v < N && frag_id[v] == group)))
                continue;
            if (v == p)
                continue;
            if (v < N) {
                ret = max(ret, 1 + self(self, other, v, u, false, -1));
            } else {
                if (hit[v - N] ) {
                    ret = max(ret, self(self, other, v, u, false, -1));
                } else {
                    ret = max(ret, other(other, self, v - N, u < N ? frag_id[u] : u - N));
                }
            }
        }
        return ret;
    };
    auto dfs2 = [&](auto &&self, auto &&other, int u, int p) -> int {
        auto ret = 0;
        for (auto [v, w] : adj_virt[u]) {
            if (v == p)
                continue;
            if (hit[v]) {
                ret = max(ret, w + other(other, self, v + N, v + N, true, u));
            } else {
                ret = max(ret, w + self(self, other, v, u));
            }
        }
        return ret;
    };
    while (Q--) {
        int X, K;
        cin >> X >> K;
        --X;
        vector<int> A(K);
        for (auto i = 0; i < K; ++i) {
            cin >> A[i];
            --A[i];
            hit[frag_id[A[i]]] = 1;
            color[A[i]] = 1;
        }
        cout << dfs1(dfs1, dfs2, X, -1, false, -1) << "\n";
        for (auto i = 0; i < K; ++i) {
            hit[frag_id[A[i]]] = 0;
            color[A[i]] = 0;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
