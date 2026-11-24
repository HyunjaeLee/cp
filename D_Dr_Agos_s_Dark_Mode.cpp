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
    if (N <= 4) {
        vector<string> ans{"", "1", "11", "101", "0101"};
        cout << ans[N] << "\n";
        return;
    }
    i64 w = numeric_limits<i64>::max();
    vector<i64> v;
    for (i64 i = 1; i <= N - 2; i += 2) {
        i64 l = floor_div(N - (i + 2), 2LL);
        i64 r = ceil_div(N - (i + 2), 2LL);
        i64 x = l * (l + 1) / 2 + i * (i + 1) / 2 + r * (r + 1) / 2;
        if (x < w) {
            w = x;
            v = {l, i, r};
        }
    }
    for (i64 i = 1; 2 * i + 3 <= N; i += 2) {
        i64 l = floor_div(N - (2 * i + 3), 2LL);
        i64 r = ceil_div(N - (2 * i + 3), 2LL);
        i64 x = l * (l + 1) / 2 + i * (i + 1) + r * (r + 1) / 2 + (l + 1) * (r + 1);
        if (x < w) {
            w = x;
            v = {l, i, i, r};
        }
    }
    for (i64 i = 0; 2 * i + 3 <= N; i += 2) {
        i64 a = i, b = floor_div(N - (2 * i + 3), 2LL), c = i, d = ceil_div(N - (2 * i + 3), 2LL);
        if (b == 0 && d == 0)
            continue;
        if ((b & 1) == 0) {
            b++;
            d--;
        }
        i64 x = a * (a + 1) / 2 + b * (b + 1) / 2 + c * (c + 1) / 2 + d * (d + 1) / 2 + (b + 1) * (d + 1);
        if (x < w) {
            w = x;
            v = {a, b, c, d};
        }
    }
    cout << w << " ";
    string ans;
    for (auto i = 0; i < int(v.size()); ++i) {
        if (i) {
            ans += "1";
        }
        ans += string(v[i], '0');
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
