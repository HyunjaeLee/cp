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
    vector<i64> A(N);
    read(A);
    if (N == 1 && A[0] == 1) {
        cout << "YES\n";
        return;
    }
    auto S = ranges::fold_left(A, 0LL, plus());
    auto T = 2LL;
    vector<i64> F{1, 1};
    while (T < S) {
        auto k = int(F.size());
        F.push_back(F[k - 2] + F[k - 1]);
        T += F.back();
    }
    if (S < T) {
        cout << "NO\n";
        return;
    }
    auto pc = -1;
    for (auto f : F | views::reverse) {
        auto c = -1;
        for (auto i = 0; i < N; ++i) {
            if (i != pc && f <= A[i] && (c == -1 || A[c] < A[i])) {
                c = i;
            }
        }
        if (c == -1) {
            cout << "NO\n";
            return;
        }
        A[c] -= f;
        pc = c;
    }
    cout << "YES\n";
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
