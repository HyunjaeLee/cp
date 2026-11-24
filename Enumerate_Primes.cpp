#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

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
    map<int, int> factorize(int x) const { // O(log x)
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

#ifndef CEIL_DIV_HPP
#define CEIL_DIV_HPP

template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }

#endif // CEIL_DIV_HPP

linear_sieve sieve(500000000);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, A, B;
    cin >> N >> A >> B;
    auto pi = int(sieve.primes.size());
    auto X = std::max(0, ceil_div(pi - B, A));
    cout << pi << " " << X << "\n";
    for (auto i = 0; A * i + B < pi; ++i) {
        cout << sieve.primes[A * i + B] << " ";
    }
}
