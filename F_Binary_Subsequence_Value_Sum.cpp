#include <atcoder/convolution>
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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

#ifndef COMBINATORICS_HPP
#define COMBINATORICS_HPP

#include <algorithm>
#include <bit>
#include <cassert>
#include <vector>

template <typename Z> struct Combinatorics {
    static void grow(int n) {
        auto m = int(f_.size());
        if (n < m) {
            return;
        }
        n = std::min<int>(std::bit_ceil(unsigned(n + 1)), Z::mod());
        f_.resize(n);
        finv_.resize(n);
        for (auto i = m; i < n; ++i) {
            f_[i] = f_[i - 1] * Z(i);
        }
        finv_[n - 1] = f_[n - 1].inv();
        for (auto i = n - 1; m < i; --i) {
            finv_[i - 1] = finv_[i] * Z(i);
        }
    }
    static Z f(int n) { // O(1)
        assert(0 <= n);
        grow(n);
        return f_[n];
    }
    static Z finv(int n) { // O(1)
        assert(0 <= n);
        grow(n);
        return finv_[n];
    }
    static Z binom(int n, int k) { // O(1)
        if (0 <= k && k <= n) {
            return f(n) * finv(k) * finv(n - k);
        } else {
            return Z(0);
        }
    }
    static Z binom2(long long n, long long k) { // O(min(k, n - k))
        if (k < 0 || n < k) {
            return Z(0);
        }
        if (n - k < k) {
            return binom2(n, n - k);
        }
        auto ret = finv(int(k));
        for (auto i = 0; i < k; ++i) {
            ret *= Z(n - i);
        }
        return ret;
    }
    Z operator()(int n, int k) { return binom(n, k); }

private:
    inline static std::vector<Z> f_{Z(1)}, finv_{Z(1)};
};

#endif // COMBINATORICS_HPP

using i64 = long long;

int mod_inv(int a, int mod) {
    int b = mod, s = 1, t = 0, old_a = a;
    while (b) {
        int q = a / b;
        swap(a %= b, b);
        swap(s -= t * q, t);
    }
    if (a != 1) {
        fprintf(stderr, "Error: %d^{-1} mod %d does not exist.\n\n", old_a, mod);
        assert(0);
    }
    return s < 0 ? s + mod : s;
}

vector<int> extended(int n, const vector<vector<int>> &coeffs, const vector<int> &terms, int mod) {

    vector<int> ret(max<int>(n + 1, terms.size()));
    copy(terms.begin(), terms.end(), ret.begin());
    const int order = coeffs.size() - 1;
    const int deg = coeffs[0].size() - 1;
    assert((int)terms.size() >= order);
    for (int m = terms.size(); m <= n; ++m) {
        int s = 0;
        for (int i = 1; i <= order; ++i) {
            int k = m - i, t = ret[k];
            for (int d = 0; d <= deg; ++d) {
                s = (s + i64(t) * coeffs[i][d]) % mod;
                t = i64(t) * k % mod;
            }
        }
        int denom = 0, mpow = 1;
        for (int d = 0; d <= deg; ++d) {
            denom = (denom + i64(mpow) * coeffs[0][d]) % mod;
            mpow = i64(mpow) * m % mod;
        }
        ret[m] = i64(mod - s) * mod_inv(denom, mod) % mod;
    }
    return ret;
}

vector<vector<int>> find_recurrence_relation(const vector<int> &terms, const int deg, const int mod,
                                             bool verify = true) {

    const int n = terms.size();
    const int B = (n + 2) / (deg + 2); // number of blocks
    const int C = B * (deg + 1);       // number of columns
    const int R = n - (B - 1);         // number of rows
    assert(B >= 2);
    assert(R >= C - 1);

    auto mul = [mod](int a, int b) { return i64(a) * b % mod; };
    auto fixed = [mod](int a) { return (a %= mod) < 0 ? a + mod : a; };
    auto error = [](int order, int deg) {
        fprintf(stderr,
                "Error: Could not find a recurrence relation "
                "of order <= %d and degree <= %d.\n\n",
                order, deg);
        assert(0);
    };

    vector<vector<int>> mat(R, vector<int>(C));
    for (int y = 0; y < R; ++y) {
        for (int b = 0; b < B; ++b) {
            for (int d = 0, v = fixed(terms[y + b]); d <= deg; ++d) {
                mat[y][b * (deg + 1) + d] = v;
                v = mul(v, y + b);
            }
        }
    }

    int rank = 0;
    for (int x = 0; x < C; ++x) {
        int pivot = -1;
        for (int y = rank; y < R; ++y)
            if (mat[y][x] != 0) {
                pivot = y;
                break;
            }
        if (pivot < 0)
            break;
        if (pivot != rank)
            swap(mat[rank], mat[pivot]);
        int inv = mod_inv(mat[rank][x], mod);
        for (int x2 = x; x2 < C; ++x2)
            mat[rank][x2] = mul(mat[rank][x2], inv);
        for (int y = rank + 1; y < R; ++y)
            if (mat[y][x]) {
                int c = mod - mat[y][x];
                for (int x2 = x; x2 < C; ++x2) {
                    mat[y][x2] = (i64(mat[y][x2]) + i64(c) * mat[rank][x2]) % mod;
                }
            }
        ++rank;
    }

    if (rank == C)
        error(B - 1, deg);

    for (int y = rank - 1; y >= 0; --y)
        if (mat[y][rank]) {
            assert(mat[y][y] == 1);
            int c = mod - mat[y][rank];
            for (int y2 = 0; y2 < y; ++y2) {
                mat[y2][rank] = (mat[y2][rank] + i64(c) * mat[y2][y]) % mod;
            }
        }

    int order = rank / (deg + 1);
    vector<vector<int>> ret(order + 1, vector<int>(deg + 1));
    ret[0][rank % (deg + 1)] = 1;
    for (int y = rank - 1; y >= 0; --y) {
        int k = order - y / (deg + 1), d = y % (deg + 1);
        ret[k][d] = (mod - mat[y][rank]) % mod;
    }

    if (verify) {
        auto extended_terms = extended(n - 1, ret, vector<int>(terms.begin(), terms.begin() + order), mod);
        for (int i = 0; i < (int)terms.size(); ++i) {
            if (fixed(terms[i] - extended_terms[i]) != 0)
                error(B - 1, deg);
        }
    }

    auto verbose = [&] {
        int last = verify ? n - 1 : order + R - 1;
        fprintf(stderr,
                "[ Found a recurrence relation ]\n"
                "- order %d\n"
                "- degree %d\n"
                "- verified up to a(%d) (number of non-trivial terms: %d)\n",
                order, deg, last, (last + 1) - ((deg + 2) * (order + 1) - 2));
        fprintf(stderr, "{\n");
        for (int k = 0; k <= order; ++k) {
            fprintf(stderr, "  {");
            for (int d = 0; d <= deg; ++d) {
                if (d)
                    fprintf(stderr, ", ");
                fprintf(stderr, "%d", ret[k][d] <= mod / 2 ? ret[k][d] : ret[k][d] - mod);
            }
            fprintf(stderr, "}%s\n", k == order ? "" : ",");
        }
        fprintf(stderr, "}\n\n");
    };
    verbose();

    return ret;
}

void solve_p() {
    int N, Q;
    cin >> N >> Q;
    vector<int> S(N);
    for (auto i = 0; i < N; ++i) {
        char c;
        cin >> c;
        S[i] = c & 1;
    }
    Combinatorics<Z> C;
    auto F = [&](int x) {
        Z sum = 0;
        for (auto i = 0; i <= x; ++i) {
            for (auto j = 0; j <= N - x; ++j) {
                sum += C(x, i) * C(N - x, j) * (1LL * (i - j) * (i - j) / 4);
            }
        }
        return sum;
    };
    vector<int> A(min(10, N) + 1);
    for (auto i = 0; i < int(A.size()); ++i) {
        A[i] = F(i).val();
    }
    if (10 < N) {
        auto coeffs = find_recurrence_relation(A, 0, 998244353, false);
        A = extended(N + 1, coeffs, A, 998244353);
    }
    auto one = ranges::count(S, 1);
    while (Q--) {
        int i;
        cin >> i;
        --i;
        S[i] ^= 1;
        if (S[i]) {
            one++;
        } else {
            one--;
        }
        auto ans = A[one];
        cout << ans << "\n";
    }
}

#define TC
void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> S(N);
    for (auto i = 0; i < N; ++i) {
        char c;
        cin >> c;
        S[i] = c & 1;
    }
    vector<Z> A(N + 1), B(2 * N + 1);
    for (auto i = 0; i <= N; ++i) {
        A[i] = Combinatorics<Z>::binom(N, i);
    }
    for (auto i = -N; i <= N; ++i) {
        B[N + i] = (1LL * i * i) / 4;
    }
    auto C = convolution(A, B);
    auto zero = ranges::count(S, 0);
    while (Q--) {
        int i;
        cin >> i;
        --i;
        S[i] ^= 1;
        if (S[i]) {
            zero--;
        } else {
            zero++;
        }
        auto ans = C[zero + N];
        cout << ans.val() << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve_p();
    }
}
