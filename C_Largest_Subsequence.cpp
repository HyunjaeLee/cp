#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

constexpr auto inf = numeric_limits<int>::max() / 2;
using S = pair<int, int>;

S op(S a, S b) { return min(a, b); }

S e() { return {inf, inf}; }

void solve() {
    int N;
    string st;
    cin >> N >> st;
    vector<pair<int, int>> A(N);
    for (auto i = 0; i < N; ++i) {
        A[i] = {-st[i], i};
    }
    atcoder::segtree<S, op, e> seg(A);
    vector<int> P;
    while (P.empty() || P.back() < N - 1) {
        auto l = P.empty() ? 0 : P.back() + 1;
        auto r = N;
        auto [_, pos] = seg.prod(l, r);
        P.push_back(pos);
    }
    auto ans = int(P.size());
    for (auto i = 0; i < int(P.size()); ++i) {
        if (st[P[i]] == st[P[0]]) {
            ans -= 1;
        }
    }
    for (auto i = 0; i < int(P.size()) / 2; ++i) {
        swap(st[P[i]], st[P[P.size() - 1 - i]]);
    }
    if (!ranges::is_sorted(st)) {
        ans = -1;
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
