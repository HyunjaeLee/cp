#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

#include <atcoder/modint>
using Z = atcoder::modint1000000007;

#define TC
void solve() {
    i64 N;
    cin >> N;
    Z dp[61][2][2][2]{};
    bool vis[61][2][2][2]{};
    auto F = [&](this auto &&self, int pos, int fit_lo, int fit_hi, int start) -> Z {
        if (pos <= -1)
            return (pos == -1 ? 1 : 0);
        auto &ret = dp[pos][fit_lo][fit_hi][start];
        if (vis[pos][fit_lo][fit_hi][start])
            return ret;
        vis[pos][fit_lo][fit_hi][start] = true;
        if (1 <= pos && (!fit_hi || 0x3 <= ((N >> (pos - 1)) & 0x3)) &&
            (!fit_lo || ((1LL >> (pos - 1)) & 0x3) <= 0x1)) {
            ret += self(pos - 2, fit_lo && ((1LL >> (pos - 1)) & 0x3) == 0x1, fit_hi && 0x3 == ((N >> (pos - 1)) & 0x3),
                        1);
        }
        if (start && 1 <= pos && (!fit_hi || 0x1 <= ((N >> (pos - 1)) & 0x3)) &&
            (!fit_lo || ((1LL >> (pos - 1)) & 0x3) <= 0x3)) {
            ret += self(pos - 2, fit_lo && ((1LL >> (pos - 1)) & 0x3) == 0x3, fit_hi && 0x1 == ((N >> (pos - 1)) & 0x3),
                        start);
        }
        if ((!fit_hi || 0x0 <= ((N >> (pos)) & 0x1)) && (!fit_lo || ((1LL >> (pos)) & 0x1) <= 0x0)) {
            ret += self(pos - 1, fit_lo && ((1LL >> (pos)) & 0x1) == 0x0, fit_hi && 0x0 == ((N >> (pos)) & 0x1), start);
        }
        return ret;
    };
    cout << F(60, 1, 1, 0).val() << "\n";
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
