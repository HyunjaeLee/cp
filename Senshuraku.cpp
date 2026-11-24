#include <atcoder/convolution>
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;
using i64 = long long;
using i128 = __int128;
using Z = modint998244353;

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

vector<Z> Pow(vector<Z> a, int n) {
    vector<Z> r{1};
    while (0 < n) {
        if (n & 1) {
            r = convolution(r, a);
        }
        a = convolution(a, a);
        n /= 2;
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<array<int, 2>> A(N);
    {
        auto M = 0;
        for (auto &[x, y] : A) {
            cin >> x >> y;
            M = max({M, x, y});
        }
        for (auto &[x, y] : A) {
            x = clamp(x, M - 2, M) - (M - 2);
            y = clamp(y, M - 2, M) - (M - 2);
        }
    }
    tensor<int, 2> freq({3, 3});
    for (auto [x, y] : A) {
        freq[x][y] += 1;
    }
    auto inv = Z(2).inv();
    auto F = [&] { // win = M
        vector<Z> f{1};
        for (auto i = 0; i < 3; ++i) {
            for (auto j = 0; j < 3; ++j) {
                if ((i == 2 && j == 1) || (i == 1 && j == 2)) {
                    vector<Z> a{0, 0, inv};
                    f = convolution(f, Pow(a, freq[i][j]));
                } else if ((i == 2 && j == 0) || (i == 0 && j == 2)) {
                    vector<Z> a{0, inv};
                    f = convolution(f, Pow(a, freq[i][j]));
                } else {
                    vector<Z> a{0, 0};
                    auto apply = [&](int k) {
                        if (k == 2) {
                            // 0
                        } else if (k == 1) {
                            a[1] += inv;
                        } else {
                            a[0] += inv;
                        }
                    };
                    apply(i);
                    apply(j);
                    f = convolution(f, Pow(a, freq[i][j]));
                }
            }
        }
        return f;
    };
    auto G = [&] { // win = M + 1
        vector<Z> g{1};
        for (auto i = 0; i < 3; ++i) {
            for (auto j = 0; j < 3; ++j) {
                vector<Z> a{0, 0};
                auto apply = [&](int k) {
                    if (k == 2) {
                        a[1] += inv; 
                    } else {
                        a[0] += inv;
                    }
                };
                apply(i);
                apply(j);
                g = convolution(g, Pow(a, freq[i][j]));
            }
        }
        return g;
    };
    tensor<Z, 3> ans({3, 3, 2});
    {
        freq[2, 1]--;
        auto f = convolution(F(), {0, 0, inv});
        for (auto i = 1; i < int(f.size()); ++i) {
            ans[2, 1, 0] += f[i] / i;
            ans[2, 1, 1] += f[i] / i;
        }
        freq[2, 1]++;
    }
    {
        freq[1, 2]--;
        auto f = convolution(F(), {0, 0, inv});
        for (auto i = 1; i < int(f.size()); ++i) {
            ans[1, 2, 0] += f[i] / i;
            ans[1, 2, 1] += f[i] / i;
        }
        freq[1, 2]++;
    }
    {
        freq[2, 0]--;
        auto f = convolution(F(), {0, inv});
        for (auto i = 1; i < int(f.size()); ++i) {
            ans[2, 0, 0] += f[i] / i;
        }
        freq[2, 0]++;
    }
    {
        freq[0, 2]--;
        auto f = convolution(F(), {0, inv});
        for (auto i = 1; i < int(f.size()); ++i) {
            ans[0, 2, 1] += f[i] / i;
        }
        freq[0, 2]++;
    }
    {
        freq[1, 1]--;
        auto f = convolution(F(), {0, inv});
        for (auto i = 1; i < int(f.size()); ++i) {
            ans[1, 1, 0] += f[i] / i;
            ans[1, 1, 1] += f[i] / i;
        }
        freq[1, 1]++;
    }
    {
        freq[1, 0]--;
        auto f = convolution(F(), {0, inv});
        for (auto i = 1; i < int(f.size()); ++i) {
            ans[1, 0, 0] += f[i] / i;
        }
        freq[1, 0]++;
    }
    {
        freq[0, 1]--;
        auto f = convolution(F(), {0, inv});
        for (auto i = 1; i < int(f.size()); ++i) {
            ans[0, 1, 1] += f[i] / i;
        }
        freq[0, 1]++;
    }
    {
        freq[2, 2]--;
        auto g = convolution(G(), {0, inv});
        for (auto i = 1; i < int(g.size()); ++i) {
            ans[2, 2, 0] += g[i] / i;
            ans[2, 2, 1] += g[i] / i;
        }
        freq[2, 2]++;
    }
    {
        freq[2, 1]--;
        auto g = convolution(G(), {0, inv});
        for (auto i = 1; i < int(g.size()); ++i) {
            ans[2, 1, 0] += g[i] / i;
        }
        freq[2, 1]++;
    }
    {
        freq[2, 0]--;
        auto g = convolution(G(), {0, inv});
        for (auto i = 1; i < int(g.size()); ++i) {
            ans[2, 0, 0] += g[i] / i;
        }
        freq[2, 0]++;
    }
    {
        freq[1, 2]--;
        auto g = convolution(G(), {0, inv});
        for (auto i = 1; i < int(g.size()); ++i) {
            ans[1, 2, 1] += g[i] / i;
        }
        freq[1, 2]++;
    }
    {
        freq[0, 2]--;
        auto g = convolution(G(), {0, inv});
        for (auto i = 1; i < int(g.size()); ++i) {
            ans[0, 2, 1] += g[i] / i;
        }
        freq[0, 2]++;
    }
    for (auto [x, y] : A) {
        cout << ans[x, y, 0].val() << " " << ans[x, y, 1].val() << " ";
    }
}
