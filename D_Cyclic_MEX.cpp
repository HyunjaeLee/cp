#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int op(int a, int b) { return max(a, b); }

int e() { return -1; }

void solve() {
    int N;
    cin >> N;
    vector<int> A(2 * N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        A[N + i] = A[i];
    }
    constexpr auto P = 20;
    vector<vector<int>> F(P, vector<int>(2 * N));
    atcoder::segtree<int, op, e> seg(2 * N);
    for (auto i = 0; i < 2 * N; ++i) {
        F[0][i] = seg.prod(0, A[i]);
        seg.set(A[i], i);
    }
    for (auto i = 1; i < P; ++i) {
        for (auto j = 0; j < 2 * N; ++j) {
            if (F[i - 1][j] != -1) {
                F[i][j] = F[i - 1][F[i - 1][j]];
            }
        }
    }
    vector<i64> dp(2 * N);
    for (auto i = 0; i < 2 * N; ++i) {
        dp[i] = i64(i - F[0][i]) * A[i];
        if (F[0][i] != -1) {
            dp[i] += dp[F[0][i]];
        }
    }
    auto ans = 0LL;
    for (auto l = 0; l < N; ++l) {
        auto r = l + N;
        auto x = r - 1;
        for (auto i = P - 1; 0 <= i; --i) {
            if (l <= F[i][x]) {
                x = F[i][x];
            }
        }
        auto sum = dp[r - 1] - dp[x] + i64(x - l + 1) * A[x];
        ans = max(ans, sum);
    }
    ans += N;
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
