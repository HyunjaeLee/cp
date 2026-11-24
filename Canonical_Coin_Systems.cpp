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

// O(n^3), requires distinct positive integers including 1
// David Pearson, "A Polynomial-time Algorithm for the Change-Making Problem"
template <typename T> bool is_canonical(std::vector<T> coins) {
    auto n = int(coins.size());
    std::sort(coins.rbegin(), coins.rend());
    auto greedy = [&](T x) {
        std::vector<T> v(n);
        for (auto i = 0; i < n; ++i) {
            v[i] = x / coins[i];
            x %= coins[i];
        }
        return v;
    };
    auto count = [](const std::vector<T> &v) { return std::accumulate(v.begin(), v.end(), T(0)); };
    for (auto i = 1; i < n; ++i) {
        auto v = greedy(coins[i - 1] - 1);
        for (auto j = i; j < n; ++j) {
            std::vector<T> mw(n);
            std::copy(v.begin(), v.begin() + j, mw.begin());
            mw[j] = v[j] + 1;
            auto w = std::inner_product(coins.begin(), coins.end(), mw.begin(), T(0));
            auto gw = greedy(w);
            if (count(mw) < count(gw)) {
                return false;
            }
        }
    }
    return true;
}

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    cout << (is_canonical(A) ? "canonical\n" : "non-canonical\n");
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
