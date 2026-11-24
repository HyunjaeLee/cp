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

// p[i] = i를 중심으로 하는 최장 팰린드롬의 길이 (0 <= i < 2 * n - 1)
vector<int> manacher(string s) { // O(n)
    auto n = ssize(s);
    vector<int> p(2 * n - 1); // 0 < n
    for (auto i = 0, l = 0, r = -1; i < 2 * n - 1; ++i) {
        auto k = i < r ? min(p[l + r - i], r - i) : 1 - (i & 1);
        auto a = (i - k - 1) / 2, b = (i + k + 1) / 2;
        while (0 <= a && b < n && s[a] == s[b])
            k += 2, --a, ++b;
        p[i] = k;
        if (i + k > r) l = i - k, r = i + k;
    }
    return p;
}

void solve() {
    string S;
    cin >> S;
    show(manacher(S));
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
