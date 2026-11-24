#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> X(N + 1), Y(N + 1);
    for (auto i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }
    auto ans = 2 * (ranges::max(X) - ranges::min(X) + ranges::max(Y) - ranges::min(Y));
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
