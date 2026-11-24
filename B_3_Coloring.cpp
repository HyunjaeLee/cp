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

void solve() {
    int N;
    cin >> N;
    vector<pair<int, int>> P, Q;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            if ((i + j) & 1) {
                P.emplace_back(i, j);
            } else {
                Q.emplace_back(i, j);
            }
        }
    }
    for (auto i = 0; i < N * N; ++i) {
        int a;
        cin >> a;
        if (a == 1) {
            if (P.empty()) {
                auto [x, y] = Q.back();
                Q.pop_back();
                cout << "3 " << x + 1 << " " << y + 1 << endl;
            } else {
                auto [x, y] = P.back();
                P.pop_back();
                cout << "2 " << x + 1 << " " << y + 1 << endl;
            }
        } else {
            if (Q.empty()) {
                auto [x, y] = P.back();
                P.pop_back();
                cout << (a == 2 ? 3 : 2) << " " << x + 1 << " " << y + 1 << endl;
            } else {
                auto [x, y] = Q.back();
                Q.pop_back();
                cout << "1 " << x + 1 << " " << y + 1 << endl;
            }
        }
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
