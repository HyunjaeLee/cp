#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    auto ans = 0;
    for (auto i = 0; i < N; ++i) {
        i64 x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (y1 * y2 < 0)
            ans++;
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
