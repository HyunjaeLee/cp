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

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    read(A);
    read(B);
    ranges::reverse(B);
    vector<pair<int, int>> S(N), T(N);
    S[0] = {A[0], A[0]};
    T[0] = {B[0], B[0]};
    for (auto i = 1; i < N; ++i) {
        S[i] = {min(S[i - 1].first, A[i]), max(S[i - 1].second, A[i])};
        T[i] = {min(T[i - 1].first, B[i]), max(T[i - 1].second, B[i])};
    }
    i64 ans = 0;
    for (auto l = 1; l <= 2 * N; ++l) {
        auto it = ranges::partition_point(views::iota(l, 2 * N + 1), [&](int r) {
            auto L =
                *ranges::partition_point(views::iota(0, N), [&](int i) { return l <= S[i].first && S[i].second <= r; });
            auto R =
                *ranges::partition_point(views::iota(0, N), [&](int i) { return l <= T[i].first && T[i].second <= r; });
            return L + R <= N;
        });
        ans += 2 * N + 1 - *it;
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
