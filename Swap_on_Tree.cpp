#include <atcoder/convolution>
#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;
using namespace std;
using i64 = long long;
using i128 = __int128;

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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Combinatorics<Z> C;
    vector<vector<Z>> dp(N, vector<Z>(2));
    vector<vector<char>> vis(N, vector<char>(2));
    auto f = [&](auto &&self, int u, int on, int p) -> Z {
        auto &ret = dp[u][on];
        if (vis[u][on])
            return ret;
        vis[u][on] = true;
        vector<Z> F(2);
        F[on] = 1;
        for (auto v : adj[u]) {
            if (v == p)
                continue;
            vector<Z> G(2);
            G[0] = self(self, v, 0, u);
            G[1] = self(self, v, 1, u);
            F = atcoder::convolution(F, G);
        }
        ret = 0;
        for (auto i = 0; i < int(F.size()); ++i) {
            ret += C.f(i) * F[i];
        }
        return ret;
    };
    auto ans = f(f, 0, 0, 0);
    cout << ans.val() << "\n";
}
