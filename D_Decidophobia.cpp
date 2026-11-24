#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 N, D;
    cin >> N >> D;
    vector<i64> A(N), pref(3 * N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        pref[i] = pref[i + N] = pref[i + 2 * N] = A[i];
    }
    for (auto i = 1; i < 3 * N; ++i) {
        pref[i] += pref[i - 1];
    }
    vector<i64> B(N);
    for (auto i = 0; i < N; ++i) {
        auto L = i - D + N;
        auto R = i + D + N;
        B[i] = (2 * D + 1) * A[i] - (pref[R] - pref[L - 1]);
    }
    auto ans = 0LL;
    for (auto i = 0; i < N; ++i) {
        ans += max(0LL, B[i]);
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
