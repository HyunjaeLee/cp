#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, S;
    cin >> N >> S;
    vector<int> W(N), V(N);
    for (auto i = 0; i < N; ++i) {
        cin >> W[i] >> V[i];
    }
    vector<vector<int>> g(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> sz(N, 1);
    [&](this auto &&self, int u) -> void {
        for (auto &v : g[u]) {
            g[v].erase(ranges::find(g[v], u));
            self(v);
            sz[u] += sz[v];
            if (sz[g[u][0]] < sz[v]) {
                swap(g[u][0], v);
            }
        }
    }(0);
    // dp[0] = 정답
    // dp[1] = subtree root를 포함하지 않는 경우
    auto dfs = [&](this auto &&self, int u, const vector<int> &dpp) -> array<vector<int>, 2> {
        array<vector<int>, 2> dp;
        if (!g[u].empty()) {
            dp = self(g[u][0], dpp);
            for (auto v : g[u] | views::drop(1)) {
                dp[0] = self(v, dp[0])[0];
                dp[1] = self(v, dp[1])[1];
            }
        } else {
            dp = {dpp, dpp};
        }
        for (auto i = S; 0 <= i; --i) {
            dp[1][i] = dp[0][i];
            if (0 <= i - W[u]) {
                dp[0][i] = max(dp[0][i], dp[1][i - W[u]] + V[u]);
            }
        }
        return dp;
    };
    constexpr auto inf = numeric_limits<int>::max() / 2;
    vector<int> init(S + 1, -inf);
    init[0] = 0;
    auto dp = dfs(0, init);
    auto ans = ranges::max(dp[0]);
    cout << ans << "\n";
}
