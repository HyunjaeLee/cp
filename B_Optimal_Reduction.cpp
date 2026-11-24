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
    }
    auto it = ranges::max_element(A);
    auto p = int(it - A.begin());
    for (auto i = 0; i < p; ++i) {
        auto ok = A[i] <= A[i + 1];
        if (!ok) {
            cout << "NO\n";
            return;
        }
    }
    for (auto i = p; i < N - 1; ++i) {
        auto ok = A[i] >= A[i + 1];
        if (!ok) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
