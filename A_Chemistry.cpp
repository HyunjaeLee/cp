#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> f('z' + 1);
    string S;
    cin >> S;
    for (auto i = 0; i < N; ++i) {
        f[S[i]] += 1;
    }
    auto cnt = 0;
    for (int i = 'a'; i <= 'z'; ++i) {
        if (0 < K && f[i] % 2 == 1) {
            f[i] -= 1;
            K -= 1;
        }
        if (f[i] & 1) {
            cnt++;
        }
    }
    auto ok = cnt <= 1;
    cout << (ok ? "YES" : "NO") << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
