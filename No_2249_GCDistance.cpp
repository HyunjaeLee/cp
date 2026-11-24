#include <bits/stdc++.h>

#ifndef EULER_PHI_HPP
#define EULER_PHI_HPP

#include <cassert>
#include <vector>

std::vector<int> euler_phi(int n) {
    assert(0 < n);
    std::vector<int> prime, phi(n + 1);
    std::vector<char> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    phi[1] = 1;
    for (auto i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : prime) {
            if (i * p > n) {
                break;
            }
            is_prime[i * p] = false;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }
    return phi;
}

#endif // EULER_PHI_HPP

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    constexpr auto NMAX = 10'000'000;
    auto phi = euler_phi(NMAX);
    std::vector<long long> pref(NMAX + 1);
    for (auto i = 2; i <= NMAX; ++i) {
        pref[i] = 2 * i - 2 - phi[i];
    }
    for (auto i = 2; i < NMAX; ++i) {
        pref[i + 1] += pref[i];
    }
    int T;
    std::cin >> T;
    while (T--) {
        int N;
        std::cin >> N;
        std::cout << pref[N] << "\n";
    }
}
