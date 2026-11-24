#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 a, b, n;
    cin >> a >> b >> n;
    vector<i64> X(n);
    for (auto i = 0; i < n; ++i) {
        cin >> X[i];
    }
    auto ans = b;
    for (auto i = 0; i < n; ++i) {
        ans += min(1 + X[i], a) - 1;
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
