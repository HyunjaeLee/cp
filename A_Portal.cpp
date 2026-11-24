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
    int N, M;
    cin >> N >> M;
    vector<vector<int>> A(N + 1, vector<int>(M + 1));
    for (auto i = 0; i < N; ++i) {
        string S;
        cin >> S;
        for (auto j = 0; j < M; ++j) {
            A[i + 1][j + 1] = S[j] - '0';
        }
    }
    for (auto i = 1; i <= N; ++i) {
        for (auto j = 1; j <= M; ++j) {
            A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
        }
    }
    auto cnt1 = [&](int r1, int r2, int c1, int c2) {
        assert(1 <= r1 && r1 <= N && 1 <= r2 && r2 <= N && 1 <= c1 && c1 <= M && 1 <= c2 && c2 <= M);
        return A[r2][c2] - A[r1 - 1][c2] - A[r2][c1 - 1] + A[r1 - 1][c1 - 1];
    };
    auto cnt0 = [&](int r1, int r2, int c1, int c2) {
        assert(1 <= r1 && r1 <= r2 && r2 <= N && 1 <= c1 && c1 <= c2 && c2 <= M);
        return (r2 - r1 + 1) * (c2 - c1 + 1) - cnt1(r1, r2, c1, c2);
    };
    auto ans = 16;
    for (auto l = 1; l <= M; ++l) {
        for (auto r = l + 3; r <= M; ++r) {
            for (auto t = 1; t <= N; ++t) {
                for (auto b = t + 4; b <= N; ++b) {
                    auto C = cnt1(t + 1, b - 1, l + 1, r - 1);
                    auto T = cnt0(t, t, l + 1, r - 1);
                    auto B = cnt0(b, b, l + 1, r - 1);
                    auto L = cnt0(t + 1, b - 1, l, l);
                    auto R = cnt0(t + 1, b - 1, r, r);
                    if (16 <= T + L + R + C) {
                        break;
                    }
                    ans = min(ans, C + T + B + L + R);
                }
            }
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
