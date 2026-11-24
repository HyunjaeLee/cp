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
using Z = atcoder::modint;

string turn;

#define TC
void solve() {
    int N;
    cin >> N;
    Z::set_mod(N);
    vector<string> A(N);
    read(A);
    auto w = 0;
    Z a = 0, b = 0;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            if (A[i][j] == '#') {
                w += 1;
                a += i;
                b += j;
            }
        }
    }
    if (turn == "first") {
        int r, c;
        cin >> r >> c;
        --r, --c;
        auto dr = Z(w) * r - a;
        auto dc = Z(w) * c - b;
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < N; ++j) {
                if (A[i][j] == '#') {
                    auto x = (i + dr).val();
                    auto y = (j + dc).val();
                    if (A[x][y] == '.') {
                        println("{} {} {} {}", i + 1, j + 1, x + 1, y + 1);
                        return;
                    }
                }
            }
        }
        println("{} {} {} {}", r + 1, c + 1, r + 1, c + 1);
    } else {
        auto r = (a / w).val();
        auto c = (b / w).val();
        println("{} {}", r + 1, c + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> turn;
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
