#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    A[0] = 1;
    for (auto i = 1; i < N; ++i) {
        cin >> A[i];
    }
    vector<int> B(N);
    for (auto i = 0; i < N; ++i) {
        cin >> B[i];
    }
    ranges::sort(A);
    ranges::sort(B);
    auto p = 0;
    auto ans = N;
    for (auto i = 0; i < N; ++i) {
        while (p < N && B[p] <= A[i]) {
            ++p;
        }
        if (p < N) {
            ans -= 1;
            ++p;
        }
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
