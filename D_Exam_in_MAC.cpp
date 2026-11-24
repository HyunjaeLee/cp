#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 N, C;
    cin >> N >> C;
    vector<i64> A(N);
    copy_n(istream_iterator<i64>(cin), N, begin(A));
    i64 cnt = 0;
    for (auto i = 0; i < N; ++i) {
        cnt += A[i] / 2 + 1;
    }
    for (auto i = 0; i < N; ++i) {
        cnt += C - A[i] + 1;
    }
    i64 odd = 0, even = 0;
    for (auto i = 0; i < N; ++i) {
        if (A[i] & 1)
            odd += 1;
        else
            even += 1;
    }
    cnt -= odd * (odd + 1) / 2 + even * (even + 1) / 2;
    auto ans = (C + 1) * (C + 2) / 2 - cnt;
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
