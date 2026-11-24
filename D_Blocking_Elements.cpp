#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

constexpr auto inf = numeric_limits<i64>::max() / 4;

i64 op(i64 a, i64 b) { return min(a, b); }
i64 e() { return inf; }

void solve() {
    int N;
    cin >> N;
    vector<i64> A(N);
    copy_n(istream_iterator<i64>(cin), N, begin(A));
    vector<i64> pref(N + 1);
    for (auto i = 0; i < N; ++i) {
        pref[i + 1] = A[i] + pref[i];
    }
    auto Sum = [&](int l, int r) -> i64 { return pref[r] - pref[l]; };
    auto pred = [&](i64 X) {
        atcoder::segtree<i64, op, e> dp(N + 1);
        dp.set(N, 0);
        auto R = N;
        for (auto i = N - 1; 0 <= i; --i) {
            dp.set(i + 1, dp.get(i + 1) + A[i]);
            if (Sum(i, N) <= X) {
                dp.set(i, 0);
                continue;
            }
            while (X < Sum(i, R - 1)) {
                --R;
            }
            dp.set(i, dp.prod(i + 1, R + 1));
        }
        return !(dp.get(0) <= X);
    };
    auto ans = *ranges::partition_point(views::iota(0LL, inf), pred);
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
