#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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
    string S;
    cin >> N >> S;
    vector dp(2 * N + 1, vector<optional<pair<Z, Z>>>(4 * N + 1));
    auto f = [&](this auto &&self, int pos, int pref) -> pair<Z, Z> {
        if (pos == 2 * N)
            return pref == 0 ? pair{1, 0} : pair{0, 0};
        if (dp[pos][pref + 2 * N])
            return *dp[pos][pref + 2 * N];
        Z cnt = 0, sum = 0;
        if (S[pos] == '+' || S[pos] == '?') {
            auto [c, s] = self(pos + 1, pref + 1);
            auto k = 0 <= pref ? -1 : 1;
            cnt += c;
            sum += k * pos * c + s;
        }
        if (S[pos] == '-' || S[pos] == '?') {
            auto [c, s] = self(pos + 1, pref - 1);
            auto k = pref <= 0 ? -1 : 1;
            cnt += c;
            sum += k * pos * c + s;
        }
        dp[pos][pref + 2 * N] = {cnt, sum};
        return {cnt, sum};
    };
    cout << f(0, 0).second.val() << "\n";
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
