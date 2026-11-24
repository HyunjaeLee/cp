#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<i64> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    vector<i64> B(N);
    for (auto i = 0; i < N; ++i) {
        cin >> B[i];
    }
    auto sum = 0LL;
    for (auto i = 0; i < N; ++i) {
        sum += abs(A[i] - B[i]);
    }
    auto x = numeric_limits<i64>::min();
    for (auto i = 0; i < N; ++i) {
        x = max(x, -abs(A[i] - B[i]) - A[i] - B[i]);
    }
    auto y = numeric_limits<i64>::min();
    for (auto i = 0; i < N; ++i) {
        y = max(y, -abs(A[i] - B[i]) + A[i] + B[i]);
    }
    auto ans = max(sum, sum + x + y);
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
