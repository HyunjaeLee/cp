#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int n;
    cin >> n;
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto L = -inf, R = inf;
    vector<int> no;
    for (auto i = 0; i < n; ++i) {
        int a, x;
        cin >> a >> x;
        if (a == 1) {
            L = max(L, x);
        } else if (a == 2) {
            R = min(R, x);
        } else {
            no.push_back(x);
        }
    }
    auto ans = max(0, R - L + 1);
    for (auto x : no) {
        if (L <= x && x <= R) {
            ans -= 1;
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
