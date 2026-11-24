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

int op(int a, int b) { return max(a, b); }
int e() { return 0; }

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    auto ans = numeric_limits<int>::max();
    for (auto t = 0; t < 2; ++t) {
        auto a = 0;
        for (auto i = 0; i < N - 1; ++i) {
            if (abs(A[a + 1] - A[a]) < abs(A[i + 1] - A[i])) {
                a = i;
            }
        }
        atcoder::segtree<int, op, e> seg(N - 1);
        for (auto i = 0; i < N - 1; ++i) {
            seg.set(i, abs(A[i + 1] - A[i]));
        }
        ans = min(ans, abs(A[a + 1] - A[a]));
        auto b = a + 1, c = a + 1;
        for (; c < N; ++c) {
            if (c == N - 1) {
                auto g = max({seg.prod(0, a), 2 * seg.prod(b, c), abs(A[a] - 2 * A[c])});
                ans = min(ans, g);
                break;
            }
            auto d = c + 1;
            auto g = max(
                {seg.prod(0, a), 2 * seg.prod(b, c), seg.prod(d, N - 1), abs(A[a] - 2 * A[c]), abs(A[d] - 2 * A[b])});
            ans = min(ans, g);
        }
        ranges::reverse(A);
    }
    cout << ans << "\n";
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
