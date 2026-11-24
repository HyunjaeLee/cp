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

i64 dp[20][10][2];

i64 f(int p, int d, int s) {
    if (p == 0)
        return 1;
    auto &ret = dp[p][d][s];
    if (~ret)
        return ret;
    ret = 0;
    for (auto i = 0; i < 10; ++i) {
        if ((i && i == d) || (i == 0 && i == d && s))
            continue;
        ret += f(p - 1, i, s || i);
    }
    return ret;
}

#define TC
void solve() {
    i64 K;
    cin >> K;
    vector<int> ans;
    auto rec = [&](this auto &&self, int pos, int s) -> void {
        if (pos == -1)
            return;
        for (auto i = 0; i < 10; ++i) {
            if (!ans.empty() && i == ans.back())
                continue;
            if (0 <= K - f(pos, i, s || i)) {
                K -= f(pos, i, s || i);
            } else {
                if (i || !ans.empty()) {
                    ans.push_back(i);
                }
                return self(pos - 1, s || i);
            }
        }
    };
    rec(18, 0);
    show(ans, "");
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(dp, -1, sizeof dp);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
