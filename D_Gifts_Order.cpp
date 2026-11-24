#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

constexpr auto inf = numeric_limits<i64>::max() / 4;

struct S {
    i64 min, max, min_diff, max_diff;
};

S op(S a, S b) {
    S r;
    r.min = min(a.min, b.min);
    r.max = max(a.max, b.max);
    r.min_diff = min({a.min_diff, b.min_diff, b.min - a.max});
    r.max_diff = max({a.max_diff, b.max_diff, b.max - a.min});
    return r;
}

S e() { return {inf, -inf, 0, 0}; }

#include <atcoder/segtree>

#define TC
void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<i64> A(N);
    read(A);
    vector<S> B(N), C(N);
    for (auto i = 0; i < N; ++i) {
        B[i] = {A[i] - i, A[i] - i, 0, 0};
        C[i] = {A[i] + i, A[i] + i, 0, 0};
    }
    atcoder::segtree<S, op, e> SB(B), SC(C);
    auto query = [&] { return max(SB.all_prod().max_diff, -SC.all_prod().min_diff); };
    cout << query() << "\n";
    while (Q--) {
        int p, x;
        cin >> p >> x;
        --p;
        SB.set(p, {x - p, x - p, 0, 0});
        SC.set(p, {x + p, x + p, 0, 0});
        cout << query() << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
