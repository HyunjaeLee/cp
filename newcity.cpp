#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &x : A)
        cin >> x;
    auto M = ranges::max(A);
    vector<int> B(M + 1);
    for (auto i = 1; i <= M; ++i) {
        cin >> B[i];
    }
    for (auto i = 0; i < M; ++i) {
        B[i + 1] = max(B[i + 1], B[i]);
    }
    i64 ans = 0;
    for (auto i = 0; i < N; ++i) {
        ans += B[A[i]];
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
