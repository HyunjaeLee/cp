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

// https://hitonanode.github.io/cplib-cpp/graph/general_matching.hpp
#line 2 "linear_algebra_matrix/matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

namespace matrix_ {
struct has_id_method_impl {
    template <class T_> static auto check(T_ *) -> decltype(T_::id(), std::true_type());
    template <class T_> static auto check(...) -> std::false_type;
};
template <class T_> struct has_id : decltype(has_id_method_impl::check<T_>(nullptr)) {};
} // namespace matrix_

template <typename T> struct matrix {
    int H, W;
    std::vector<T> elem;
    typename std::vector<T>::iterator operator[](int i) { return elem.begin() + i * W; }
    inline T &at(int i, int j) { return elem[i * W + j]; }
    inline T get(int i, int j) const { return elem[i * W + j]; }
    int height() const { return H; }
    int width() const { return W; }
    std::vector<std::vector<T>> vecvec() const {
        std::vector<std::vector<T>> ret(H);
        for (int i = 0; i < H; i++) {
            std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));
        }
        return ret;
    }
    operator std::vector<std::vector<T>>() const { return vecvec(); }
    matrix() = default;
    matrix(int H, int W) : H(H), W(W), elem(H * W) {}
    matrix(const std::vector<std::vector<T>> &d) : H(d.size()), W(d.size() ? d[0].size() : 0) {
        for (auto &raw : d)
            std::copy(raw.begin(), raw.end(), std::back_inserter(elem));
    }

    template <typename T2, typename std::enable_if<matrix_::has_id<T2>::value>::type * = nullptr> static T2 _T_id() {
        return T2::id();
    }
    template <typename T2, typename std::enable_if<!matrix_::has_id<T2>::value>::type * = nullptr> static T2 _T_id() {
        return T2(1);
    }

    static matrix Identity(int N) {
        matrix ret(N, N);
        for (int i = 0; i < N; i++)
            ret.at(i, i) = _T_id<T>();
        return ret;
    }

    matrix operator-() const {
        matrix ret(H, W);
        for (int i = 0; i < H * W; i++)
            ret.elem[i] = -elem[i];
        return ret;
    }
    matrix operator*(const T &v) const {
        matrix ret = *this;
        for (auto &x : ret.elem)
            x *= v;
        return ret;
    }
    matrix operator/(const T &v) const {
        matrix ret = *this;
        const T vinv = _T_id<T>() / v;
        for (auto &x : ret.elem)
            x *= vinv;
        return ret;
    }
    matrix operator+(const matrix &r) const {
        matrix ret = *this;
        for (int i = 0; i < H * W; i++)
            ret.elem[i] += r.elem[i];
        return ret;
    }
    matrix operator-(const matrix &r) const {
        matrix ret = *this;
        for (int i = 0; i < H * W; i++)
            ret.elem[i] -= r.elem[i];
        return ret;
    }
    matrix operator*(const matrix &r) const {
        matrix ret(H, r.W);
        for (int i = 0; i < H; i++) {
            for (int k = 0; k < W; k++) {
                for (int j = 0; j < r.W; j++)
                    ret.at(i, j) += this->get(i, k) * r.get(k, j);
            }
        }
        return ret;
    }
    matrix &operator*=(const T &v) { return *this = *this * v; }
    matrix &operator/=(const T &v) { return *this = *this / v; }
    matrix &operator+=(const matrix &r) { return *this = *this + r; }
    matrix &operator-=(const matrix &r) { return *this = *this - r; }
    matrix &operator*=(const matrix &r) { return *this = *this * r; }
    bool operator==(const matrix &r) const { return H == r.H and W == r.W and elem == r.elem; }
    bool operator!=(const matrix &r) const { return H != r.H or W != r.W or elem != r.elem; }
    bool operator<(const matrix &r) const { return elem < r.elem; }
    matrix pow(int64_t n) const {
        matrix ret = Identity(H);
        bool ret_is_id = true;
        if (n == 0)
            return ret;
        for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {
            if (!ret_is_id)
                ret *= ret;
            if ((n >> i) & 1)
                ret *= (*this), ret_is_id = false;
        }
        return ret;
    }
    std::vector<T> pow_vec(int64_t n, std::vector<T> vec) const {
        matrix x = *this;
        while (n) {
            if (n & 1)
                vec = x * vec;
            x *= x;
            n >>= 1;
        }
        return vec;
    };
    matrix transpose() const {
        matrix ret(W, H);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++)
                ret.at(j, i) = this->get(i, j);
        }
        return ret;
    }
    // Gauss-Jordan elimination
    // - Require inverse for every non-zero element
    // - Complexity: O(H^2 W)
    template <typename T2, typename std::enable_if<std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const matrix<T2> &mtr, int h, int c) noexcept {
        int piv = -1;
        for (int j = h; j < mtr.H; j++) {
            if (mtr.get(j, c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c))))
                piv = j;
        }
        return piv;
    }
    template <typename T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const matrix<T2> &mtr, int h, int c) noexcept {
        for (int j = h; j < mtr.H; j++) {
            if (mtr.get(j, c) != T2())
                return j;
        }
        return -1;
    }
    matrix gauss_jordan() const {
        int c = 0;
        matrix mtr(*this);
        std::vector<int> ws;
        ws.reserve(W);
        for (int h = 0; h < H; h++) {
            if (c == W)
                break;
            int piv = choose_pivot(mtr, h, c);
            if (piv == -1) {
                c++;
                h--;
                continue;
            }
            if (h != piv) {
                for (int w = 0; w < W; w++) {
                    std::swap(mtr[piv][w], mtr[h][w]);
                    mtr.at(piv, w) *= -_T_id<T>(); // To preserve sign of determinant
                }
            }
            ws.clear();
            for (int w = c; w < W; w++) {
                if (mtr.at(h, w) != T())
                    ws.emplace_back(w);
            }
            const T hcinv = _T_id<T>() / mtr.at(h, c);
            for (int hh = 0; hh < H; hh++)
                if (hh != h) {
                    const T coeff = mtr.at(hh, c) * hcinv;
                    for (auto w : ws)
                        mtr.at(hh, w) -= mtr.at(h, w) * coeff;
                    mtr.at(hh, c) = T();
                }
            c++;
        }
        return mtr;
    }
    int rank_of_gauss_jordan() const {
        for (int i = H * W - 1; i >= 0; i--) {
            if (elem[i] != T{})
                return i / W + 1;
        }
        return 0;
    }
    int rank() const { return gauss_jordan().rank_of_gauss_jordan(); }

    T determinant_of_upper_triangle() const {
        T ret = _T_id<T>();
        for (int i = 0; i < H; i++)
            ret *= get(i, i);
        return ret;
    }
    int inverse() {
        assert(H == W);
        std::vector<std::vector<T>> ret = Identity(H), tmp = *this;
        int rank = 0;
        for (int c = 0; c < W; c++) {
            int ti = rank;
            while (ti < H and tmp[ti][c] == T())
                ti++;
            if (ti == H) {
                continue;
            }
            ret[rank].swap(ret[ti]), tmp[rank].swap(tmp[ti]);
            T inv = _T_id<T>() / tmp[rank][c];
            for (int j = 0; j < W; j++)
                ret[rank][j] *= inv;
            for (int j = c + 1; j < W; j++)
                tmp[rank][j] *= inv;
            for (int h = 0; h < H; h++) {
                if (rank == h)
                    continue;
                const T coeff = -tmp[h][c];
                for (int j = 0; j < W; j++)
                    ret[h][j] += ret[rank][j] * coeff;
                for (int j = c + 1; j < W; j++)
                    tmp[h][j] += tmp[rank][j] * coeff;
            }
            rank++;
        }
        *this = ret;
        return rank;
    }
    friend std::vector<T> operator*(const matrix &m, const std::vector<T> &v) {
        assert(m.W == int(v.size()));
        std::vector<T> ret(m.H);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++)
                ret[i] += m.get(i, j) * v[j];
        }
        return ret;
    }
    friend std::vector<T> operator*(const std::vector<T> &v, const matrix &m) {
        assert(int(v.size()) == m.H);
        std::vector<T> ret(m.W);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++)
                ret[j] += v[i] * m.get(i, j);
        }
        return ret;
    }
    std::vector<T> prod(const std::vector<T> &v) const { return (*this) * v; }
    std::vector<T> prod_left(const std::vector<T> &v) const { return v * (*this); }
    template <class OStream> friend OStream &operator<<(OStream &os, const matrix &x) {
        os << "[(" << x.H << " * " << x.W << " matrix)";
        os << "\n[column sums: ";
        for (int j = 0; j < x.W; j++) {
            T s = T();
            for (int i = 0; i < x.H; i++)
                s += x.get(i, j);
            os << s << ",";
        }
        os << "]";
        for (int i = 0; i < x.H; i++) {
            os << "\n[";
            for (int j = 0; j < x.W; j++)
                os << x.get(i, j) << ",";
            os << "]";
        }
        os << "]\n";
        return os;
    }
    template <class IStream> friend IStream &operator>>(IStream &is, matrix &x) {
        for (auto &v : x.elem)
            is >> v;
        return is;
    }
};
#line 3 "modint.hpp"
#include <iostream>
#include <set>
#line 6 "modint.hpp"

template <int md> struct ModInt {
    static_assert(md > 1);
    using lint = long long;
    constexpr static int mod() { return md; }
    static int get_primitive_root() {
        static int primitive_root = 0;
        if (!primitive_root) {
            primitive_root = [&]() {
                std::set<int> fac;
                int v = md - 1;
                for (lint i = 2; i * i <= v; i++)
                    while (v % i == 0)
                        fac.insert(i), v /= i;
                if (v > 1)
                    fac.insert(v);
                for (int g = 1; g < md; g++) {
                    bool ok = true;
                    for (auto i : fac)
                        if (ModInt(g).pow((md - 1) / i) == 1) {
                            ok = false;
                            break;
                        }
                    if (ok)
                        return g;
                }
                return -1;
            }();
        }
        return primitive_root;
    }
    int val_;
    int val() const noexcept { return val_; }
    constexpr ModInt() : val_(0) {}
    constexpr ModInt &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }
    constexpr ModInt(lint v) { _setval(v % md + md); }
    constexpr explicit operator bool() const { return val_ != 0; }
    constexpr ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val_ + x.val_); }
    constexpr ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val_ - x.val_ + md); }
    constexpr ModInt operator*(const ModInt &x) const { return ModInt()._setval((lint)val_ * x.val_ % md); }
    constexpr ModInt operator/(const ModInt &x) const { return ModInt()._setval((lint)val_ * x.inv().val() % md); }
    constexpr ModInt operator-() const { return ModInt()._setval(md - val_); }
    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x; }
    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this - x; }
    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this * x; }
    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this / x; }
    friend constexpr ModInt operator+(lint a, const ModInt &x) { return ModInt(a) + x; }
    friend constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt(a) - x; }
    friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt(a) * x; }
    friend constexpr ModInt operator/(lint a, const ModInt &x) { return ModInt(a) / x; }
    constexpr bool operator==(const ModInt &x) const { return val_ == x.val_; }
    constexpr bool operator!=(const ModInt &x) const { return val_ != x.val_; }
    constexpr bool operator<(const ModInt &x) const { return val_ < x.val_; } // To use std::map<ModInt, T>
    friend std::istream &operator>>(std::istream &is, ModInt &x) {
        lint t;
        return is >> t, x = ModInt(t), is;
    }
    constexpr friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return os << x.val_; }

    constexpr ModInt pow(lint n) const {
        ModInt ans = 1, tmp = *this;
        while (n) {
            if (n & 1)
                ans *= tmp;
            tmp *= tmp, n >>= 1;
        }
        return ans;
    }

    static constexpr int cache_limit = std::min(md, 1 << 21);
    static std::vector<ModInt> facs, facinvs, invs;

    constexpr static void _precalculation(int N) {
        const int l0 = facs.size();
        if (N > md)
            N = md;
        if (N <= l0)
            return;
        facs.resize(N), facinvs.resize(N), invs.resize(N);
        for (int i = l0; i < N; i++)
            facs[i] = facs[i - 1] * i;
        facinvs[N - 1] = facs.back().pow(md - 2);
        for (int i = N - 2; i >= l0; i--)
            facinvs[i] = facinvs[i + 1] * (i + 1);
        for (int i = N - 1; i >= l0; i--)
            invs[i] = facinvs[i] * facs[i - 1];
    }

    constexpr ModInt inv() const {
        if (this->val_ < cache_limit) {
            if (facs.empty())
                facs = {1}, facinvs = {1}, invs = {0};
            while (this->val_ >= int(facs.size()))
                _precalculation(facs.size() * 2);
            return invs[this->val_];
        } else {
            return this->pow(md - 2);
        }
    }

    constexpr static ModInt fac(int n) {
        assert(n >= 0);
        if (n >= md)
            return ModInt(0);
        while (n >= int(facs.size()))
            _precalculation(facs.size() * 2);
        return facs[n];
    }

    constexpr static ModInt facinv(int n) {
        assert(n >= 0);
        if (n >= md)
            return ModInt(0);
        while (n >= int(facs.size()))
            _precalculation(facs.size() * 2);
        return facinvs[n];
    }

    constexpr static ModInt doublefac(int n) {
        assert(n >= 0);
        if (n >= md)
            return ModInt(0);
        long long k = (n + 1) / 2;
        return (n & 1) ? ModInt::fac(k * 2) / (ModInt(2).pow(k) * ModInt::fac(k)) : ModInt::fac(k) * ModInt(2).pow(k);
    }

    constexpr static ModInt nCr(int n, int r) {
        assert(n >= 0);
        if (r < 0 or n < r)
            return ModInt(0);
        return ModInt::fac(n) * ModInt::facinv(r) * ModInt::facinv(n - r);
    }

    constexpr static ModInt nPr(int n, int r) {
        assert(n >= 0);
        if (r < 0 or n < r)
            return ModInt(0);
        return ModInt::fac(n) * ModInt::facinv(n - r);
    }

    static ModInt binom(long long n, long long r) {
        static long long bruteforce_times = 0;

        if (r < 0 or n < r)
            return ModInt(0);
        if (n <= bruteforce_times or n < (int)facs.size())
            return ModInt::nCr(n, r);

        r = std::min(r, n - r);
        assert((int)r == r);

        ModInt ret = ModInt::facinv(r);
        for (int i = 0; i < r; ++i)
            ret *= n - i;
        bruteforce_times += r;

        return ret;
    }

    // Multinomial coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)
    // Complexity: O(sum(ks))
    // Verify: https://yukicoder.me/problems/no/3178
    template <class Vec> static ModInt multinomial(const Vec &ks) {
        ModInt ret{1};
        int sum = 0;
        for (int k : ks) {
            assert(k >= 0);
            ret *= ModInt::facinv(k), sum += k;
        }
        return ret * ModInt::fac(sum);
    }
    template <class... Args> static ModInt multinomial(Args... args) {
        int sum = (0 + ... + args);
        ModInt result = (1 * ... * ModInt::facinv(args));
        return ModInt::fac(sum) * result;
    }

    // Catalan number, C_n = binom(2n, n) / (n + 1) = # of Dyck words of length 2n
    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4 = 14, ...
    // https://oeis.org/A000108
    // Complexity: O(n)
    static ModInt catalan(int n) {
        if (n < 0)
            return ModInt(0);
        return ModInt::fac(n * 2) * ModInt::facinv(n + 1) * ModInt::facinv(n);
    }

    ModInt sqrt() const {
        if (val_ == 0)
            return 0;
        if (md == 2)
            return val_;
        if (pow((md - 1) / 2) != 1)
            return 0;
        ModInt b = 1;
        while (b.pow((md - 1) / 2) == 1)
            b += 1;
        int e = 0, m = md - 1;
        while (m % 2 == 0)
            m >>= 1, e++;
        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;
        x *= (*this);
        ModInt z = b.pow(m);
        while (y != 1) {
            int j = 0;
            ModInt t = y;
            while (t != 1)
                j++, t *= t;
            z = z.pow(1LL << (e - j - 1));
            x *= z, z *= z, y *= z;
            e = j;
        }
        return ModInt(std::min(x.val_, md - x.val_));
    }
};
template <int md> std::vector<ModInt<md>> ModInt<md>::facs = {1};
template <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};
template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};

using ModInt998244353 = ModInt<998244353>;
// using mint = ModInt<998244353>;
// using mint = ModInt<1000000007>;
#line 5 "graph/general_matching.hpp"
#include <chrono>
#include <queue>
#include <random>
#line 10 "graph/general_matching.hpp"

// CUT begin
// Find maximum matchings in general graph using the Tutte matrix (The Rabin-Vazirani algorithm)
// Complexity: O(N^3)
// Reference: https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/GeneralMatching.h
//            https://kopricky.github.io/code/Academic/maximum_matching.html
std::vector<std::pair<int, int>> generalMatching(int N, std::vector<std::pair<int, int>> ed) {
    using MODINT = ModInt<1000000007>;
    std::vector<std::pair<int, int>> ed_tmp;
    for (auto p : ed) {
        if (p.first != p.second) {
            ed_tmp.emplace_back(std::minmax(p.first, p.second));
        }
    }
    ed = ed_tmp, std::sort(ed.begin(), ed.end()), ed.erase(std::unique(ed.begin(), ed.end()), ed.end());
    std::vector<std::pair<int, int>> ret;

    std::vector<int> deg(N), used(N);
    std::vector<std::vector<int>> conn(N);
    for (auto p : ed) {
        deg[p.first]++, deg[p.second]++;
        conn[p.first].emplace_back(p.second), conn[p.second].emplace_back(p.first);
    }
    std::queue<int> q_deg1;
    for (int i = 0; i < N; i++) {
        if (deg[i] == 1) {
            q_deg1.emplace(i);
        }
    }
    while (q_deg1.size()) {
        int i = q_deg1.front(), j = -1;
        q_deg1.pop();
        if (!used[i]) {
            for (auto k : conn[i]) {
                if (!used[k]) {
                    j = k, ret.emplace_back(i, j);
                    break;
                }
            }
        }
        for (int t = 0; t < 2; t++) {
            if (i >= 0 and !used[i]) {
                used[i] = 1;
                for (auto k : conn[i]) {
                    deg[k]--;
                    if (deg[k] == 1) {
                        q_deg1.emplace(k);
                    }
                }
            }
            std::swap(i, j);
        }
    }

    std::vector<int> idx(N, -1), idx_inv;
    for (int i = 0; i < N; i++) {
        if (deg[i] > 0 and !used[i]) {
            idx[i] = idx_inv.size(), idx_inv.emplace_back(i);
        }
    }

    const int D = idx_inv.size();
    if (D == 0) {
        return ret;
    }
    std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> d(MODINT::mod());

    std::vector<std::vector<MODINT>> mat(D, std::vector<MODINT>(D));
    for (auto p : ed) {
        int a = idx[p.first], b = idx[p.second];
        if (a < 0 or b < 0)
            continue;
        mat[a][b] = d(mt), mat[b][a] = -mat[a][b];
    }
    matrix<MODINT> A = mat;
    const int rank = A.inverse(), M = 2 * D - rank;
    if (M != D) {
        do {
            mat.resize(M, std::vector<MODINT>(M));
            for (int i = 0; i < D; i++) {
                mat[i].resize(M);
                for (int j = D; j < M; j++) {
                    mat[i][j] = d(mt), mat[j][i] = -mat[i][j];
                }
            }
            A = mat;
        } while (A.inverse() != M);
    }

    std::vector<int> has(M, 1);
    int fi = -1, fj = -1;
    for (int it = 0; it < M / 2; it++) {
        [&]() {
            for (int i = 0; i < M; i++) {
                if (has[i]) {
                    for (int j = i + 1; j < M; j++) {
                        if (A[i][j] and mat[i][j]) {
                            fi = i, fj = j;
                            return;
                        }
                    }
                }
            }
        }();
        if (fj < D) {
            ret.emplace_back(idx_inv[fi], idx_inv[fj]);
        }
        has[fi] = has[fj] = 0;
        for (int sw = 0; sw < 2; sw++) {
            MODINT a = A[fi][fj].inv();
            for (int i = 0; i < M; i++) {
                if (has[i] and A[i][fj]) {
                    MODINT b = A[i][fj] * a;
                    for (int j = 0; j < M; j++) {
                        A[i][j] -= A[fi][j] * b;
                    }
                }
            }
            std::swap(fi, fj);
        }
    }
    return ret;
}

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    read(A);
    vector<vector<int>> G(N, vector<int>(N));
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u][v] = G[v][u] = 1;
    }
    vector<int> V;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < A[i]; ++j) {
            V.push_back(i);
        }
    }
    vector<pair<int, int>> E;
    for (auto i = 0; i < ssize(V); ++i) {
        for (auto j = i + 1; j < ssize(V); ++j) {
            if (G[V[i]][V[j]]) {
                E.emplace_back(i, j);
            }
        }
    }
    cout << generalMatching(int(V.size()), E).size() << "\n";
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
