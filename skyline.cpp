#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

struct S {
    int min, max;
};

S op(S a, S b) { return {min(a.min, b.min), max(a.max, b.max)}; }

constexpr auto inf = numeric_limits<int>::max() / 2;

S e() { return {inf, -inf}; }

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    atcoder::segtree<S, op, e> seg(N);
    for (auto i = 0; i < N; ++i) {
        seg.set(i, {A[i], A[i]});
    }
    auto ans = 0;
    for (auto i = 0; i < N; ++i) {
        if (seg.prod(0, i).max <= A[i] && A[i] <= seg.prod(i + 1, N).min) {
            ans++;
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
