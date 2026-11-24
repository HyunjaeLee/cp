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
    read(A);
    auto a = 0, b = 0;
    for (auto i = 0; i < N; ++i) {
        if (A[i] == 1) {
            ++a;
        } else {
            ++b;
        }
    }
    vector<bool> f(N);
    if (a < b) {
        for (auto i = 1; i < N && a < b; ++i) {
            if (A[i] == -1) {
                --b;
                ++a;
                f[i - 1] = true;
                ++i;
            }
        }
    } else {
        for (auto i = 1; i < N && a > b; ++i) {
            if (A[i] == 1) {
                --a;
                ++b;
                f[i - 1] = true;
                ++i;
            }
        }
    }
    if (a != b) {
        cout << "-1\n";
        return;
    }
    vector<pair<int, int>> ans;
    for (auto i = 0; i < N; ++i) {
        if (f[i]) {
            ans.emplace_back(i + 1, i + 2);
            ++i;
        } else {
            ans.emplace_back(i + 1, i + 1);
        }
    }
    cout << size(ans) << "\n";
    for (auto [l, r] : ans) {
        cout << l << " " << r << "\n";
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
