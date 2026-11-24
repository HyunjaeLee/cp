#include <atcoder/lazysegtree>
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

int op(int a, int b) { return max(a, b); }

int e() { return 0; }

int mapping(int f, int x) { return f + x; }

int composition(int f, int g) { return f + g; }

int id() { return 0; }

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    atcoder::lazy_segtree<int, op, e, int, mapping, composition, id> seg(N + 1);
    for (auto i = 0; i < N; ++i) {
        seg.set(A[i], 0);
        seg.apply(0, A[i], 1);
        cout << seg.all_prod() << " \n"[i == N - 1];
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
