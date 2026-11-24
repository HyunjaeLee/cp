#include <bits/stdc++.h>
using namespace std;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

void solve() {
    i64 n, m;
    cin >> n >> m;
    n %= m;
    if (n == 0) {
        cout << "0\n";
        return;
    }
    auto p = 1;
    auto x = m;
    auto ans = 0LL;
    while (0 < n && (x & 1) == 0) {
        x /= 2;
        n *= 2;
        if (m <= n) {
            n -= m;
            ans += ((1LL << p) - 1) * x;
        }
        p++;
    }
    if (0 < n) {
        cout << "-1\n";
        return;
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
