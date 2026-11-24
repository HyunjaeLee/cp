#include <atcoder/segtree>
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

i64 op(i64 a, i64 b) { return max(a, b); }
i64 e() { return numeric_limits<i64>::min(); }

#define TC
void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    read(A);
    vector<int> D; // divisors without N
    for (auto i = 1; i < N; ++i) {
        if (N % i == 0) {
            D.push_back(i);
        }
    }
    atcoder::segtree<i64, op, e> seg(ranges::fold_left(D, 0, plus()));
    for (auto t = 0; auto d : D) {
        for (auto i = 0; i < d; ++i) {
            i64 sum = 0;
            for (auto j = i; j < N; j += d) {
                sum += A[j];
            }
            seg.set(t++, d * sum);
        }
    }
    cout << seg.all_prod() << "\n";
    while (Q--) {
        int p, x;
        cin >> p >> x;
        --p;
        for (auto t = 0; auto d : D) {
            auto i = p % d;
            seg.set(t + i, seg.get(t + i) + d * i64(x - A[p]));
            t += d;
        }
        A[p] = x;
        cout << seg.all_prod() << "\n";
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
