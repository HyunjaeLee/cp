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
    i64 N, M;
    cin >> N >> M;
    vector<i64> A(N);
    read(A);
    vector<i64> F(M + 10);
    for (i64 i = 0; i < N; ++i) {
        F[A[i]]++;
    }
    for (auto i = 0; i < M + 9; ++i) {
        F[i + 1] += F[i];
    }
    auto Prod = [&](auto l, auto r) {
        auto R = F[r - 1];
        auto L = l ? F[l - 1] : 0;
        return R - L;
    };
    auto Get = [&](auto i) {
        auto R = F[i];
        auto L = i ? F[i - 1] : 0;
        return R - L;
    };
    vector<i64> ANS;
    for (i64 k = 1; k <= min<i64>(20, M); ++k) {
        i64 ans = 0;
        i64 alpha = 1 << (k - 1);
        for (i64 x = 1; x <= M; ++x) {
            i64 sum = 0;
            for (i64 d = 0; d < 2 * alpha; ++d) {
                i64 l = d * x;
                i64 r = (d + 1) * x;
                if (M < l)
                    break;
                sum += d * Prod((int)l, (int)min(r, M + 1));
            }
            sum += Get((int)min(2 * alpha * x, M + 1)) * 2 * alpha;
            sum += Prod((int)min(2 * alpha * x + 1, M + 1), int(M + 1)) * (2 * alpha - 1);
            ans = max(ans, sum);
        }
        ANS.push_back(ans);
    }
    while (ssize(ANS) < M) {
        ANS.push_back(ANS.back());
    }
    show(ANS);
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
