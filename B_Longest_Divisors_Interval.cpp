#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 N;
    cin >> N;
    i128 prod = 1;
    auto ans = 0;
    for (auto i = 1;; ++i) {
        prod = prod * i / __gcd<i64>((i64)prod, i);
        if (N % prod) {
            break;
        }
        ans += 1;
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
