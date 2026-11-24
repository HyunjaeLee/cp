#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 a, b, c;
    cin >> a >> b >> c;
    auto x = c / 2 + c % 2 + a;
    auto y = c / 2 + b;
    if (x > y) {
        cout << "First\n";
    } else {
        cout << "Second\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
