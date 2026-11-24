#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint1000000007;

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
    int N;
    std::cin >> N;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    std::vector<Z> dp(N + 1);
    dp[N] = 1;
    linear_sieve sieve(std::ranges::max(A));
    for (auto i = N - 1; 0 <= i; --i) {
        if (!sieve.is_prime(A[i])) {
            continue;
        }
        for (auto j = 1; j <= 2; ++j) {
            if (i + j <= N && (i + j == N || A[i] < A[i + j])) {
                dp[i] += dp[i + j];
            }
        }
    }
    std::cout << dp[0].val() << "\n";
}
