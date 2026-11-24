#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

#ifndef CEIL_DIV_HPP
#define CEIL_DIV_HPP

template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }

#endif // CEIL_DIV_HPP

void solve() {
    i64 n, x, y, z;
    cin >> n >> x >> y >> z;
    auto a = ceil_div(n + 10 * y * z, 10 * y + x);
    auto b = ceil_div(n, x + y);
    auto ans = min(a, b);
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
