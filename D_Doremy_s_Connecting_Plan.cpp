#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 N, C;
    cin >> N >> C;
    vector<i64> A(N);
    for (i64 i = 0; i < N; ++i) {
        cin >> A[i];
    }
    vector<pair<i64, i64>> B;
    for (i64 i = 1; i < N; ++i) {
        B.emplace_back(C * (i + 1) - A[i], i);
    }
    ranges::sort(B);
    i64 sum = A[0];
    for (auto [x, i] : B) {
        if (sum < x) {
            cout << "No\n";
            return;
        }
        sum += A[i];
    }
    cout << "Yes\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
