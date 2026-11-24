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
    vector<array<int, 3>> v;
    for (auto i = 0; i < N; ++i) {
        if (!v.empty() && v.back()[0] == A[i]) {
            v.back()[2]++;
        } else {
            v.push_back({A[i], i, i});
        }
    }
    vector<int> ans;
    auto f = [&](auto id) {
        auto [x, l, r] = v[id];
        if (x == 0) { // <-
            for (auto i = r; l <= i; --i) {
                ans.push_back(i);
            }
        } else { // ->
            for (auto i = l; i <= r; ++i) {
                ans.push_back(i);
            }
        }
    };
    if (v.front()[0] == 0 && v.back()[0] == 1) {
        cout << "-1\n";
        return;
    }
    if (v.size() == 1) {
        f(0);
    } else {
        if (!(v[0][0] == 1 && v[1][0] == 0))
            ranges::reverse(v);
        const auto k = int(v.size());
        for (auto i = 0; i + 1 < k; i += 2) {
            f(i + 1);
            f(i);
        }
        if (k & 1)
            f(k - 1);
    }
    for (auto i = 0; i < N; ++i) {
        cout << ans[i] + 1 << " \n"[i == N - 1];
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
