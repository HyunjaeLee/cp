#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 N, M;
    cin >> N >> M;
    vector<array<i64, 3>> A(N);
    for (auto &[t, l, r] : A) {
        cin >> t >> l >> r;
        r += 1;
    }
    i64 T = 0, L = M, R = M + 1;
    for (auto [t, l, r] : A) {
        auto d = t - T;
        L = max(L - d, l);
        R = min(R + d, r);
        T = t;
        if (R - L <= 0) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
