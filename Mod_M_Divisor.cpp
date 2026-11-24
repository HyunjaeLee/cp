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

#ifndef FACTOR_HPP
#define FACTOR_HPP

#include <algorithm>
#include <numeric>
#include <vector>

unsigned long long modmul(unsigned long long a, unsigned long long b, unsigned long long M) {
    long long ret = a * b - M * (unsigned long long)(1.L / (long double)M * (long double)a * (long double)b);
    return ret + M * (ret < 0) - M * (ret >= (long long)(M));
}

unsigned long long modpow(unsigned long long b, unsigned long long e, unsigned long long mod) {
    unsigned long long ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2) {
        if (e & 1) {
            ans = modmul(ans, b, mod);
        }
    }
    return ans;
}

bool is_prime(unsigned long long n) {
    if (n < 2 || n % 6 % 4 != 1) {
        return (n | 1) == 3;
    }
    unsigned long long A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;
    for (unsigned long long a : A) {
        unsigned long long p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) {
            p = modmul(p, p, n);
        }
        if (p != n - 1 && i != s) {
            return 0;
        }
    }
    return 1;
}

unsigned long long pollard(unsigned long long n) {
    unsigned long long x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    auto f = [&](unsigned long long a) { return modmul(a, a, n) + i; };
    while (t++ % 40 || std::gcd(prd, n) == 1) {
        if (x == y) {
            x = ++i, y = f(x);
        }
        if ((q = modmul(prd, std::max(x, y) - std::min(x, y), n))) {
            prd = q;
        }
        x = f(x), y = f(f(y));
    }
    return std::gcd(prd, n);
}

std::vector<unsigned long long> factor(unsigned long long n) {
    if (n == 1) {
        return {};
    }
    if (is_prime(n)) {
        return {n};
    }
    auto x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

unsigned long long euler_phi(unsigned long long n) {
    auto f = factor(n);
    std::sort(f.begin(), f.end());
    f.erase(std::unique(f.begin(), f.end()), f.end());
    for (auto p : f) {
        n -= n / p;
    }
    return n;
}

#endif // FACTOR_HPP

void solve() {
    i64 N, M;
    cin >> N >> M;
    if (N == 1) {
        vector<int> ans(M, -1);
        ans[1 % M] = 1;
        show(ans, "\n");
        return;
    }
    auto P = factor(N);
    constexpr auto inf = std::numeric_limits<int>::max() / 2;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(ssize(P) * M, inf);
    dist[1 % M] = 0;
    pq.emplace(0, 1 % M);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] != d)
            continue;
        auto i = u / M;
        auto x = u % M;
        auto j = i == ssize(P) - 1 ? 0 : i + 1;
        auto y = int(i128(P[i]) * x % M);
        auto w = i == ssize(P) - 1 ? 1 : 0;
        for (auto v : {j * M + x, j * M + y}) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    for (auto x = 0; x < M; ++x) {
        if (dist[x] == 0)
            dist[x] = 1;
        else if (dist[x] == inf)
            dist[x] = -1;
        cout << dist[x] << "\n";
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
