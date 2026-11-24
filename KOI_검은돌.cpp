#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (auto i = 0; i < M; ++i) {
        int x;
        cin >> x;
        --x;
        A[x] = 1;
    }
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int>> children(N);
    vector<int> order;
    [&](this auto &&self, int u, int p) -> void {
        for (auto v : adj[u]) {
            if (v == p)
                continue;
            children[u].push_back(v);
            self(v, u);
        }
        order.push_back(u);
    }(0, 0);
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto min_plus_convolution = [&](const vector<int> &a, const vector<int> &b) {
        auto n = int(a.size());
        auto m = int(b.size());
        vector<int> c(n + m - 1, inf);
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < m; ++j) {
                c[i + j] = min(c[i + j], a[i] + b[j]);
            }
        }
        return c;
    };
    auto max_plus_convolution = [&](const vector<int> &a, const vector<int> &b) {
        auto n = int(a.size());
        auto m = int(b.size());
        vector<int> c(n + m - 1, -inf);
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < m; ++j) {
                c[i + j] = max(c[i + j], a[i] + b[j]);
            }
        }
        return c;
    };
    vector<vector<int>> dp_min(N);
    for (auto u : order) {
        dp_min[u] = {inf, A[u]};
        for (auto v : children[u]) {
            dp_min[u] = min_plus_convolution(dp_min[u], dp_min[v]);
        }
        dp_min[u][0] = 0;
    }
    vector<vector<int>> dp_max(N);
    for (auto u : order) {
        dp_max[u] = {-inf, A[u]};
        for (auto v : children[u]) {
            dp_max[u] = max_plus_convolution(dp_max[u], dp_max[v]);
        }
        dp_max[u][0] = 0;
    }
    vector<int> L(N + 1, inf);
    for (const auto &a : dp_min) {
        for (auto i = 0; i < int(a.size()); ++i) {
            L[i] = min(L[i], a[i]);
        }
    }
    vector<int> R(N + 1, -inf);
    for (const auto &a : dp_max) {
        for (auto i = 0; i < int(a.size()); ++i) {
            R[i] = max(R[i], a[i]);
        }
    }
    auto ans = 0;
    int Q;
    cin >> Q;
    while (Q--) {
        int i, j;
        cin >> i >> j;
        if (L[i] <= j && j <= R[i]) {
            ++ans;
        }
    }
    cout << ans << "\n";
}
