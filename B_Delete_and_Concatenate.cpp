#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, C;
    cin >> N >> C;
    vector<i64> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        A[i] -= C;
    }
    ranges::sort(A);
    auto ans = 0LL;
    for (auto i = 0; i < N / 2; ++i) {
        ans += max(0LL, A[i]);
    }
    for (auto i = N / 2; i < N; ++i) {
        ans += A[i];
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
