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

u64 H(const string &s) {
    u64 x = 0;
    for (auto i = 0; i < ssize(s); ++i) {
        x |= u64(s[i]) << (8 * i);
    }
    static const auto seed = chrono::steady_clock::now().time_since_epoch().count();
    return x ^ seed;
}

void solve() {
    int N, M;
    cin >> N >> M;
    vector<string> A(N);
    read(A);
    vector<vector<i64>> F(3, vector<i64>(N));
    {
        unordered_map<u64, i64> mp;
        for (auto i = 0; i < N; ++i) {
            F[0][i] = mp[H(A[i])];
            mp[H(A[i])]++;
        }
    }
    {
        unordered_map<u64, i64> mp;
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < M; ++j) {
                auto s = A[i];
                s[j] = '*';
                F[1][i] += mp[H(s)];
            }
            F[1][i] -= F[0][i] * M;
            for (auto j = 0; j < M; ++j) {
                auto s = A[i];
                s[j] = '*';
                mp[H(s)]++;
            }
        }
    }
    {
        unordered_map<u64, i64> mp;
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < M; ++j) {
                for (auto k = j + 1; k < M; ++k) {
                    auto s = A[i];
                    s[j] = s[k] = '*';
                    F[2][i] += mp[H(s)];
                }
            }
            F[2][i] -= F[0][i] * i64(M) * (M - 1) / 2;
            F[2][i] -= F[1][i] * (M - 1);
            for (auto j = 0; j < M; ++j) {
                for (auto k = j + 1; k < M; ++k) {
                    auto s = A[i];
                    s[j] = s[k] = '*';
                    mp[H(s)]++;
                }
            }
        }
    }
    i64 ans = 0;
    for (auto i = 0; i < 3; ++i) {
        ans += ranges::fold_left(F[i], 0LL, plus());
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
