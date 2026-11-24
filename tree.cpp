#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> depth(N);
    vector<int> parent(N);
    auto dfs = [&](auto &&self, int u, int p) -> void {
        parent[u] = p;
        for (auto v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                self(self, v, u);
            }
        }
    };
    dfs(dfs, 0, -1);
    auto a = int(ranges::max_element(depth) - depth.begin());
    depth.assign(N, 0);
    dfs(dfs, a, -1);
    auto b = int(ranges::max_element(depth) - depth.begin());
    auto K = depth[b] + 1;
    vector<int> A;
    for (auto u = b; ~u; u = parent[u]) {
        A.push_back(u);
    }
    auto pos = K - 1;
    vector<int> ans;
    for (auto i = 0; i < K; ++i) {
        ans.push_back(A[pos] + 1);
        if (i & 1) {
            pos = pos + (K - 1 - i);
        } else {
            pos = pos - (K - 1 - i);
        }
    }
    cout << K << "\n";
    ranges::copy(ans | views::reverse, ostream_iterator<int>(cout, " "));
}
