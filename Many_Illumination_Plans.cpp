#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, X;
    cin >> N >> X;
    vector<int> P(N);
    vector<vector<int>> g(N);
    for (auto i = 1; i < N; ++i) {
        cin >> P[i];
        --P[i];
        g[P[i]].push_back(i);
    }
    vector<i64> B(N);
    vector<int> W(N), C(N);
    for (auto i = 0; i < N; ++i) {
        cin >> B[i] >> W[i] >> C[i];
    }
    vector<int> sz(N, 1);
    [&](this auto &&self, int u) -> void {
        for (auto &v : g[u]) {
            self(v);
            sz[u] += sz[v];
            if (sz[g[u][0]] < sz[v]) {
                swap(g[u][0], v);
            }
        }
    }(0);
    vector<i64> ans(N);
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    auto dfs = [&](this auto &&self, int u, const vector<i64> &dp_par, bool is_root) -> array<vector<i64>, 2> {
        array<vector<i64>, 2> dp_ch;
        if (g[u].empty()) {
            dp_ch = {dp_par, dp_par};
        } else {
            dp_ch = self(g[u][0], dp_par, is_root);
            for (auto v : g[u] | views::drop(1)) {
                dp_ch[0] = self(v, dp_ch[0], false)[0];
                dp_ch[1] = self(v, dp_ch[1], false)[1];
                if (is_root) {
                    self(v, dp_par, true);
                }
            }
        }
        vector<i64> dp(X + 1, -inf);
        auto dp_ret = dp_ch;
        for (auto i = 0; i + W[u] <= X; ++i) {
            dp[i + W[u]] = dp_ch[C[u] ^ 1][i] + B[u];
            dp_ret[C[u]][i + W[u]] = max(dp_ret[C[u]][i + W[u]], dp[i + W[u]]);
        }
        if (is_root) {
            ans[u] = ranges::max(dp);
        }
        return dp_ret;
    };
    vector<i64> init(X + 1, -inf);
    init[0] = 0;
    dfs(0, init, true);
    for (auto x : ans) {
        cout << x << "\n";
    }
}
