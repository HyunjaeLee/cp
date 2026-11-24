#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

struct sieve {
    explicit sieve(int n) : lpf(n + 1) {
        for (auto i = 2; i <= n; ++i) {
            if (lpf[i] == 0) {
                lpf[i] = i;
                primes.push_back(i);
            }
            for (auto p : primes) {
                if (lpf[i] < p || n < i * p) {
                    break;
                }
                lpf[i * p] = p;
            }
        }
    }
    map<int, int> factorize(int x) {
        assert(1 <= x && x < int(lpf.size()));
        map<int, int> f;
        while (1 < x) {
            ++f[lpf[x]];
            x /= lpf[x];
        }
        return f;
    }
    bool is_prime(int x) {
        assert(1 <= x && x < int(lpf.size()));
        return lpf[x] == x;
    }
    vector<int> lpf;
    vector<int> primes;
};

sieve S(1'000'000);

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> A(2 * N - 1);
    for (auto i = N - 1; i < 2 * N - 1; ++i) {
        cin >> A[i];
    }
    for (auto i = 0; i < N - 1; ++i) {
        A[i] = A[N + i];
    }
    map<int, vector<int>> G;
    for (auto i = 0; i < 2 * N - 1; ++i) {
        for (auto [p, e] : S.factorize(A[i])) {
            G[p].push_back(i);
        }
    }
    atcoder::dsu dsu(2 * N - 1);
    for (const auto &[p, v] : G) {
        auto m = int(v.size());
        for (auto i = 0; i < m - 1; ++i) {
            if (v[i + 1] - v[i] <= K) {
                dsu.merge(v[i + 1], v[i]);
            }
        }
    }
    i64 ans = 0;
    for (auto i = 0; i < 2 * N - 1; ++i) {
        if (A[i] == 1) {
            ans += N - abs(N - 1 - i);
        } else if (dsu.leader(i) == i) {
            ans += 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
