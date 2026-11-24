#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;

template <typename T> void subset_zeta_transform(std::vector<T> &f) {
    assert(std::has_single_bit(f.size()));
    auto n = int(std::countr_zero(f.size()));
    for (auto i = 0; i < n; ++i) {
        for (auto t = 0; t < (1 << n); ++t) {
            if (t & (1 << i)) {
                f[t] += f[t ^ (1 << i)];
            }
        }
    }
}

template <typename T> void subset_mobius_transform(std::vector<T> &g) {
    assert(std::has_single_bit(g.size()));
    auto n = int(std::countr_zero(g.size()));
    for (auto i = 0; i < n; ++i) {
        for (auto t = 0; t < (1 << n); ++t) {
            if (t & (1 << i)) {
                g[t] -= g[t ^ (1 << i)];
            }
        }
    }
}

template <typename T> void superset_zeta_transform(std::vector<T> &f) {
    assert(std::has_single_bit(f.size()));
    auto n = int(std::countr_zero(f.size()));
    for (auto i = 0; i < n; ++i) {
        for (auto t = 0; t < (1 << n); ++t) {
            if (t & (1 << i)) {
                f[t ^ (1 << i)] += f[t];
            }
        }
    }
}

template <typename T> void superset_mobius_transform(std::vector<T> &g) {
    assert(std::has_single_bit(g.size()));
    auto n = int(std::countr_zero(g.size()));
    for (auto i = 0; i < n; ++i) {
        for (auto t = 0; t < (1 << n); ++t) {
            if (t & (1 << i)) {
                g[t ^ (1 << i)] -= g[t];
            }
        }
    }
}

template <typename T> std::vector<T> and_convolution(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    superset_zeta_transform(a);
    superset_zeta_transform(b);
    for (auto i = 0; i < int(a.size()); ++i) {
        a[i] *= b[i];
    }
    superset_mobius_transform(a);
    return a;
}

template <typename T> std::vector<T> or_convolution(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    subset_zeta_transform(a);
    subset_zeta_transform(b);
    for (auto i = 0; i < int(a.size()); ++i) {
        a[i] *= b[i];
    }
    subset_mobius_transform(a);
    return a;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<Z> A(1 << N);
    for (auto i = 0; i < (1 << N); ++i) {
        int x;
        std::cin >> x;
        A[i] = x;
    }
    std::vector<Z> B(1 << N);
    for (auto i = 0; i < (1 << N); ++i) {
        int x;
        std::cin >> x;
        B[i] = x;
    }
    std::ranges::reverse(A);
    std::ranges::reverse(B);
    auto C = or_convolution(A, B);
    std::ranges::reverse(C);
    for (auto i = 0; i < (1 << N); ++i) {
        std::cout << C[i].val() << " ";
    }
}
