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
    int N;
    cin >> N;
    vector<int> A(N);
    read<1>(A);
    string s;
    cin >> s;
    auto a = 0;
    auto b = N - 1;
    auto c = int(ranges::max_element(A) - A.begin());
    auto d = int(ranges::min_element(A) - A.begin());
    if (s[a] == '1' || s[b] == '1' || s[c] == '1' || s[d] == '1') {
        cout << "-1\n";
        return;
    }
    vector<pair<int, int>> ans{{a, c}, {a, d}, {c, d}, {c, b}, {d, b}};
    cout << 5 << "\n";
    for (auto [l, r] : ans) {
        if (l > r)
            swap(l, r);
        cout << l + 1 << " " << r + 1 << "\n";
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
