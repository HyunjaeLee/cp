#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
using Z = atcoder::modint998244353;

void solve() {
    i64 N;
    cin >> N;
    map<i64, pair<Z, Z>> dp;
    auto F = [&](auto &&self, i64 n) -> pair<Z, Z> {
        if (n == 1) {
            return {1, 0};
        }
        if (dp.contains(n)) {
            return dp[n];
        }
        auto l = (n + 1) / 2;
        auto r = n / 2;
        auto [al, bl] = self(self, l);
        auto [ar, br] = self(self, r);
        return dp[n] = {2 * al + 2 * ar + (Z(2).pow(l) - 1) * (Z(2).pow(r) - 1), bl + ar + br};
    };
    auto [a, b] = F(F, N);
    auto ans = a + b;
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
