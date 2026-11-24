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
    vector<int> I(N);
    iota(begin(I), end(I), 0);
    ranges::sort(I, {}, [&](int i) { return A[i]; });
    vector<pair<int, int>> ans;
    while (0 < A[I[0]] && 0 < A[I[1]]) {
        auto g1 = gcd(A[I[0]] - gcd(A[I[0]], A[I[1]]), A[I[1]]);
        auto g2 = gcd(A[I[0]], A[I[1]] - gcd(A[I[0]], A[I[1]]));
        if (g1 > g2) {
            A[I[0]] -= __gcd(A[I[0]], A[I[1]]);
            ans.emplace_back(I[0], I[1]);
        } else {
            A[I[1]] -= __gcd(A[I[0]], A[I[1]]);
            ans.emplace_back(I[1], I[0]);
        }
    }
    ranges::sort(I, {}, [&](int i) { return A[i]; });
    assert(A[I[0]] == 0);
    for (auto i = 0; i < N; ++i) {
        if (A[I[i]] == 0)
            continue;
        A[I[i]] -= __gcd(A[I[i]], A[I[0]]);
        assert(A[I[i]] == 0);
        ans.emplace_back(I[i], I[0]);
    }
    assert(int(ans.size()) <= N + 40);
    cout << ans.size() << "\n";
    for (auto [a, b] : ans) {
        cout << a + 1 << " " << b + 1 << "\n";
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
