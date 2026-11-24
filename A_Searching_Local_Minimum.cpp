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

void solve() {
    int N;
    cin >> N;
    auto cnt = 0;
    auto Query = [&](int i) {
        assert(++cnt <= 100);
        cout << "? " << i + 1 << endl;
        int x;
        cin >> x;
        return x;
    };
    vector<int> A(N, -1);
    auto F = [&](int i) {
        constexpr auto inf = numeric_limits<int>::max() / 2;
        if (i < 0 || N <= i)
            return inf;
        if (A[i] != -1)
            return A[i];
        return A[i] = Query(i);
    };
    auto pred = [&](int i) { return F(i) > F(i + 1); };
    auto it = ranges::partition_point(views::iota(0, N), pred);
    auto ans = *it + 1;
    cout << "! " << ans << endl;
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
