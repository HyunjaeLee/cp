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

#ifndef SPARSE_SEGTREE_2D_HPP
#define SPARSE_SEGTREE_2D_HPP

#include <algorithm>
#include <cassert>
#include <numeric>
#include <tuple>
#include <vector>

// https://github.com/Aeren1564/CP/blob/master/Library/Data_Structure/Segment_Tree/segment_tree_2d_sparse.sublime-snippet
// https://github.com/maspypy/library/blob/main/ds/segtree/segtree_2d.hpp
template <typename IndexType, class S, auto op, auto e, bool Compress = true> struct sparse_segtree_2d {
    sparse_segtree_2d(const std::vector<IndexType> &x, const std::vector<IndexType> &y)
        : sparse_segtree_2d(int(x.size()), [&](int i) { return std::tuple{x[i], y[i], e()}; }) {}
    sparse_segtree_2d(const std::vector<IndexType> &x, const std::vector<IndexType> &y, const std::vector<S> &data)
        : sparse_segtree_2d(int(x.size()), [&](int i) { return std::tuple{x[i], y[i], data[i]}; }) {}
    // f(i) = (x, y, val)
    sparse_segtree_2d(int n, auto f) : n_(n) {
        std::vector<IndexType> x(n), y(n);
        std::vector<S> wt(n);
        for (auto i = 0; i < n; ++i) {
            auto [a, b, c] = f(i);
            x[i] = a, y[i] = b, wt[i] = c;
        }
        if constexpr (Compress) {
            key_x_ = x;
            std::sort(key_x_.begin(), key_x_.end());
            key_x_.erase(std::unique(key_x_.begin(), key_x_.end()), key_x_.end());
            nx_ = int(key_x_.size());
        } else {
            min_x_ = (x.empty() ? 0 : *std::min_element(x.begin(), x.end()));
            nx_ = (x.empty() ? 1 : *std::max_element(x.begin(), x.end()) - min_x_ + 1);
        }
        log_ = 0;
        while ((1 << log_) < nx_) {
            ++log_;
        }
        size_ = 1 << log_;
        std::vector<int> ix(n);
        for (auto i = 0; i < n; ++i) {
            ix[i] = xtoi(x[i]);
        }
        indptr_.assign(2 * size_, 0);
        for (auto i : ix) {
            for (i += size_; i; i >>= 1) {
                ++indptr_[i];
            }
        }
        indptr_.insert(indptr_.begin(), 0);
        for (auto i = 1; i < int(indptr_.size()); ++i) {
            indptr_[i] += indptr_[i - 1];
        }
        data_.assign(2 * indptr_.back(), e());
        to_left_.assign(indptr_[size_], 0);
        std::vector<int> ptr = indptr_;
        std::vector<int> I(y.size());
        std::iota(I.begin(), I.end(), 0);
        std::sort(I.begin(), I.end(), [&](int i, int j) { return y[i] < y[j]; });
        pos_.resize(n);
        for (auto i = 0; i < n; ++i) {
            pos_[I[i]] = i;
        }
        for (auto raw_idx : I) {
            int i = ix[raw_idx] + size_;
            int j = -1;
            for (; i; i >>= 1) {
                int p = ptr[i];
                ptr[i]++;
                data_[indptr_[i + 1] + p] = wt[raw_idx];
                if (j != -1) {
                    to_left_[p] = (j % 2 == 0);
                }
                j = i;
            }
        }
        to_left_.insert(to_left_.begin(), 0);
        for (auto i = 1; i < int(to_left_.size()); ++i) {
            to_left_[i] += to_left_[i - 1];
        }
        for (auto i = 0; i < 2 * size_; ++i) {
            int off = 2 * indptr_[i];
            int m = indptr_[i + 1] - indptr_[i];
            for (auto j = m - 1; 0 < j; --j) {
                data_[off + j] = op(data_[off + 2 * j + 0], data_[off + 2 * j + 1]);
            }
        }
        all_y_ = y;
        std::sort(all_y_.begin(), all_y_.end());
    }
    // raw_idx: index in the original point cloud
    void multiply(int raw_idx, S val) {
        assert(0 <= raw_idx && raw_idx < n_);
        int i = 1, p = pos_[raw_idx];
        while (true) {
            multiply_i(i, p - indptr_[i], val);
            if (size_ <= i) {
                break;
            }
            int lc = to_left_[p] - to_left_[indptr_[i]];
            int rc = (p - indptr_[i]) - lc;
            if (to_left_[p + 1] - to_left_[p]) {
                p = indptr_[2 * i + 0] + lc;
                i = 2 * i + 0;
            } else {
                p = indptr_[2 * i + 1] + rc;
                i = 2 * i + 1;
            }
        }
    }
    // raw_idx: index in the original point cloud
    void set(int raw_idx, S val) {
        assert(0 <= raw_idx && raw_idx < n_);
        int i = 1, p = pos_[raw_idx];
        while (true) {
            set_i(i, p - indptr_[i], val);
            if (size_ <= i) {
                break;
            }
            int lc = to_left_[p] - to_left_[indptr_[i]];
            int rc = (p - indptr_[i]) - lc;
            if (to_left_[p + 1] - to_left_[p]) {
                p = indptr_[2 * i + 0] + lc;
                i = 2 * i + 0;
            } else {
                p = indptr_[2 * i + 1] + rc;
                i = 2 * i + 1;
            }
        }
    }
    // [lx, rx) * [ly, ry)
    // O(log^2 n)
    S prod(IndexType lx, IndexType rx, IndexType ly, IndexType ry) const {
        assert(lx <= rx && ly <= ry);
        int L = xtoi(lx);
        int R = xtoi(rx);
        S res = e();
        auto dfs = [&](auto self, int i, int l, int r, int a, int b) -> void {
            if (a == b || R <= l || r <= L) {
                return;
            }
            if (L <= l && r <= R) {
                res = op(res, query_i(i, a, b));
                return;
            }
            int la = to_left_[indptr_[i] + a] - to_left_[indptr_[i]];
            int ra = a - la;
            int lb = to_left_[indptr_[i] + b] - to_left_[indptr_[i]];
            int rb = b - lb;
            int m = (l + r) / 2;
            self(self, 2 * i + 0, l, m, la, lb);
            self(self, 2 * i + 1, m, r, ra, rb);
        };
        dfs(dfs, 1, 0, size_, int(std::lower_bound(all_y_.begin(), all_y_.end(), ly) - all_y_.begin()),
            int(std::lower_bound(all_y_.begin(), all_y_.end(), ry) - all_y_.begin()));
        return res;
    }
    // [lx, rx) * [ly, ry)
    // O(log n)
    int count(IndexType lx, IndexType rx, IndexType ly, IndexType ry) const {
        assert(lx <= rx && ly <= ry);
        int L = xtoi(lx);
        int R = xtoi(rx);
        int res = 0;
        auto dfs = [&](auto self, int i, int l, int r, int a, int b) -> void {
            if (a == b || R <= l || r <= L) {
                return;
            }
            if (L <= l && r <= R) {
                res += b - a;
                return;
            }
            int la = to_left_[indptr_[i] + a] - to_left_[indptr_[i]];
            int ra = a - la;
            int lb = to_left_[indptr_[i] + b] - to_left_[indptr_[i]];
            int rb = b - lb;
            int m = (l + r) / 2;
            self(self, 2 * i + 0, l, m, la, lb);
            self(self, 2 * i + 1, m, r, ra, rb);
        };
        dfs(dfs, 1, 0, size_, int(std::lower_bound(all_y_.begin(), all_y_.end(), ly) - all_y_.begin()),
            int(std::lower_bound(all_y_.begin(), all_y_.end(), ry) - all_y_.begin()));
        return res;
    }

private:
    int xtoi(IndexType x) const {
        if constexpr (Compress) {
            return int(std::lower_bound(key_x_.begin(), key_x_.end(), x) - key_x_.begin());
        }
        return std::clamp<IndexType>(x - min_x_, 0, nx_);
    }
    S query_i(int i, int a, int b) const {
        int lid = indptr_[i];
        int n = indptr_[i + 1] - indptr_[i];
        int off = 2 * lid;
        S val = e();
        for (auto L = n + a, R = n + b; L < R; L >>= 1, R >>= 1) {
            if (L & 1) {
                val = op(val, data_[off + L++]);
            }
            if (R & 1) {
                val = op(data_[off + --R], val);
            }
        }
        return val;
    }
    void multiply_i(int i, int j, S val) {
        int lid = indptr_[i];
        int n = indptr_[i + 1] - indptr_[i];
        int off = 2 * lid;
        for (j += n; j; j >>= 1) {
            data_[off + j] = op(data_[off + j], val);
        }
    }
    void set_i(int i, int j, S val) {
        int lid = indptr_[i];
        int n = indptr_[i + 1] - indptr_[i];
        int off = 2 * lid;
        j += n;
        data_[off + j] = val;
        for (; 0 < (j >>= 1);) {
            data_[off + j] = op(data_[off + 2 * j + 0], data_[off + 2 * j + 1]);
        }
    }
    int n_, nx_, log_, size_;
    IndexType min_x_;
    std::vector<IndexType> key_x_, all_y_;
    std::vector<int> pos_, indptr_, to_left_;
    std::vector<S> data_;
};

#endif // SPARSE_SEGTREE_2D_HPP

#include <atcoder/modint>
using Z = atcoder::modint998244353;

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<int> L{0}, R{0};
    for (auto i = 0; i < N; ++i) {
        if (L.back() < A[i]) {
            L.push_back(A[i]);
        }
    }
    for (auto i = N - 1; 0 <= i; --i) {
        if (R.back() < A[i]) {
            R.push_back(A[i]);
        }
    }
    vector<Z> pow2(N + 1);
    pow2[0] = 1;
    for (auto i = 1; i <= N; ++i) {
        pow2[i] = pow2[i - 1] * 2;
    }
    vector<Z> inv2(N + 1);
    inv2[N] = pow2[N].inv();
    for (auto i = N - 1; 0 <= i; --i) {
        inv2[i] = inv2[i + 1] * 2;
    }
    sparse_segtree_2d<int, int, [&](int, int) { return 0; }, [] { return 0; }> seg(
        N, [&](int i) { return tuple{A[i], i, 0}; });
    sparse_segtree_2d<int, Z, [&](Z a, Z b) { return a + b; }, [] { return 0; }> dpl(
        N, [&](int i) { return tuple{A[i], i, 0}; });
    for (auto i = 0; i < N; ++i) {
        auto it = ranges::lower_bound(L, A[i]);
        if (*it != A[i])
            continue;
        auto x = *prev(it);
        if (x == 0) {
            dpl.set(i, pow2[seg.count(0, A[i] + 1, i + 1, N)]);
            continue;
        }
        dpl.set(i, dpl.prod(x, x + 1, 0, i) * pow2[seg.count(0, A[i] + 1, i + 1, N)] * inv2[seg.count(0, x + 1, i, N)]);
    }
    sparse_segtree_2d<int, Z, [&](Z a, Z b) { return a + b; }, [] { return 0; }> dpr(
        N, [&](int i) { return tuple{A[i], i, 0}; });
    for (auto i = N - 1; 0 <= i; --i) {
        auto it = ranges::lower_bound(R, A[i]);
        if (*it != A[i])
            continue;
        auto x = *prev(it);
        if (x == 0) {
            dpr.set(i, pow2[seg.count(0, A[i] + 1, 0, i)]);
            continue;
        }
        dpr.set(i, dpr.prod(x, x + 1, i + 1, N) * pow2[seg.count(0, A[i] + 1, 0, i)] *
                       inv2[seg.count(0, x + 1, 0, i + 1)]);
    }
    auto H = ranges::max(A);
    Z ans = 0;
    for (auto i = 0; i < N; ++i) {
        if (A[i] < H)
            continue;
        ans += dpl.prod(A[i], A[i] + 1, i, i + 1) * inv2[seg.count(0, H + 1, i + 1, N)] * dpr.prod(A[i], A[i] + 1, i, i + 1) * inv2[seg.count(0, H + 1, 0, i)];
        auto l = dpl.prod(A[i], A[i] + 1, i, i + 1) * inv2[seg.count(0, H + 1, i + 1, N)] * inv2[seg.count(0, H + 1, 0, i + 1)];
        auto r = dpr.prod(A[i], A[i] + 1, i + 1, N);
        ans += l * r;
    }
    cout << ans.val() << "\n";
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
