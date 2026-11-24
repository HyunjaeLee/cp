#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
using Z = atcoder::modint998244353;

void solve() {
    int N, K;
    cin >> N >> K;
    vector<vector<Z>> dp(N + 1, vector<Z>(N + 1));
    vector<vector<char>> vis(N + 1, vector<char>(N + 1));
    auto f = [&](auto &&self, int n, int l) -> Z {
        if (n == 0)
            return 1;
        auto &ret = dp[n][l];
        if (vis[n][l])
            return ret;
        vis[n][l] = true;
        for (auto r = 0; r <= K - l - 1 && 0 <= n - (l + 1) * (r + 1); ++r) {
            ret += self(self, n - (l + 1) * (r + 1), r);
        }
        return ret;
    };
    Z ans = 0;
    for (auto l = 0; l < N; ++l) {
        ans += f(f, N, l);
    }
    cout << ans.val() << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
