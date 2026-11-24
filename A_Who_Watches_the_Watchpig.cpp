#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, K;
    string S;
    cin >> N >> K >> S;
    if (N < 2 * K) {
        cout << "-1\n";
        return;
    }
    auto ans = 0;
    for (auto i = 0; i < K; ++i) {
        if (S[i] == 'L') {
            ans += 1;
        }
    }
    for (auto i = 0; i < K; ++i) {
        if (S[N - 1 - i] == 'R') {
            ans += 1;
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
