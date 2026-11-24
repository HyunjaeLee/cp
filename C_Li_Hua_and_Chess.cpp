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
    int N, M;
    cin >> N >> M;
    auto query = [&](int r, int c) {
        cout << "? " << r << " " << c << endl;
        int d;
        cin >> d;
        return d;
    };
    auto answer = [&](int r, int c) { cout << "! " << r << " " << c << endl; };
    auto a = query(1, 1);
    if (N < 1 + a) {
        auto r = 1 + query(1, 1 + a);
        auto c = 1 + a;
        answer(r, c);
    } else if (M < 1 + a) {
        auto r = 1 + a;
        auto c = 1 + query(1 + a, 1);
        answer(r, c);
    } else {
        auto b = query(1 + a, 1 + a);
        auto c = query(1 + a - b, 1 + a);
        if (c == 0) {
            answer(1 + a - b, 1 + a);
        } else {
            answer(1 + a, 1 + a - b);
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
