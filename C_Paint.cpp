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
    auto Encode = [&] {
        int N;
        cin >> N;
        vector<int> A(N);
        read(A);
        vector<int> B;
        for (auto i = 0; i < N; ++i) {
            if (B.empty() || B.back() != A[i]) {
                B.push_back(A[i]);
            }
        }
        auto M = int(B.size());
        return pair(M, B);
    };
    auto [N, A] = Encode();
    vector<vector<int>> G(ranges::max(A) + 1);
    for (auto i = 0; i < N; ++i) {
        G[A[i]].push_back(i);
    }
    vector<vector<int>> dp(N, vector<int>(N, -1));
    cout << [&](this auto &&self, int l, int r) -> int {
        assert(0 <= l && l <= r && r < N);
        if (l == r)
            return 0;
        auto &ret = dp[l][r];
        if (~ret)
            return ret;
        ret = self(l + 1, r) + 1;
        for (auto i : G[A[l]]) {
            if (l < i && i <= r) {
                ret = min(ret, self(l + 1, i - 1) + 1 + self(i, r));
            }
        }
        return ret;
    }(0, N - 1) << "\n";
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
