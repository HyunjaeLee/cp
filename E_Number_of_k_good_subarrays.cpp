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

struct S {
    __int128 len, sum, l, r;
};

optional<S> dp[61][61];

S op(S a, S b) {
    S c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum + a.r * b.l;
    c.l = a.len == a.l ? a.len + b.l : a.l;
    c.r = b.len == b.r ? a.r + b.len : b.r;
    return c;
}

S f(int m, int k) {
    if (k < 0)
        return {1LL << m, 0, 0, 0};
    if (m == 0)
        return {1, 1, 1, 1};
    if (dp[m][k])
        return *dp[m][k];
    return *(dp[m][k] = op(f(m - 1, k), f(m - 1, k - 1)));
}

#define TC
void solve() {
    i64 N;
    int K;
    cin >> N >> K;
    vector<int> M;
    for (auto i = 60; 0 <= i; --i) {
        if ((N >> i) & 1)
            M.push_back(i);
    }
    S prod = f(M[0], K);
    for (auto i = 1; i < ssize(M); ++i) {
        prod = op(prod, f(M[i], K - i));
    }
    auto ans = prod.sum;
    cout << int(ans % 1000000007) << "\n";
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
