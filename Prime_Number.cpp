#include <bits/stdc++.h>

struct linear_sieve {
    explicit linear_sieve(int n) : lpf(n + 1) {
        for (auto i = 2; i <= n; ++i) {
            if (lpf[i] == 0) {
                lpf[i] = i;
                primes.push_back(i);
            }
            for (auto p : primes) {
                if (lpf[i] < p || n < 1LL * i * p) {
                    break;
                }
                lpf[i * p] = p;
            }
        }
    }
    std::map<int, int> factorize(int x) const { // O(log x)
        assert(1 <= x && x < int(lpf.size()));
        std::map<int, int> f;
        while (1 < x) {
            ++f[lpf[x]];
            x /= lpf[x];
        }
        return f;
    }
    bool is_prime(int x) const { // O(1)
        assert(1 <= x && x < int(lpf.size()));
        return lpf[x] == x;
    }
    std::vector<int> lpf;
    std::vector<int> primes;
};

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::vector<int> A;
    for (int x; std::cin >> x;) {
        A.push_back(x);
    }
    linear_sieve sieve(std::ranges::max(A));
    for (auto x : A) {
        auto it = std::ranges::upper_bound(sieve.primes, x);
        auto ans = it - sieve.primes.begin();
        std::cout << ans << "\n";
    }
}
