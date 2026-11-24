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

#define TC
void solve() {
    int N;
    string S;
    cin >> N >> S;
    tensor<int, 3> dp({2, N + 1, 2 * N + 1});
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto Get = [&](int pos, int cnt0, int prev) {
        if (cnt0 < 0)
            return -inf;
        if (prev < -N || N < prev)
            return -inf;
        if (pos == N) {
            return (cnt0 == 0) ? 0 : -inf;
        }
        return dp[pos & 1, cnt0, N + prev];
    };
    for (auto pos = N - 1; 0 <= pos; --pos) {
        for (auto cnt0 = 0; cnt0 <= N; ++cnt0) {
            for (auto prev = -N; prev <= N; ++prev) {
                dp[pos & 1, cnt0, N + prev] = -inf;
                if (S[pos] == 'T' || S[pos] == 'N') {
                    auto suff = min(prev, 0) + 1;
                    auto val = Get(pos + 1, cnt0, suff);
                    dp[pos & 1, cnt0, N + prev] = max(dp[pos & 1, cnt0, N + prev], min(suff, val));
                }
                if (S[pos] == 'F' || S[pos] == 'N') {
                    auto suff = min(prev, 0) - 1;
                    auto val = Get(pos + 1, cnt0 - 1, suff);
                    dp[pos & 1, cnt0, N + prev] = max(dp[pos & 1, cnt0, N + prev], min(suff, val));
                }
            }
        }
    }
    auto ans = -inf;
    for (auto i = 0; i <= N; ++i) {
        ans = max(ans, i + Get(0, i, 0));
    }
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
