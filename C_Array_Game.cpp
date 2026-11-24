#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 N, K;
    cin >> N >> K;
    vector<i64> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    ranges::sort(A);
    auto ans = ranges::min(A);
    if (1 <= K) {
        for (auto i = 0; i < N - 1; ++i) {
            ans = min(ans, A[i + 1] - A[i]);
        }
    }
    if (2 <= K) {
        for (auto i = 0; i < N - 1; ++i) {
            for (auto j = i + 1; j < N; ++j) {
                auto x = A[j] - A[i];
                auto it = ranges::lower_bound(A, x);
                if (it != A.end()) {
                    ans = min(ans, *it - x);
                }
                if (it != A.begin()) {
                    ans = min(ans, x - *prev(it));
                }
            }
        }
    }
    if (3 <= K) {
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
