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

int op(int a, int b) { return a + b; }
int e() { return 0; }

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    read(A);
    static constexpr auto inf = numeric_limits<int>::max() / 2;
    atcoder::segtree<int, op, e> seg(N);
    atcoder::segtree<int, [](int a, int b) { return min(a, b); }, [] { return inf; }> seg2(A);
    atcoder::segtree<int, [](int a, int b) { return max(a, b); }, [] { return -inf; }> seg3(A);
    for (auto i = 0; i < N - 1; ++i) {
        if (A[i] <= A[i + 1]) {
            seg.set(i, 1);
        }
    }
    A.push_back(inf);
    seg.set(N - 1, 1);
    for (auto i = 0; i + K + 1 <= N; ++i) {
        if (seg.prod(0, i) == i && seg.prod(i + K + 1, N) == N - (i + K + 1) && A[i] <= seg2.prod(i, i + K + 1) &&
            seg3.prod(i, i + K + 1) <= A[i + K + 1]) {
            cout << "Yes\n";
            return;
        }
    }
    cout << "No\n";
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
