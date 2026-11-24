#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        --A[i];
    }
    auto cnt = 0;
    for (auto i = 0; i < N; ++i) {
        if (A[i] == i) {
            cnt += 1;
        }
    }
    int ans = (cnt / 2) + (cnt % 2);
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
