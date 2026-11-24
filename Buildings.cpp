#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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

#ifndef COMBINATORICS_HPP
#define COMBINATORICS_HPP

#include <algorithm>
#include <bit>
#include <cassert>
#include <vector>

template <typename Z> struct Combinatorics {
    static void grow(int n) {
        auto m = int(f_.size());
        if (n < m) {
            return;
        }
        n = std::min<int>(std::bit_ceil(unsigned(n + 1)), Z::mod());
        f_.resize(n);
        finv_.resize(n);
        for (auto i = m; i < n; ++i) {
            f_[i] = f_[i - 1] * Z(i);
        }
        finv_[n - 1] = f_[n - 1].inv();
        for (auto i = n - 1; m < i; --i) {
            finv_[i - 1] = finv_[i] * Z(i);
        }
    }
    static Z f(int n) { // O(1)
        assert(0 <= n);
        grow(n);
        return f_[n];
    }
    static Z finv(int n) { // O(1)
        assert(0 <= n);
        grow(n);
        return finv_[n];
    }
    static Z binom(int n, int k) { // O(1)
        if (0 <= k && k <= n) {
            return f(n) * finv(k) * finv(n - k);
        } else {
            return Z(0);
        }
    }
    static Z binom2(long long n, long long k) { // O(min(k, n - k))
        if (k < 0 || n < k) {
            return Z(0);
        }
        if (n - k < k) {
            return binom2(n, n - k);
        }
        auto ret = finv(int(k));
        for (auto i = 0; i < k; ++i) {
            ret *= Z(n - i);
        }
        return ret;
    }
    Z operator()(int n, int k) { return binom(n, k); }

private:
    inline static std::vector<Z> f_{Z(1)}, finv_{Z(1)};
};

#endif // COMBINATORICS_HPP

void solve() {
    int N;
    cin >> N;
    vector<int> A(N + 1);
    for (auto i = 1; i <= N - 1; ++i) {
        cin >> A[i];
    }
    Z target = 1;
    map<int, int> mp;
    for (auto i = 1; i <= N; ++i) {
        assert(!mp.contains(Z(2).inv().pow(i).val()));
        mp[Z(2).inv().pow(i).val()] = i;
    }
    for (auto i = 1; i <= N - 1; ++i) {
        target -= Z(2).inv().pow(A[i]);
    }
    Z ans = 0;
    Combinatorics<Z> C;
    auto Go = [&] {
        vector<pair<int, int>> st;
        vector<array<int, 2>> adj;
        for (auto i = 0; i <= N; ++i) {
            st.emplace_back(A[i], -1);
            while (2 <= st.size() && st[ssize(st) - 1].first == st[ssize(st) - 2].first) {
                auto [d1, c1] = st[ssize(st) - 1];
                auto [d2, c2] = st[ssize(st) - 2];
                st.pop_back();
                st.pop_back();
                auto u = int(adj.size());
                adj.push_back({c1, c2});
                st.emplace_back(d1 - 1, u);
            }
        }
        if (st.size() != 1 || st.back().first != 0) {
            return;
        }
        auto root = st[0].second;
        Z val = 1;
        [&](this auto &&self, int u) -> int {
            if (u == -1)
                return 0;
            auto L = self(adj[u][0]);
            auto R = self(adj[u][1]);
            auto S = L + 1 + R;
            val *= C(S - 1, L);
            return S;
        }(root);
        ans += val;
    };
    for (auto x = 1; x <= N; ++x) {
        auto v = (target - Z(2).inv().pow(x)).val();
        if (mp.contains(v)) {
            auto y = mp[v];
            A[0] = x;
            A[N] = y;
            Go();
        }
    }
    cout << ans.val() << "\n";
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