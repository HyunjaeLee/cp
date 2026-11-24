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

#include <atcoder/modint>
using Z = atcoder::modint1000000007;
using mint = atcoder::modint;

#define TC
void solve() {
    int N, C;
    cin >> N >> C;
    string S;
    cin >> S;
    S.insert(S.begin(), '*');
    if (S[1] == '0' || S[N] == '0') {
        cout << "-1\n";
        return;
    }
    S[1] = S[N] = '1';
    auto two = 0;
    for (auto x = C; x % 2 == 0; x /= 2) {
        two++;
    }
    Z prod = 1;
    mint::set_mod(C);
    mint pc = 1;
    for (auto i = 1; i < N; ++i) {
        auto c = 0;
        if (S[i] == '?') {
            c = min(2, i - 1);
        } if (S[i] == '1') {
            c = 2;
        } else {
            c = i - 1;
        }
        prod *= c;
        pc *= c;
        while (c % 2 == 0) {
            two--;
            c /= 2;
        }
    }
    if (pc != 0) {
        cout << prod.val() << "\n";
        return;
    }
    for (auto i = 3; i < N && two <= 0; ++i) {
        if (S[i] != '?') continue;
        if ((i - 1) % 2 == 0) continue;
        prod *= Z(i - 1) / 2;
        two++;
    }
    if (0 < two) {
        cout << prod.val() << "\n";
        return;
    }
    cout << "-1\n";
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
