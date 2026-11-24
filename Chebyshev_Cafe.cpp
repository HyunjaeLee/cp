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
    int N, M;
    cin >> N >> M;
    vector<i64> A(N), B(N);
    read(A);
    read(B);
    vector<vector<i64>> U1(2 * N, vector<i64>(2 * N));
    vector<vector<i64>> U2(2 * N, vector<i64>(2 * N));
    vector<vector<i64>> U3(2 * N, vector<i64>(2 * N));
    vector<vector<i64>> U4(2 * N, vector<i64>(2 * N));
    vector<vector<i64>> V(2 * N, vector<i64>(2 * N));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            auto r = i + j;
            auto c = N - 1 + i - j;
            auto w = (A[i] * B[j]) % M;
            U1[r + 1][c + 1] = (-r + c) * w;
            U2[r + 1][c + 1] = (-r - c) * w;
            U3[r + 1][c + 1] = (r - c) * w;
            U4[r + 1][c + 1] = (r + c) * w;
            V[r + 1][c + 1] = w;
        }
    }
    auto build = [&](vector<vector<i64>> &a) {
        for (auto i = 1; i < 2 * N; ++i) {
            for (auto j = 1; j < 2 * N; ++j) {
                a[i][j] = a[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
            }
        }
    };
    build(U1);
    build(U2);
    build(U3);
    build(U4);
    build(V);
    auto prod = [&](const vector<vector<i64>> &a, int r1, int r2, int c1, int c2) {
        return a[r2][c2] - a[r1][c2] - a[r2][c1] + a[r1][c1];
    };
    i64 ans = 0;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            auto r = i + j;
            auto c = N - 1 + i - j;
            i64 f = 0;
            f += prod(U1, 0, r + 1, c + 1, 2 * N - 1) + prod(V, 0, r + 1, c + 1, 2 * N - 1) * (r - c);
            f += prod(U2, 0, r, 0, c + 1) + prod(V, 0, r, 0, c + 1) * (r + c);
            f += prod(U3, r, 2 * N - 1, 0, c) + prod(V, r, 2 * N - 1, 0, c) * (-r + c);
            f += prod(U4, r + 1, 2 * N - 1, c, 2 * N - 1) + prod(V, r + 1, 2 * N - 1, c, 2 * N - 1) * (-r - c);
            f /= 2;
            ans ^= f + i * N + j;
        }
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
