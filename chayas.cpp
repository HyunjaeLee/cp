#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;

#ifndef SUBSET_ZETA_HPP
#define SUBSET_ZETA_HPP

#include <bit>
#include <cassert>
#include <vector>

template <typename T> void subset_zeta_transform(std::vector<T> &f) {
    assert(std::has_single_bit(f.size()));
    auto n = int(std::countr_zero(f.size()));
    for (auto i = 0; i < n; ++i) {
        for (auto s = 0; s < (1 << n); ++s) {
            if (s & (1 << i)) {
                f[s] += f[s ^ (1 << i)];
            }
        }
    }
}

#endif // SUBSET_ZETA_HPP

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> f(1 << n);
    for (auto i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        --a, --b, --c;
        f[(1 << a) | (1 << c)] += 1;
        f[(1 << b)] += 1;
        f[(1 << a) | (1 << b)] -= 1;
        f[(1 << b) | (1 << c)] -= 1;
    }
    subset_zeta_transform(f);
    std::vector<Z> dp(1 << n);
    dp[(1 << n) - 1] = 1;
    for (auto s = (1 << n) - 2; 0 <= s; --s) {
        for (auto i = 0; i < n; ++i) {
            if (((s >> i) & 1) == 0 && f[s] == 0 && f[s | (1 << i)] == 0) {
                dp[s] += dp[s | (1 << i)];
            }
        }
    }
    std::cout << dp[0].val() << "\n";
}
