#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int n;
    string s;
    cin >> n >> s;
    auto r = s;
    ranges::reverse(r);
    if (s == r) {
        cout << r << "\n";
        return;
    }
    if (r < s) {
        if (n & 1) {
            cout << r << "\n";
        } else {
            cout << r + s << "\n";
        }
    } else {
        if (n & 1) {
            cout << s + r << "\n";
        } else {
            cout << s << "\n";
        }
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
