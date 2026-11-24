#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

i128 op(i128 a, i128 b) { return a + b; }

i128 e() { return 0; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    i64 N, M, K;
    cin >> N >> M >> K;
    vector<array<i64, 3>> P(M);
    for (auto &[B, A, v] : P) {
        cin >> v >> A >> B;
        --v;
    }
    ranges::sort(P);
    atcoder::segtree<i128, op, e> seg(vector<i128>(N, numeric_limits<i64>::max()));
    auto ans = numeric_limits<i64>::max();
    for (auto [B, A, v] : P) {
        auto i = int(v);
        auto x = seg.get(i);
        x = min<i128>(x, A);
        seg.set(i, x);
        auto val = B * K + seg.all_prod();
        ans = (i64)min<i128>(ans, val);
    }
    cout << ans << "\n";
}
