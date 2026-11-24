#include <bits/stdc++.h>
using namespace std;
using u32 = unsigned;
using i64 = long long;

template <typename T> void subset_mobius_transform(std::vector<T> &g) {
    assert(std::has_single_bit(g.size()));
    auto n = int(std::countr_zero(g.size()));
    for (auto i = 0; i < n; ++i) {
        for (auto s = 0; s < (1 << n); ++s) {
            if (s & (1 << i)) {
                g[s] -= g[s ^ (1 << i)];
            }
        }
    }
}

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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<i64> f(1 << N);
    for (auto i = 0; i < M; ++i) {
        string s;
        cin >> s;
        auto x = 0;
        for (auto c : s) {
            x |= (1 << (c - 'A'));
        }
        ++f[x];
    }
    vector<int> A(N);
    auto O = 0;
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        if (A[i] & 1) {
            O |= 1 << i;
        }
    }
    vector<vector<i64>> F(N + 1, vector<i64>(1 << N));
    for (auto s = 0; s < (1 << N); ++s) {
        auto r = popcount(u32(s & O));
        F[r][s] = f[s];
    }
    for (auto i = 0; i <= N; ++i) {
        subset_zeta_transform(F[i]);
    }
    vector<vector<i64>> C(N + 1, vector<i64>(1 << N));
    for (auto k = 0; k <= N; ++k) {
        for (auto i = 0; i <= k; ++i) {
            for (auto j = 0; j < (1 << N); ++j) {
                C[k][j] += F[i][j] * F[k - i][j];
            }
        }
        subset_mobius_transform(C[k]);
    }
    vector<i64> ans(ranges::fold_left(A, 0, plus()) + 1);
    for (auto s = 0; s < (1 << N); ++s) {
        auto r = popcount(u32(s & O));
        auto cnt = C[r][s];
        if ((s & O) == 0) {
            cnt -= f[s];
        }
        cnt /= 2;
        auto sum = 0;
        for (auto i = 0; i < N; ++i) {
            if (((s >> i) & 1) == 0) {
                sum += A[i];
            }
        }
        ans[sum] += cnt;
    }
    for (auto x : ans) {
        cout << x << " ";
    }
}
