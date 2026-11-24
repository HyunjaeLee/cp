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

#include <atcoder/segtree>

constexpr auto inf = numeric_limits<int>::max() / 2;
int op(int a, int b) { return max(a, b); }
int e() { return -inf; }

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    read<1>(A);
    atcoder::segtree<int, op, e> f(N);
    {
        atcoder::segtree<int, op, e> seg(N);
        for (auto i = 0; i < N; ++i) {
            f.set(i, seg.prod(A[i] + 1, N));
            seg.set(A[i], i);
        }
    }
    for (auto i = 0; i <= N - 2 * K; ++i) {
        auto l = i, r = i + K;
        auto is_sorted = f.prod(l, r) < l;
        if (is_sorted) {
            show<1>(A);
            return;
        }
    }
    atcoder::segtree<int, op, e> max_seg(A);
    atcoder::segtree<int, [](int a, int b) { return min(a, b); }, [] { return inf; }> min_seg(A);
    auto p = -1;
    for (auto i = max(0, N - 2 * K + 1); i <= N - K; ++i) {
        auto l = i, r = i + K;
        auto is_sorted = f.prod(l, N - K) < l;
        auto x = max_seg.prod(l, N - K);
        auto y = min_seg.prod(N - K, r);
        if (is_sorted && x < y) {
            p = i;
            break;
        }
    }
    auto l = N - K, r = p + K;
    if (l < r) {
        ranges::sort(begin(A) + l, begin(A) + r);
    }
    show<1>(A);
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
