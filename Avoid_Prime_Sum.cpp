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

#ifndef LINEAR_SIEVE_HPP
#define LINEAR_SIEVE_HPP

#include <cassert>
#include <map>
#include <vector>

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

#endif // LINEAR_SIEVE_HPP

linear_sieve sieve(2100100);

bool check(const vector<vector<int>> &A) {
    auto N = int(A.size());
    for (auto i = 0; i < N - 1; ++i) {
        for (auto j = 0; j < N; ++j) {
            if (sieve.is_prime(A[i][j] + A[i + 1][j])) {
                return false;
            }
        }
    }
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N - 1; ++j) {
            if (sieve.is_prime(A[i][j] + A[i][j + 1])) {
                return false;
            }
        }
    }
    return true;
}

void solve() {
    int N;
    cin >> N;
    if (N == 3) {
        cout << "1 3 5\n";
        cout << "8 7 9\n";
        cout << "4 2 6\n";
        return;
    }
    vector<vector<int>> A(N, vector<int>(N));
    if (N % 2 == 0) {
        for (auto i = 0; i < N / 2; ++i) {
            for (auto j = 0; j < N; ++j) {
                A[i][j] = 2 * (i * N + j + 1);
            }
        }
        set<int> S;
        for (auto i = 1; i <= N * N; i += 2) {
            S.insert(i);
        }
        for (auto it = prev(S.end());; --it) {
            if (!sieve.is_prime(A[N / 2 - 1][0] + *it)) {
                A[N / 2][0] = *it;
                S.erase(it);
                break;
            }
        }
        for (auto i = 1; i < N; ++i) {
            A[N / 2][i] = A[N / 2][i - 1] - 2;
            S.erase(A[N / 2][i - 1] - 2);
        }
        auto it = S.begin();
        for (auto i = N / 2 + 1; i < N; ++i) {
            for (auto j = 0; j < N; ++j) {
                A[i][j] = *it++;
            }
        }
    } else {
        {
            vector<int> v;
            for (auto i = 1; i <= N * N; i += 2) {
                v.push_back(i);
            }
            auto it = v.begin();
            for (auto i = 0; i < N / 2; ++i) {
                for (auto j = 0; j < N; ++j) {
                    A[i][j] = *it++;
                }
            }
            for (auto j = N / 2; j < N; ++j) {
                A[N / 2][j] = *it++;
            }
        }
        set<int> S;
        for (auto i = 2; i <= N * N; i += 2) {
            S.insert(i);
        }
        for (auto it = begin(S);; ++it) {
            if (!sieve.is_prime(A[N / 2][N / 2] + *it) && !sieve.is_prime(A[N / 2 - 1][N / 2 - 1] + *it)) {
                A[N / 2][N / 2 - 1] = *it;
                S.erase(it);
                break;
            }
        }
        for (auto j = N / 2 - 2; 0 <= j; --j) {
            A[N / 2][j] = A[N / 2][j + 1] + 2;
            S.erase(A[N / 2][j + 1] + 2);
        }
        for (auto it = prev(end(S));; --it) {
            if (!sieve.is_prime(A[N / 2][N / 2] + *it)) {
                A[N / 2 + 1][N / 2] = *it;
                S.erase(it);
                break;
            }
        }
        for (auto j = N / 2 + 1; j < N; ++j) {
            A[N / 2 + 1][j] = A[N / 2 + 1][j - 1] - 2;
            S.erase(A[N / 2][j - 1] - 2);
        }
        auto it = S.begin();
        for (auto i = 0; i < N; ++i) {
            for (auto j= 0; j < N; ++j) {
                if (A[i][j] == 0) {
                    A[i][j] = *it++;
                }
            }
        }
    }
    assert(check(A));
    for (auto i = 0; i < N; ++i) {
        show(A[i]);
    }
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
