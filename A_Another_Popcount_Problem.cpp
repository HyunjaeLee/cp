#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int n, k;
    cin >> n >> k;
    auto ans = 0;
    for (auto i = 0; i < 30; ++i) {
        auto x = 1 << i;
        if (i64(x) * k <= n) {
            n -= x * k;
            ans += k;
        } else {
            ans += n / x;
            break;
        }
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
