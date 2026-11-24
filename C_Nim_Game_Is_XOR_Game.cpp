#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    auto sum = 0;
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        sum ^= A[i];
    }
    auto ans = 0;
    if (sum == 0) {
        ans = 1;
    }
    for (auto i = 0; i < N; ++i) {
        if ((A[i] ^ sum) < A[i]) {
            ans += 1;
        }
    }
    if (N == 1) {
        ans = 0;
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
