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

#ifndef MODINT_HPP
#define MODINT_HPP

#include <cassert>
#include <concepts>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

template <std::signed_integral auto mod> struct modint {
    using T = decltype(mod);
    static_assert(0 < mod && mod <= std::numeric_limits<T>::max() / 2 + 1);
    constexpr modint() : v(0) {}
    constexpr modint(std::integral auto x) : v(T((x % mod + mod) % mod)) {}
    constexpr modint &operator+=(modint o) {
        v = (v + o.v) % mod;
        return *this;
    }
    constexpr modint &operator-=(modint o) {
        v = (v - o.v + mod) % mod;
        return *this;
    }
    constexpr modint &operator*=(modint o) {
        static_assert(sizeof(T) <= sizeof(long long));
        using U = std::conditional_t<sizeof(T) <= sizeof(int), long long, __int128>;
        v = T(U(v) * o.v % mod);
        return *this;
    }
    constexpr modint &operator/=(modint o) { return *this *= o.inv(); }
    constexpr modint operator-() const { return -v; }
    constexpr modint operator+() const { return *this; }
    friend constexpr modint operator+(modint l, modint r) { return l += r; }
    friend constexpr modint operator-(modint l, modint r) { return l -= r; }
    friend constexpr modint operator*(modint l, modint r) { return l *= r; }
    friend constexpr modint operator/(modint l, modint r) { return l /= r; }
    friend bool operator==(modint, modint) = default;
    constexpr modint pow(std::integral auto n) const {
        assert(0 <= n);
        modint x = *this, r = 1;
        for (; n; x *= x, n /= 2) {
            if (n & 1) {
                r *= x;
            }
        }
        return r;
    }
    constexpr modint inv() const {
        T a = v, b = mod, s = 1, t = 0;
        while (b) {
            T q = a / b;
            std::swap(a -= b * q, b);
            std::swap(s -= t * q, t);
        }
        assert(a == 1);
        return s;
    }
    constexpr T val() const { return v; }
    friend std::ostream &operator<<(std::ostream &os, modint a) { return os << a.v; }
    friend std::istream &operator>>(std::istream &is, modint &a) {
        long long x;
        is >> x;
        a = x;
        return is;
    }

private:
    T v;
};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;

#endif // MODINT_HPP

#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <type_traits>
#include <utility>

// https://github.com/ecnerwala/cp-book/blob/master/src/tensor.hpp
template <typename T, int NDIMS> struct tensor_view {
    static_assert(0 < NDIMS);

    tensor_view() : shape_{}, strides_{}, data_(nullptr) {}

    T &operator[](std::array<int, NDIMS> idx) const {
#ifdef _GLIBCXX_DEBUG
        return data_[flatten_index_checked(idx)];
#else
        return data_[flatten_index(idx)];
#endif
    }
#ifdef __cpp_multidimensional_subscript
    template <typename... I>
        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))
    T &operator[](I... idx) const {
        return (*this)[std::array<int, NDIMS>{static_cast<int>(idx)...}];
    }
#endif
    decltype(auto) operator[](int idx) const {
#ifdef _GLIBCXX_DEBUG
        assert(0 <= idx && idx < shape_[0]);
#endif
        if constexpr (NDIMS == 1) {
            return (data_[strides_[0] * idx]);
        } else {
            std::array<int, NDIMS - 1> nshape;
            std::copy(shape_.begin() + 1, shape_.end(), nshape.begin());
            std::array<int, NDIMS - 1> nstrides;
            std::copy(strides_.begin() + 1, strides_.end(), nstrides.begin());
            T *ndata = data_ + (strides_[0] * idx);
            return tensor_view<T, NDIMS - 1>(nshape, nstrides, ndata);
        }
    }

    T &at(std::array<int, NDIMS> idx) const { return data_[flatten_index_checked(idx)]; }
    template <typename... I>
        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))
    T &at(I... idx) const {
        return at(std::array<int, NDIMS>{static_cast<int>(idx)...});
    }
    decltype(auto) at(int idx) const {
        assert(0 <= idx && idx < shape_[0]);
        return operator[](idx);
    }

private:
    tensor_view(std::array<int, NDIMS> shape, std::array<int, NDIMS> strides, T *data)
        : shape_(shape), strides_(strides), data_(data) {}
    int flatten_index(std::array<int, NDIMS> idx) const {
        int res = 0;
        for (int i = 0; i < NDIMS; ++i) {
            res += idx[i] * strides_[i];
        }
        return res;
    }
    int flatten_index_checked(std::array<int, NDIMS> idx) const {
        int res = 0;
        for (int i = 0; i < NDIMS; ++i) {
            assert(0 <= idx[i] && idx[i] < shape_[i]);
            res += idx[i] * strides_[i];
        }
        return res;
    }
    template <typename U, int D> friend struct tensor_view;
    template <typename U, int D> friend struct tensor;
    std::array<int, NDIMS> shape_;
    std::array<int, NDIMS> strides_;
    T *data_;
};

template <typename T, int NDIMS> struct tensor {
    static_assert(0 < NDIMS);

    tensor() : shape_{}, strides_{}, len_(0), data_(nullptr) {}
    explicit tensor(std::array<int, NDIMS> shape, const T &val = T()) : shape_(shape), len_(1) {
        for (int i = NDIMS - 1; 0 <= i; --i) {
            strides_[i] = len_;
            len_ *= shape_[i];
        }
        data_ = new T[len_];
        std::fill(data_, data_ + len_, val);
    }
    tensor(const tensor &o) : shape_(o.shape_), strides_(o.strides_), len_(o.len_), data_(new T[len_]) {
        for (int i = 0; i < len_; ++i) {
            data_[i] = o.data_[i];
        }
    }
    tensor(tensor &&o) noexcept
        : shape_(std::exchange(o.shape_, std::array<int, NDIMS>{})),
          strides_(std::exchange(o.strides_, std::array<int, NDIMS>{})), len_(std::exchange(o.len_, 0)),
          data_(std::exchange(o.data_, nullptr)) {}

    void swap(tensor &o) noexcept {
        std::swap(shape_, o.shape_);
        std::swap(strides_, o.strides_);
        std::swap(len_, o.len_);
        std::swap(data_, o.data_);
    }
    tensor &operator=(tensor &&o) noexcept {
        tensor tmp(std::move(o));
        swap(tmp);
        return *this;
    }
    tensor &operator=(const tensor &o) { return *this = tensor(o); }
    ~tensor() { delete[] data_; }

    using view_t = tensor_view<T, NDIMS>;
    view_t view() { return tensor_view<T, NDIMS>(shape_, strides_, data_); }
    operator view_t() { return view(); }

    using const_view_t = tensor_view<const T, NDIMS>;
    const_view_t view() const { return tensor_view<const T, NDIMS>(shape_, strides_, data_); }
    operator const_view_t() const { return view(); }

    T &operator[](std::array<int, NDIMS> idx) { return view()[idx]; }
    const T &operator[](std::array<int, NDIMS> idx) const { return view()[idx]; }

#ifdef __cpp_multidimensional_subscript
    template <typename... I>
        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))
    T &operator[](I... idx) {
        return (*this)[std::array<int, NDIMS>{static_cast<int>(idx)...}];
    }
    template <typename... I>
        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))
    const T &operator[](I... idx) const {
        return (*this)[std::array<int, NDIMS>{static_cast<int>(idx)...}];
    }
#endif

    decltype(auto) operator[](int idx) { return view()[idx]; }
    decltype(auto) operator[](int idx) const { return view()[idx]; }

    T &at(std::array<int, NDIMS> idx) { return view().at(idx); }
    const T &at(std::array<int, NDIMS> idx) const { return view().at(idx); }

    template <typename... I>
        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))
    T &at(I... idx) {
        return view().at(idx...);
    }
    template <typename... I>
        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))
    const T &at(I... idx) const {
        return view().at(idx...);
    }

    decltype(auto) at(int idx) { return view().at(idx); }
    decltype(auto) at(int idx) const { return view().at(idx); }

private:
    std::array<int, NDIMS> shape_;
    std::array<int, NDIMS> strides_;
    int len_;
    T *data_;
};

#endif // TENSOR_HPP

using Z = modint998244353;

void solve() {
    string S;
    cin >> S;
    auto N = int(size(S));
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        A[i] = S[i] - '0';
    }
    tensor<optional<Z>, 3> dp({N, 8, 8});
    auto f = [&](this auto &&self, int pos, int fit, int good) -> Z {
        if (pos == N)
            return good == 7;
        if (auto opt = dp[{pos, fit, good}])
            return *opt;
        Z ret = 0;
        constexpr array<int, 8> g{0, 1, 2, 4, 4, 2, 1, 0};
        for (auto m = 0; m < 8; ++m) {
            auto ok = true;
            auto nfit = 0;
            for (auto i = 0; i < 3; ++i) {
                if ((fit >> i) & 1) {
                    if (A[pos] < ((m >> i) & 1)) {
                        ok = false;
                        break;
                    }
                    if (((m >> i) & 1) == A[pos]) {
                        nfit ^= 1 << i;
                    }
                }
            }
            if (!ok)
                continue;
            auto ngood = good | g[m];
            ret += self(pos + 1, nfit, ngood);
        }
        return *(dp[{pos, fit, good}] = ret);
    };
    auto ans = f(0, 7, 0);
    cout << ans << "\n";
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
