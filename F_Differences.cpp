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
    int N, M, K;
    cin >> N >> M >> K;
    vector<string> S(N);
    read(S);
    vector<vector<int>> A(N, vector<int>(M));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            A[i][j] = S[i][j] - 'A';
        }
    }
    constexpr i64 B = 654321, P = (1LL << 61) - 1;
    vector<i64> X(N);
    X[0] = 1;
    for (auto i = 1; i < N; ++i) {
        X[i] = i64(i128(X[i - 1]) * B % P);
    }
    i64 U = 0;
    for (auto i = 0; i < N; ++i) {
        U = (U + X[i]) % P;
    }
    vector<vector<i64>> F(M, vector<i64>(4));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            F[j][A[i][j]] = (F[j][A[i][j]] + X[i]) % P;
        }
    }
    for (auto i = 0; i < N; ++i) {
        i64 sum = 0;
        for (auto j = 0; j < M; ++j) {
            for (auto k = 0; k < 4; ++k) {
                if (A[i][j] != k) {
                    sum = (sum + F[j][k]) % P;
                }
            }
        }
        if (sum == i64(i128(P + U - X[i]) * K % P)) {
            cout << i + 1 << "\n";
            return;
        }
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
