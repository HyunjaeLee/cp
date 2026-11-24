#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    copy_n(istream_iterator<int>(cin), N, begin(A));
    copy_n(istream_iterator<int>(cin), N, begin(B));
    vector<pair<int, int>> C(N);
    for (auto i = 0; i < N; ++i) {
        C[i] = pair(A[i], B[i]);
    }
    ranges::sort(C, {}, [](auto p) { return max(p.first, p.second); });
    for (auto i = 0; i < N; ++i) {
        A[i] = C[i].first;
    }
    for (auto i = 0; i < N; ++i) {
        B[i] = C[i].second;
    }
    ranges::copy(A, ostream_iterator<int>(cout, " "));
    cout << "\n";
    ranges::copy(B, ostream_iterator<int>(cout, " "));
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
