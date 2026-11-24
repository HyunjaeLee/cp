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
    i64 N;
    cin >> N;
    vector<i64> A_(N);
    read(A_);
    auto f = [&](i64 x) {
        i64 cnt = 0;
        while (0 < x) {
            if (x & 1) {
                x -= 1;
            } else {
                x /= 2;
            }
            cnt++;
        }
        return cnt;
    };
    auto ans = 0LL;
    for (auto i = 0; i < N; ++i) {
        ans += f(A_[i]);
    }
    auto find_best = [&](i64 x, i64 w) {
        auto profit = 0LL;
        auto xx = x;
        for (auto d = 0; d * w < 45; d++) {
            auto pp = f(x) - f(x + d) - d * w;
            if (profit < pp) {
                profit = pp;
                xx = x + d;
            }
        }
        return xx;
    };
    for (auto lg = 0; lg < 20; ++lg) {
        auto A = A_;
        i64 val = 0;
        for (auto i = 0; i < N; ++i) {
            if (A[i] & ((1LL << lg) - 1)) {
                auto s = ((~A[i]) & ((1LL << lg) - 1)) + 1;
                val += s;
                A[i] += s;
            }
            auto best = find_best(A[i] >> lg, 1 << lg) << lg;
            val += best - A[i];
            A[i] = best;
            assert((A[i] & ((1LL << lg) - 1)) == 0);
        }
        while (ranges::fold_left(A, 0LL, plus())) {
            auto ok = true;
            for (auto i = 0; i < N; ++i) {
                if (A[i] & 1) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                break;
            }
            for (auto i = 0; i < N; ++i) {
                A[i] /= 2;
            }
            val += 1;
        }
        for (auto i = 0; i < N; ++i) {
            val += f(A[i]);
        }
        ans = min(ans, val);
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
