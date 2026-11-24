#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
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
    vector<vector<int>> adj_virt(nvirt);
    auto build = [&](auto &self, int u, int id) -> void {
        if (N <= u) {
            int new_id = u - N;
            if (id != -1 && id != new_id) {
                adj_virt[id].push_back(new_id);
            }
            id = new_id;
        } else {
            frag_id[u] = id;
        }
        for (int v : adj[u]) {
            self(self, v, id);
        }
    };
    build(build, iroot, -1);
    vector<map<int, int>> freq(nvirt); // (id, depth) -> cnt
    for (auto i = 0; i < N; ++i) {
        freq[frag_id[i]][depth[i]] += 1;
    }
    vector<i64> F(nvirt), D(N);
    auto update = [&](int d, i64 x) {
        D[d] += x;
        for (auto i = 0; i < nvirt; ++i) {
            if (freq[i].contains(d)) {
                F[i] += freq[i][d] * x;
            }
        }
    };
    auto query = [&](int u) {
        auto dfs_nisemono = [&](auto &&self, int u) -> i64 {
            auto ret = F[u];
            for (auto v : adj_virt[u])
                ret += self(self, v);
            return ret;
        };
        auto dfs_honmono = [&](auto &&self, int u) -> i64 {
            if (N <= u)
                return dfs_nisemono(dfs_nisemono, u - N);
            auto ret = D[depth[u]];
            for (auto v : adj[u])
                ret += self(self, v);
            return ret;
        };
        return dfs_honmono(dfs_honmono, u);
    };
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int d, x;
            cin >> d >> x;
            update(d, x);
        } else {
            int u;
            cin >> u;
            --u;
            auto ans = query(u);
            cout << ans << "\n";
        }
    }
}
