#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<pair<int, int>> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i].first;
        A[i].second = i;
    }
    vector<int> ans(N);
    ranges::sort(A);
    auto p = -1;
    auto score = 0LL;
    for (auto i = 0; i < N; ++i) {
        while (p < i) {
            score += A[++p].first;
        }
        while (p + 1 < N && A[p + 1].first <= score) {
            score += A[p + 1].first;
            p += 1;
        }
        ans[A[i].second] = p;
    }
    ranges::copy(ans, ostream_iterator<int>(cout, " "));
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
