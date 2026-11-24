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
    string A, B, C;
    cin >> N >> A >> B >> C;
    vector<array<int, 3>> P(N);
    auto F = [&](string S, int id) {
        auto cnt = 0;
        for (auto i = 0; i < 2 * N; ++i) {
            if (S[i] == '1') {
                P[cnt][id] = i;
                cnt += 1;
            }
        }
    };
    F(A, 0);
    F(B, 1);
    F(C, 2);
    i64 ans = 0;
    string X(2 * N, '0');
    for (auto i = 0; i < N; ++i) {
        ranges::sort(P[i]);
        ans += P[i][2] - P[i][0];
        auto pos = P[i][1];
        assert(X[pos] == '0');
        X[pos] = '1';
    }
    cout << ans << "\n" << X << "\n";
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
