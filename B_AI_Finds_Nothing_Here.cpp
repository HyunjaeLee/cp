#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
using Z = atcoder::modint998244353;

void solve() {
    i64 n, m, r, c;
    cin >> n >> m >> r >> c;
    auto p = n * m - (n - r + 1) * (m - c + 1);
    auto ans = Z(2).pow(p);
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
