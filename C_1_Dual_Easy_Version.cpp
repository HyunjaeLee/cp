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
    vector<pair<int, int>> ans;
    if (ranges::max(A) <= 0) {
        for (auto i = N - 1; 0 < i; --i) {
            ans.emplace_back(i - 1, i);
        }
    } else {
        auto it = ranges::max_element(A);
        auto p = int(it - A.begin());
        for (auto i = 0; i < 5; ++i) {
            ans.emplace_back(p, p);
        }
        ans.emplace_back(N - 1, p);
        ans.emplace_back(N - 1, N - 1);
        ans.emplace_back(N - 1, N - 1);
        ans.emplace_back(N - 1, N - 1);
        ans.emplace_back(N - 1, N - 1);
        for (auto i = 1; i < N; ++i) {
            ans.emplace_back(N - 1, N - 1);
            ans.emplace_back(i, N - 1);
        }
    }
    assert(ans.size() <= 50);
    cout << ans.size() << "\n";
    for (auto [i, j] : ans) {
        cout << i + 1 << " " << j + 1 << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
