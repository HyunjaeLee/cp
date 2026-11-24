#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    array<int, 3> A;
    copy_n(istream_iterator<int>(cin), 3, begin(A));
    if ((A[0] + A[1] + A[2]) & 1) {
        cout << -1 << "\n";
        return;
    }
    A[2] = min(A[2], A[0] + A[1]);
    auto n = A[0] + A[1] + A[2];
    auto ans = n / 2;
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
